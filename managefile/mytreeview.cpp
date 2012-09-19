//默认的树结构只有一列两个子树
#include <QStandardItem>
#include <QMessageBox>
#include <QModelIndex>
#include <QDir>
#include <QDebug>
#include <QMenu>
#include <QUuid>
#include <QInputDialog>
#include <QThread>

#include "mytreeview.h"
#include "utils.h"
#include "fileutils.h"
#include "mytreeitemmodel.h"
#include "db/tagdao.h"
#include "db/docdao.h"
#include "db/dirdao.h"
#include "db/doctagdao.h"
#include "db/relatedocdao.h"
#include "db/notedao.h"
#include "preferences.h"

#include "importdocdialog.h"
#include "exportdocdialog.h"
#include "createsubdirdialog.h"
#include "movetodirdialog.h"
#include "movetotagdialog.h"
#include "propofdirdialog.h"
#include "propoftagdialog.h"
#include "createtagdialog.h"
#include "sortsubdirsdialog.h"
#include "indexfile.h"

MyTreeView::MyTreeView(QString title, QWidget *parent) : treeTitle("tree"), QTreeView(parent), numSubTree(2),
    mouseStatus(true), curTitle(title)
{
	//默认两个子树的树形结构
        model = new MyTreeItemModel(this);
        //delegate = new MyTreeDelegate(parent);
//        model->setHeaderData(0, Qt::Horizontal, title);
        this->setModel(model);
        //this->setItemDelegate(delegate);

        //  "QTreeView::item:selected{background-color:rgb(255,255,255)}"

        // QCSS
        this->setStyleSheet(
                    "QTreeView::branch {image:none;}"
                    "QTreeView::item{height: 25px;}"
                    "QTreeView {show-decoration-selected: 1;}"
                    "QTreeView::item {border: 0px solid #d9d9d9;border-top-color: transparent;border-bottom-color: transparent;}"
                    "QTreeView::item:hover {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #e7effd, stop: 1 #cbdaf1);border: 1px solid #bfcde4;}"

                    "QTreeView::item:selected {border: 1px solid #567dbc;}"
                    "QTreeView::item:selected:active{background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6ea1f1, stop: 1 #567dbc);}"
                    "QTreeView::item:selected:!active {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6b9be8, stop: 1 #577fbf);}"

                    "QTreeView::branch:closed:has-children:has-siblings { image: url(:/icons/expander_normal.png);}"
                    "QTreeView::branch:has-children:!has-siblings:closed { image: url(:/icons/expander_normal.png); }"
                    "QTreeView::branch:open:has-children:has-siblings { image: url(:/icons/expander_open.png);}"
                    "QTreeView::branch:open:has-children:!has-siblings { image: url(:/icons/expander_open.png); }"
        );

        initTree();

        this->setMouseTracking(true);
        this->setAnimated(true);
        //this->setColumnWidth(0,160);

//        this->setDragEnabled(true);
//        this->setAcceptDrops(true);

        m_appName = tr("Solo Local File Manager");

        this->setSelectionMode(QAbstractItemView::SingleSelection);
        this->setSelectionBehavior(QAbstractItemView::SelectRows);

        this->header()->hide();
        this->setEditTriggers(NoEditTriggers);
        initActions();

        if(lastdirIndex.isValid()){
           this->expand(lastdirIndex);

        }
        if(lasttagIndex.isValid()){
           this->expand(lasttagIndex);
        }
        this->expandToDepth(2);
}

// 打开右键菜单
void MyTreeView::initTree()
{
    QStandardItem  *allDocItem = new QStandardItem(tr("AllDocs"));
    allDocItem->setData("", UUID);  // UUid
    allDocItem->setData("alldocs", NODE_TYPE); // Type
    allDocItem->setData("folder.ico",  Qt::DecorationRole);


    QStandardItem  *allTagItem = new QStandardItem(tr("AllTags"));
    allTagItem->setData("", UUID);
    allTagItem->setData("alltags", NODE_TYPE);
    allTagItem->setData("tags.png",  Qt::DecorationRole);

    QStandardItem  *wasteasketItem = new QStandardItem(tr("WasteBasket"));
    wasteasketItem->setData("", UUID);
    wasteasketItem->setData("basket", NODE_TYPE);
    wasteasketItem->setData("basket.ico",  Qt::DecorationRole);

    Preferences* p = Preferences::instance();
    lastdirUuid = p->getLastSelDirs();
    lasttagUuid = p->getLastSelTags();

    if(curTitle == "all"){
        model->setItem(0,0,allDocItem);
        model->setItem(1,0,allTagItem);
        model->setItem(2,0,wasteasketItem);
        loadDirs("", allDocItem);
        loadTagByParent("", allTagItem);
    }
    if(curTitle == "tag"){
        model->setItem(0, 0, allTagItem);
        loadTagByParent("", allTagItem);
    }
    if(curTitle == "doc"){
        model->setItem(0, 0, allDocItem);
        loadDirs("", allDocItem);
    }
    if(curTitle == "basket"){
        model->setItem(0, 0, wasteasketItem);
        loadDelDirs("", wasteasketItem);
    }
}

// Action 数据
void MyTreeView::initActions (){

    //Doc ContextMenu
    makeSubDir = new QAction(tr("&New Sub Dir"), this);
    connect(makeSubDir, SIGNAL(triggered()), this, SLOT(createSubDir()));
    moveToDir= new QAction(tr("&Move To Dir"), this);
    connect(moveToDir, SIGNAL(triggered()), this, SLOT(moveDir()));
    delDir= new QAction(tr("&Delete"), this);
    connect(delDir, SIGNAL(triggered()), this, SLOT(delSubDir()));
    renameDir= new QAction(tr("&Rename"), this);
    connect(renameDir, SIGNAL(triggered()), this, SLOT(renameSubDir()));

    // 导入
    importDir = new QAction(Utils::getIcon("document-import.png"),tr("&Import..."), this);
    importDir->setShortcut(tr("Ctrl+I"));
    connect(importDir, SIGNAL(triggered()), this, SLOT(importDlg()));
    // 导出
    exportDir = new QAction(Utils::getIcon("document-export.png"),tr("&Export..."), this);
    exportDir->setShortcut(tr("Ctrl+E"));
    connect(exportDir, SIGNAL(triggered()), this, SLOT(exportDlg()));

    subDirSort= new QAction(tr("&Sort SubDirs"), this);
    connect(subDirSort, SIGNAL(triggered()), this, SLOT(sortSubDirs()));

    showSubDirDoc= new QAction(tr("&Show docs under sub Dir"), this);
    showSubDirDoc->setCheckable(true);

    Preferences* p = Preferences::instance();
    showSubDirDoc->setChecked(p->isShowDocUnderSub());

    connect(showSubDirDoc, SIGNAL(triggered()), this, SLOT(setShowSubDirDoc()));

    protectDir= new QAction(Utils::getIcon("vip.png"), tr("&Protect"), this);
    connect(protectDir, SIGNAL(triggered()), this, SLOT(about()));
    propOfDir= new QAction(tr("&Properties"), this);
    connect(propOfDir, SIGNAL(triggered()), this, SLOT(properties()));

    //Root ContextMenu
    makeRootDir= new QAction(tr("&New Root Dir"), this);
    connect(makeRootDir, SIGNAL(triggered()), this, SLOT(createRootDir()));
    dirSort= new QAction(tr("&Sort Dir"), this);
    connect(dirSort, SIGNAL(triggered()), this, SLOT(sortSubDirs()));
    protectRootDir= new QAction(tr("&Protect"), this);
    connect(protectRootDir, SIGNAL(triggered()), this, SLOT(about()));
    optionOfDir= new QAction(tr("&Option"), this);
    connect(optionOfDir, SIGNAL(triggered()), this, SLOT(properties()));
    refreshDir= new QAction(tr("&Refresh"), this);
    connect(refreshDir, SIGNAL(triggered()), this, SLOT(refresh()));

    restoreA= new QAction(tr("&ReStore"), this);
    connect(restoreA, SIGNAL(triggered()), this, SLOT(restoreDir()));

    //Tag ContextMenu
    makeSubTag= new QAction(tr("&New Sub Tag"), this);
    connect(makeSubTag, SIGNAL(triggered()), this, SLOT(newTag()));
    moveToTag= new QAction(tr("&Move to Tag"), this);
    connect(moveToTag, SIGNAL(triggered()), this, SLOT(movetoTag()));
    moveToRootTag= new QAction(tr("&Move to Root Tag"), this);
    connect(moveToRootTag, SIGNAL(triggered()), this, SLOT(moveToRoot()));
    delTag= new QAction(tr("&Delete"), this);
    connect(delTag, SIGNAL(triggered()), this, SLOT(deleteTag()));
    renameTag= new QAction(tr("&Rename"), this);
    connect(renameTag, SIGNAL(triggered()), this, SLOT(renameSubTag()));
    showSubDirTag= new QAction(tr("&Show docs under sub Tag"), this);
    showSubDirTag->setCheckable(true);
    connect(showSubDirTag, SIGNAL(triggered()), this, SLOT(setShowSubTagDoc()));

    showSubDirTag->setChecked(p->isShowDocUnderSubTag());

    propOfTag= new QAction(tr("&Properties"), this);
    connect(propOfTag, SIGNAL(triggered()), this, SLOT(showPropOfTag()));

    //Root Tag ContextMenu
    makeTag= new QAction(tr("&New Tag"), this);
    connect(makeTag, SIGNAL(triggered()), this, SLOT(newTag()));

    //Root Basket ContextMenu
    clearBasket= new QAction(tr("&Clear Basket"), this);
    connect(clearBasket, SIGNAL(triggered()), this, SLOT(dropBasket()));

    // 右键
    contextMenu = new QMenu(this);
    contextMenu->setStyleSheet(
                "QMenu::item{height: 25px}"
                "QMenu::item:hover{background-color:rgb(100,100,100)}"
                "QMenu::item:selected{background-color:rgb(128,128,128)}"
    );
    contextMenu->hide();
}

// 打开右键菜单
void MyTreeView::treeContextMenuOpened()
{
    QPoint pos = getCurPoint();

    tableTree_currentItemChanged();
    if (contextMenu->actions().count() > 0){
        contextMenu->exec(this->viewport()->mapToGlobal(pos));
    }
}

// 打开右键菜单
void MyTreeView::tableTree_currentItemChanged()
{
        contextMenu->clear();
        QString type = getCurType();
        QString uuid = getCurUuid();

         QString delFlg;
        if(!uuid.isEmpty() && type == "basket" ){
            Dir dir = DirDao::selectDir(uuid);
            delFlg = dir.DELETE_FLAG;
        }
        // 如果选择Root
        if(type == "alldocs"){
            contextMenu->addAction(makeRootDir);
            contextMenu->addSeparator();
            contextMenu->addAction(refreshDir);
            contextMenu->addSeparator();
            contextMenu->addAction(dirSort);
            contextMenu->addSeparator();
            contextMenu->addAction(protectRootDir);
            contextMenu->addSeparator();
            contextMenu->addAction(optionOfDir);

        } else if(type == "alltags"){
            //Tag ContextMenu
            contextMenu->addAction(makeTag);
            contextMenu->addSeparator();
            contextMenu->addAction(refreshDir);
            contextMenu->addSeparator();
            contextMenu->addAction(showSubDirTag);
            contextMenu->addAction(propOfTag);
            contextMenu->addSeparator();
        }  else if(type == "tag"){
            contextMenu->addAction(makeSubTag);
            contextMenu->addSeparator();
            contextMenu->addAction(refreshDir);
            contextMenu->addSeparator();
            contextMenu->addAction(moveToTag);
            contextMenu->addAction(moveToRootTag);
            contextMenu->addAction(delTag);
            contextMenu->addAction(renameTag);
            contextMenu->addSeparator();
            contextMenu->addAction(showSubDirTag);
            contextMenu->addSeparator();
            contextMenu->addAction(propOfTag);
       }  else if(type == "doc"){
            contextMenu->addAction(makeSubDir);
            contextMenu->addSeparator();
            contextMenu->addAction(refreshDir);
            contextMenu->addSeparator();
            contextMenu->addAction(moveToDir);
            contextMenu->addAction(delDir);
            contextMenu->addAction(renameDir);
            contextMenu->addSeparator();
            contextMenu->addAction(importDir);
            contextMenu->addAction(exportDir);
            contextMenu->addSeparator();
            contextMenu->addAction(subDirSort);
            contextMenu->addSeparator();
            contextMenu->addAction(showSubDirDoc);
            contextMenu->addAction(subDirSort);
            contextMenu->addAction(protectDir);
            contextMenu->addAction(subDirSort);
            contextMenu->addAction(propOfDir);

        } else if(type == "basket" && uuid.isEmpty()){
            contextMenu->addAction(clearBasket);
            contextMenu->addSeparator();
            contextMenu->addAction(refreshDir);
        } else if(type == "basket" && delFlg == "1"){
            contextMenu->addAction(restoreA);
            contextMenu->addSeparator();
            contextMenu->addAction(refreshDir);
            contextMenu->addSeparator();
            contextMenu->addAction(propOfDir);
        }
        return;
}


MyTreeView::~MyTreeView()
{
     delete model;
}

void MyTreeView::setTreeTitle(QString title)
{
        model->setHeaderData(0, Qt::Horizontal, title);
}

void MyTreeView::setSubTreeTitle(int subTree, QString title)
{
        model->item(subTree)->setText(title);
}

void MyTreeView::addItem(int subTree, QString itemName, QString uuid, QString type, QString icon)
{
        QStandardItem  *parenItem = model->item(subTree);
        QStandardItem  *childItem =  new QStandardItem(itemName);
        childItem->setData(uuid, UUID);
        childItem->setData(type, NODE_TYPE);
        childItem->setData(icon,  Qt::DecorationRole);
        parenItem->appendRow(childItem);
}

QStandardItem* MyTreeView::addItemByParentItem(QStandardItem *parentItem, QString itemName, QString uuid, QString type, QString icon)
{
        QStandardItem  *childItem =  new QStandardItem(itemName);
        childItem->setData(uuid, UUID);
        childItem->setData(type, NODE_TYPE);
        childItem->setData(icon,  Qt::DecorationRole);
        parentItem->appendRow(childItem);
        return childItem;
}

bool MyTreeView::delSubItems(QStandardItem *parenItem)
{
    // 清除子节点
    int rows = parenItem->rowCount();
    int columns = parenItem->columnCount();
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            model->removeRow(i, parenItem->index());
            model->removeColumn(j, parenItem->index());
        }
    }

    parenItem->setRowCount(0);
    return true;
}

void MyTreeView::addItems(int subTree, QList<QString> nameList)
{
        QStandardItem  *parenItem = model->item(subTree);
	QList<QStandardItem*> childItems;
	QStandardItem  *tmpItem = NULL;
	int   i = 0;
	
	for(i = 0; i < nameList.size(); i++)
	{
		if(tmpItem != NULL)
		{
			tmpItem = NULL;
		}
		tmpItem = new QStandardItem(nameList.at(i));
		childItems.push_back(tmpItem);
	}
	
	parenItem->appendRows(childItems);
}

void MyTreeView::delelteItem(int subTree, QString itemName)
{
        QStandardItem  *parenItem = model->item(subTree);
	int  i = 0;
	
	//找出名字为itemName的子项，并将其删除
	for(i = 0; i < parenItem->rowCount(); i++)
	{	
		if(itemName == parenItem->child(i)->text())
		{
			parenItem->removeRow (i);
			break;
		}
	}
}

void MyTreeView::clearTree(int subTree)
{
        QStandardItem  *parenItem = model->item(subTree);
	int   i = 0;
	for(i = parenItem->rowCount() - 1; i >= 0; i--)
	{
		parenItem->removeRow(i);
	}
	
}

void MyTreeView::enableMouse(bool yesOrNo)
{
	mouseStatus = yesOrNo;
}

bool MyTreeView::getMouseStatus()
{
	return mouseStatus;
}

QString MyTreeView::getCurTitle()
{
	return curTitle;
}

QModelIndex MyTreeView::getCurIndex()
{
	return curIndex;
}
QStandardItem* MyTreeView::getCurItem()
{
       return curItem;
}
QString MyTreeView::getCurPath()
{
    // 递归出path
    QString path = "";

    QString uuid = qvariant_cast<QString>(curItem->data(UUID));
    if(uuid == ""){
        return "";
    }

    QStandardItem *tmp = curItem;
    path.prepend(QDir::separator());
    do
    {
       path.prepend(tmp->text());
       path.prepend(QDir::separator());
       tmp = tmp->parent();
       if(tmp != NULL){
           uuid = qvariant_cast<QString>(tmp->data(UUID));
       }
    }while(uuid != "");

    curPath = path;
    return path;
}
QString MyTreeView::getCurUuid()
{
        return curUuId;
}
QString MyTreeView::getCurType()
{
        return curType;
}
QPoint MyTreeView::getCurPoint(){
      return curPoint;
}

// 左键双击
void MyTreeView::mouseDoubleClickEvent(QMouseEvent *event)
{

        if(true == mouseStatus && Qt::LeftButton == event->button())
        {
                curPoint = event->pos();
                curIndex = indexAt(curPoint);
                if(curIndex.isValid()){
                       curItem = model->itemFromIndex(curIndex);
                       curTitle = curIndex.data().toString();
                       curUuId =  qvariant_cast<QString>(curItem->data(UUID));
                       curType = qvariant_cast<QString>(curItem->data(NODE_TYPE));
                       showChildTree();
                }
        }
}
//// 右键单击
//void MyTreeView::mousePressEvent(QMouseEvent *event)
//{
//        if(true == mouseStatus && Qt::RightButton == event->button() )
//        {
//                QModelIndex  index = this->currentIndex();
//                curItem = model->itemFromIndex(index);
//                curPath = qvariant_cast<QString>(curItem->data());

//                curIndex = index;
//                curTitle = index.data().toString();
//                curPoint = event->pos();
//                emit RBtnClk();
//        }
//}

// 单击
void MyTreeView::mouseReleaseEvent(QMouseEvent *event)
{
    // 右键
    if( Qt::RightButton == event->button() && true == mouseStatus){
        curPoint = event->pos();
        curIndex= indexAt(curPoint);
        if(curIndex.isValid()){
                curItem = model->itemFromIndex(curIndex);
                curTitle = curIndex.data().toString();
                curUuId =  qvariant_cast<QString>(curItem->data(UUID));
                curType = qvariant_cast<QString>(curItem->data(NODE_TYPE));
                treeContextMenuOpened();
        }
    }

    // 左键
    if(true == mouseStatus && Qt::LeftButton == event->button())
    {
            curPoint = event->pos();
            curIndex= indexAt(curPoint);
            if(curIndex.isValid()){
                curItem = model->itemFromIndex(curIndex);
                curTitle = curIndex.data().toString();
                curUuId =  qvariant_cast<QString>(curItem->data(UUID));
                curType = qvariant_cast<QString>(curItem->data(NODE_TYPE));
                emit LBtnClk();
            }
    }
}

//// 根据文件父目录取得子目录树结构
void MyTreeView::loadDirs(QString dirUuId,  QStandardItem *curItem){

    QList<Dir> dirs = DirDao::selectDirsbyParent(dirUuId, "0");

    //迭代出所有子节点
    for(int i = 0; i < dirs.count(); i++)
    {
            Dir dir = dirs.at(i);
            QString icon = dir.DIR_ICON;
            if(icon.isEmpty()){
                icon = "folder.ico";
            }
            QStandardItem* child = addItemByParentItem(curItem, dir.DIR_NAME, dir.DIR_GUID, "doc", icon);

            if(dirUuId == lastdirUuid){
                lastdirIndex = curItem->index();
                this->expand(lastdirIndex);
            }
            loadDirs(dir.DIR_GUID, child);
    }
}

// 根据文件父目录取得子目录树结构
void MyTreeView::loadDelDirs(QString dirUuId,  QStandardItem *curItem){

    QList<Dir> dirs = DirDao::selectDirsbyParent(dirUuId, "1");

    //迭代出所有子节点
    for(int i = 0; i < dirs.count(); i++)
    {
        Dir dir = dirs.at(i);
        QString icon = dir.DIR_ICON;
        if(icon.isEmpty()){
            icon = "folder.ico";
        }
        QStandardItem* child = addItemByParentItem(curItem, dir.DIR_NAME, dir.DIR_GUID, "basket", icon);

        loadDelDirs(dir.DIR_GUID, child);
    }
}
//
void MyTreeView::showImportDlg(){
     this->importDlg();
}
//
void MyTreeView::showExportDlg(){
     this->exportDlg();
}

// 根据标签来判断
void MyTreeView::loadTagByParent(QString tagUuId, QStandardItem *curItem){
    // 不需要判断tagUuId
    QList<Tag> tags = TagDao::selectTagsbyParent(tagUuId);

    //迭代出所有子节点
    for(int i = 0; i < tags.count(); i++)
    {
            Tag tag = tags.at(i);
            QStandardItem* child = addItemByParentItem(curItem, tag.TAG_NAME, tag.TAG_GUID, "tag", "tag.ico");

            QString tmpUuid = tag.TAG_GUID;
            loadTagByParent(tmpUuid, child);
    }
}

// 打开当前树节点
void MyTreeView::showChildTree()
{
    // 设置打开状态
    if(isExpanded(curIndex)){
       collapse(curIndex);
    }else{
       expand(curIndex);
    }

    if(curItem->hasChildren()){
       return;
    }

    if(curType == "doc" || curType == "alldocs" ){
       loadDirs(curUuId, curItem);
    }

    if(curType == "tag" || curType == "alltags" ){
       loadTagByParent(curUuId, curItem);
    }

    if(curType == "basket"){
       loadDelDirs(curUuId, curItem);
    }
}

// 删除子文件夹
void MyTreeView::delSubTree()
{
    QString curType = getCurType();
    QStandardItem* curItem = getCurItem();
    if(!curItem){
       return;
    }
    QStandardItem *parent = curItem->parent();

    if(!curType.isEmpty() && curType != "alltags" && curType != "alldocs") {
        delSubItems(curItem);
        parent->removeRow(curItem->row());
    }
}

// 根据CurPath设置当前选定的元素
void MyTreeView::setCurItemByUuid(QString uuId, QString type){

    QStandardItem *parenItem;
    //Doc树
    if(type == "alldocs" || type == "doc" ){
        parenItem = model->item(0);
    }else if (type == "alltags" || type == "tag"){
        parenItem = model->item(1);
    }else if (type == "basket"){
        parenItem = model->item(2);
   }

    //迭代出所有子节点
    for(int i = 0; i < parenItem->rowCount(); i++)
    {
            QStandardItem *item = parenItem->child(i);
            QString tcurUuid = qvariant_cast<QString>(item->data(UUID));
            if(tcurUuid == uuId){
                curItem = item;
                curUuId = qvariant_cast<QString>(item->data(UUID));
                curIndex = item->index();
                curTitle = item->data().toString();
                break;
            }
    }
}

// 重新加载Tag树
void MyTreeView::reloadTagTree()
{
       clearTree(1);
       QStandardItem *allTagItem = model->item(1,0);
       loadTagByParent("", allTagItem);
}
//////////////////////////////////////////////////Action 业务操作//////////////////////////////////////////////

// 设置是否显示子文件夹下的文件
void MyTreeView::setShowSubDirDoc()
{
    // 反向选择
    isShowDocUnderSub = showSubDirDoc->isChecked();
    Preferences* p = Preferences::instance();
    p->setShowDocUnderSub(isShowDocUnderSub);
}

// 设置是否显示子标签下的文件
void MyTreeView::setShowSubTagDoc()
{
    // 反向选择
    isShowDocUnderTag = showSubDirTag->isChecked();
    Preferences* p = Preferences::instance();
    p->setShowDocUnderSubTag(isShowDocUnderTag);
}

// 打开导入界面
void MyTreeView::importDlg()
{
    // 判断是否正在建立索引
    Preferences* p = Preferences::instance();
    bool isIndexing = p->getIsIndexing();
    if(isIndexing){
        QMessageBox::warning(this, tr("Warning"), tr("The index is busying. Please try later"), QMessageBox::Yes);
        return;
    }

    QString curType = getCurType();
    QString uuId = getCurUuid();
    bool hasSelRight = false;

    // 需选中子节点
    if(!curType.isEmpty() && curType != "alldocs" && curType != "alltags") {

        hasSelRight = true;
        // 后台运行Thread
        ImportDocDialog dlg(this, uuId, getCurPath());
        QThread thread;
        IndexFilesObj indexFilesObj;
        indexFilesObj.moveToThread(&thread);

        IndexFilesSign dummy;
        qDebug()<<"main thread:"<< QThread::currentThreadId();

        QObject::connect(&dummy, SIGNAL(sig()), &indexFilesObj, SLOT(indexfiles()));
        thread.start();
        dlg.exec();

        if(dlg.update){
            // 通知主界面改变不可搜索
            Preferences* p = Preferences::instance();
            p->setIsIndexing(true);
            dummy.emitsig();
            // 重新加载树节点
            QStandardItem* curItem = getCurItem();
            delSubItems(curItem);
            loadDirs(uuId, curItem);
        }
    }
    // 如果没有选中子目录节点
    if(!hasSelRight){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select an sub directory."), QMessageBox::Yes);
        return;
    }
}

// 打开导出界面
void MyTreeView::exportDlg()
{
    QString curType = getCurType();
    bool hasSelRight = false;

    // 需选中子节点
    if(!curType.isEmpty() && curType != "alldocs" && curType != "alltags") {
        hasSelRight = true;
        ExportDocDialog dlg(this, curUuId, getCurPath(), curType);
        dlg.exec();
        if(dlg.update){
          // 不做任何操作
        }
    }
    // 如果没有选中子目录节点
    if(!hasSelRight){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select an sub directory."), QMessageBox::Yes);
        return;
    }
}

// 查看文件夹属性
void MyTreeView::properties()
{
    QString curType = getCurType();
    bool hasSelRight = false;

    // 需选中子节点
    if(curType == "doc" || curType == "basket" ) {
        hasSelRight = true;
        PropOfDirDialog dlg(this, curUuId);
        dlg.exec();
        if(dlg.update){
          // 不做任何操作
        }
    }
    // 如果没有选中子目录节点
    if(!hasSelRight){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select an directory."), QMessageBox::Yes);
        return;
    }
}

// 刷新选中树结构
void MyTreeView::refresh()
{
    // 清除所有子节点
    delSubItems(curItem);
    showChildTree();
    // 展开
    QModelIndex index = getCurIndex();
    if(index.isValid()){
      expand(index);
    }
}

// 恢复文件夹  TODO 暂时无法解决 该功能屏蔽
void MyTreeView::restoreDir()
{
   // 清除所有子节点
   QString uuid = getCurUuid();
   QString title = getCurTitle();

   MoveToDirDialog dlg(this, uuid, getCurPath());
   dlg.exec();
   if(dlg.update){
         // 取得子界面选中的path
         QString toDirUuid = dlg.m_toUuid;
         // 删除主界面选中的节点
         curItem->parent()->removeRow(curItem->row());

         // 设置主界面的节点 (子界面新建文件夹情况下不成功)
         setCurItemByUuid(toDirUuid, "doc");
         addItemByParentItem(curItem, title, uuid, "doc", "folder.ico");
         expand(getCurIndex());

         // 设置所有子节点
         QList<Doc> docs;
         QList<Dir> allSubDirs;
         allSubDirs.append(DirDao::selectDir(uuid));
         DirDao::selectAllSubDirbyDir(allSubDirs, uuid, "1");
         // 逻辑恢复子文件夹
         for (int var = 0; var < allSubDirs.size(); var++) {
             // 文件夹
             Dir dir = allSubDirs.at(var);
             if( dir.DELETE_FLAG == "1"){
                 dir.DELETE_FLAG = "0";
                 dir.MF_VERSION = dir.MF_VERSION + 1;
                 DirDao::updateDir(dir);
             }
             // 取得删除的文档
             docs.append(DocDao::selectDocsbyDir(dir.DIR_GUID, "1"));
         }

         QList<Dir> allnormalSubDirs;
         DirDao::selectAllSubDirbyDir(allnormalSubDirs, uuid, "0");
         // 逻辑恢复子文件夹
         for (int var = 0; var < allnormalSubDirs.size(); var++) {
             // 文件夹
             Dir dir = allnormalSubDirs.at(var);
             // 取得删除的文档
             docs.append(DocDao::selectDocsbyDir(dir.DIR_GUID, "1"));
         }

         // 恢复文件
         for (int var = 0; var < docs.size(); var++) {
             // 文件
             Doc doc = docs.at(var);
             // 取得删除的文档
             doc.DELETE_FLAG = "0";
             doc.MF_VERSION = doc.MF_VERSION + 1;
             DocDao::updateDoc(doc);
         }
   }
}

// 创建子文件夹
void MyTreeView::createSubDir()
{
    QString curType = getCurType();
    QString curUuid = getCurUuid();
    bool hasSelRight = false;

    // 需选中 总节点和子节点
    if(curType == "doc") {
        hasSelRight = true;
        CreateSubDirDialog dlg(this, curUuid, getCurPath());
        dlg.exec();
        if(dlg.update){

            // 刷新选中的树
            QStandardItem* curItem = getCurItem();
            addItemByParentItem(curItem, dlg.dirName->text(), dlg.m_newUuid, "doc", "folder.ico");
            expand(getCurIndex());
        }
    }
    // 如果没有选中子目录节点
    if(!hasSelRight){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select an directory."), QMessageBox::Yes);
        return;
    }
}

// 移动文件夹
void MyTreeView::moveDir()
{
    QString curType = getCurType();
    QString curUuid = getCurUuid();
    QString curTitle = getCurTitle();
    QStandardItem* curItem = getCurItem();
    bool hasSelRight = false;

    // 需选中 文件 子节点
    if(curType == "doc") {
        hasSelRight = true;
        MoveToDirDialog dlg(this, curUuid, getCurPath());
        dlg.exec();
        if(dlg.update){
              // 取得子界面选中的path
              QString toDirUuid = dlg.m_toUuid;
              // 删除主界面选中的节点
              curItem->parent()->removeRow(curItem->row());

              // 设置主界面的节点 (子界面新建文件夹情况下不成功)
              if(dlg.m_newUuid != ""){
                  //子界面有新建文件夹情况,刷新
                  setCurItemByUuid(dlg.m_parent_newUuid, curType);
                  refresh();
              }

              setCurItemByUuid(toDirUuid, curType);

              QStandardItem* curItem = getCurItem();
              addItemByParentItem(curItem, curTitle, curUuid, "doc", "folder.ico");
              expand(getCurIndex());
        }
    }
    // 如果没有选中子目录节点
    if(!hasSelRight){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select an directory."), QMessageBox::Yes);
        return;
    }
}

// 改变子文件夹名称
void MyTreeView::renameSubDir()
{
    QString curType = getCurType();
    QStandardItem* curItem = getCurItem();
    QString curTitle = getCurTitle();
    bool hasSelRight = false;

    // 需选中 总节点和子节点
    if(!curType.isEmpty() && curType != "alltags") {
        hasSelRight = true;
        bool ok;
        QString text = QInputDialog::getText(this, m_appName, tr("New Directory name:"), QLineEdit::Normal, curTitle, &ok);
        if (ok && !text.isEmpty()) {
                if (text == curTitle){
                  return;
                }
                // 改变树节点
                curItem->setData(text, Qt::DisplayRole);
                // 改变目录名称
                Dir dir = DirDao::selectDir(getCurUuid());
                dir.DIR_NAME = text;
                dir.MF_VERSION = dir.MF_VERSION + 1;
                dir.DIR_ORDER = 0;
                DirDao::updateDir(dir);
        }
    }
    // 如果没有选中子目录节点
    if(!hasSelRight){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select an directory."), QMessageBox::Yes);
        return;
    }
}

// 子文件夹排序
void MyTreeView::sortSubDirs()
{
    QString curType = getCurType();
    QString curUuid = getCurUuid();
    bool hasSelRight = false;

    // 需选中 总节点和子节点
    if(curType == "doc" || curType == "alldocs" ) {
        hasSelRight = true;
        SortSubDirsDialog dlg(this, curUuid, getCurPath());
        dlg.exec();
        if(dlg.update){
            // 刷新选中的树
            setCurItemByUuid(curUuid, curType);
            delSubItems(curItem);
            //showChildTree();
        }
    }
    // 如果没有选中子目录节点
    if(!hasSelRight){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select an directory."), QMessageBox::Yes);
        return;
    }
}

// 新建根节点
void MyTreeView::createRootDir()
{
    QString curType = getCurType();
    bool hasSelRight = false;

    // 需选中 总节点
    if(curType == "alldocs") {
        hasSelRight = true;
        bool ok;
        QString text = QInputDialog::getText(this, m_appName, tr("New Root Directory name:"), QLineEdit::Normal, "", &ok);
        if (ok && !text.isEmpty()) {
                if (text == ""){
                  return;
                }
                // 插入目录
                Dir dir;
                dir.DIR_GUID = QUuid::createUuid();
                dir.DIR_PARENT_UUID = "";
                dir.DIR_NAME = text;
                dir.DIR_DESCRIPTION = "";
                dir.DIR_ICON = "folder.ico";
                dir.DIR_ORDER = 0;
                dir.DELETE_FLAG = '0';
                dir.MF_VERSION = 0;
                DirDao::insertDir(dir);

                QStandardItem* curItem = getCurItem();
                addItemByParentItem(curItem, text, dir.DIR_GUID , "doc", "folder.ico");
                expand(getCurIndex());
        }
    }
    // 如果没有选中子目录节点
    if(!hasSelRight){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select an directory."), QMessageBox::Yes);
        return;
    }
}

// 新建根标签
void MyTreeView::newTag()
{
    QString curType = getCurType();
    bool hasSelRight = false;

    // 需选中 标签 节点
    if(curType == "alltags" || curType == "tag") {
        hasSelRight = true;
        // curPath 用于判断根节点和子节点
        CreateTagDialog dlg(this, getCurUuid());
        dlg.exec();
        if(dlg.update){
              QStandardItem* curItem = getCurItem();
              addItemByParentItem(curItem,  dlg.m_tagname, dlg.m_newTagUuId, "tag", "tag.ico");
              expand(getCurIndex());
        }
    }
    // 如果没有选中子目录节点
    if(!hasSelRight){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select an directory."), QMessageBox::Yes);
        return;
    }
}

// 删除标签
void MyTreeView::deleteTag()
{
    QString curType = getCurType();
    bool hasSelRight = false;
    QString title = getCurTitle();
    QString curUuId = getCurUuid();

    // 需选中 标签 节点
    if(curType == "tag") {
        hasSelRight = true;
        int ret = QMessageBox::warning(this, QString(),
                           tr("Are you sure you want to delete the %1 tag?").arg(title),
                           QMessageBox::Yes | QMessageBox::No,
                           QMessageBox::No);

        if (ret == QMessageBox::No) {
            return;
        }
        if(ret == QMessageBox::Yes){
          delSubTree();
          // 删除Tag
          TagDao::deleteTag(curUuId);
          // 删除以它为父的所有Tag
          QList<Tag> tags;
          TagDao::selectAllSubTagbyTag(tags, curUuId);

          for (int var = 0; var < tags.length(); ++var) {
              Tag tag = tags.at(var);
              TagDao::deleteTag(tag.TAG_GUID);
              DocTagDao::deleteDocTagByTag(tag.TAG_GUID);
          }
        }
    }
    // 如果没有选中子目录节点
    if(!hasSelRight){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select an Sub Tag."), QMessageBox::Yes);
        return;
    }
}

// 改变子标签名称
void MyTreeView::renameSubTag()
{
    QString curType = getCurType();
    QStandardItem* curItem = getCurItem();
    QString curTitle = getCurTitle();
    QString curUuId = getCurUuid();

    bool hasSelRight = false;

    // 需选中 总节点和子节点
    if(curType == "tag") {
        hasSelRight = true;
        bool ok;
        QString text = QInputDialog::getText(this,  tr("Rename"), tr("Rename Tag name:"), QLineEdit::Normal, curTitle, &ok);
        if (ok && !text.isEmpty()) {
                if (text == curTitle){
                  return;
                }
                // 改变树节点
                curItem->setData(text, Qt::DisplayRole);
                // 改变标签名称
                // 删除Tag
                Tag tag = TagDao::selectTag(curUuId);
                tag.MF_VERSION = tag.MF_VERSION + 1;
                tag.TAG_NAME = text;
                TagDao::updateTag(tag);
        }

    }
    // 如果没有选中子目录节点
    if(!hasSelRight){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select an directory."), QMessageBox::Yes);
        return;
    }
}

// 显示标签参数
void MyTreeView::showPropOfTag()
{
    QString curType = getCurType();
    bool hasSelRight = false;

    // 需选中 标签 节点
    if(curType == "tag") {
        QString tagname = getCurTitle();
        QStandardItem*  curItem = getCurItem();
        QString curUuId = getCurUuid();
        Tag tag = TagDao::selectTag(curUuId);
        hasSelRight = true;
        // curPath 用于判断根节点和子节点
        // getCurPath 用于存UuId
        PropOfTagDialog dlg(this, tag.TAG_GUID, tagname, tag.TAG_DESCRIPTION);
        dlg.exec();
        if(dlg.update){
            if (dlg.m_tagname.isEmpty()){
              // 提示出错
              return;
            }
            // 改变树节点
            curItem->setData(dlg.m_tagname, Qt::DisplayRole);

        }
    }
    // 如果没有选中子目录节点
    if(!hasSelRight){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select an directory."), QMessageBox::Yes);
        return;
    }
}

void MyTreeView:: moveToRoot(){

    QString curType = getCurType();
    bool hasSelRight = false;

    // 需选中 标签 节点
    if(curType == "tag" ) {
        QString curUuid = getCurUuid();
        Tag tag = TagDao::selectTag(curUuid);
        hasSelRight = true;
        tag.TAG_GROUP_GUID = "";
        tag.MF_VERSION = tag.MF_VERSION + 1;
        TagDao::updateTag(tag);
        // 重新load的标签树
        // 删除当前的节点
        delSubTree();

        // 设置主界面节点
        addItem(1, tag.TAG_NAME, tag.TAG_GUID, "tag", "tag.ico");

    }
    // 如果没有选中子目录节点
    if(!hasSelRight){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select an Tag."), QMessageBox::Yes);
        return;
    }
}

// 移动标签
void MyTreeView::movetoTag()
{
    QString curType = getCurType();
    QStandardItem* curItem = getCurItem();
    QString curTitle = getCurTitle();
    QString curUuId = getCurUuid();
    bool hasSelRight = false;

    // 需选中 文件 子节点
    if(curType == "tag") {
        hasSelRight = true;
        MoveToTagDialog dlg(this, curUuId);
        dlg.exec();
        if(dlg.update){
              // 取得子界面选中的path
              QString mselUuId = dlg.m_selUuId;
              // 删除主界面选中的节点
              curItem->parent()->removeRow(curItem->row());

              // 设置主界面的节点 (子界面新建文件夹情况下不成功)
              setCurItemByUuid(mselUuId,  curType);

              QStandardItem* destItem = getCurItem();
              addItemByParentItem(destItem, curTitle, curUuId, "tag", "tag.ico");
              expand(getCurIndex());
        }
    }
    // 如果没有选中子标签节点
    if(!hasSelRight){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select an sub tag."), QMessageBox::Yes);
        return;
    }
}

// 删除子文件夹
void MyTreeView::delSubDir()
{
    QString curTitle = getCurTitle();
    QString curUuid = getCurUuid();
    int ret = QMessageBox::question(this, "",
                                    tr("Are you sure that delete the directory \"%1\"?").arg(curTitle),
                                    QMessageBox::Yes, QMessageBox::No);
    if(ret == QMessageBox::Yes){
       delSubTree();
       // 删除本节点
       DirDao::deleteDir(curUuid);
       DirDao::updateToRootDir(curUuid);
       DocDao::deleteDocByDirUid(curUuid);

       // 删除子节点
       QList<Dir> selDirList;
       DirDao::selectAllSubDirbyDir(selDirList, curUuid, "0");
       // 逻辑删除
       for (int var = 0; var < selDirList.size(); ++var) {
           // 文件夹
           Dir dir = selDirList.at(var);
           DirDao::deleteDir(dir.DIR_GUID);
           // 文件夹下的文件
           DocDao::deleteDocByDirUid(dir.DIR_GUID);
       }
    }

    if(ret == QMessageBox::No){
       return;
    }
}


// 删除子文件夹 TODO 加入进度条
void MyTreeView::dropBasket()
{
    int ret = QMessageBox::question(this, "",
                                    tr("Are you sure that drop the Basket ?"),
                                    QMessageBox::Yes, QMessageBox::No);
    if(ret == QMessageBox::No){
        return;
    }

    // 删除索引文件
    // 后台运行Thread
    QThread thread;
    DelIndexFilesObj indexFilesObj;
    indexFilesObj.moveToThread(&thread);

    DelIndexFilesSign dummy;
    qDebug()<<"main thread:"<< QThread::currentThreadId();

    QObject::connect(&dummy, SIGNAL(sigDelIndexFile()), &indexFilesObj, SLOT(delIndexfiles()));
    thread.start();
    dummy.emitDelIndexFile();

    QStandardItem *parenItem = model->item(2);
    delSubItems(parenItem);

    QList<Doc> deldocs = DocDao::selectDocsByDelFlg("1");
    Doc doc;

    QString notePath = Utils::getLocateNotesPath();
    DelIndexFilesObj noteindexFilesObj;
    foreach (doc, deldocs) {
       // 删除文档附属的标注
       QList<Note> notes = NoteDao::selectNotesbyDocUuId(doc.DOCUMENT_GUID);
       Note note;
       foreach (note, notes) {
           QString noteName = note.NOTE_NAME;
           // 删除note文件
           QString filepath = notePath;
           filepath.append(QDir::separator());
           filepath.append(noteName);
           filepath.append(".html");
           QFileInfo file(filepath);
           if(file.exists()){
               QFile::remove(filepath);
           }
           // 删除笔记索引
           noteindexFilesObj.delIndexfile(filepath, note.NOTE_GUID);
       }
       NoteDao::deleteNoteByDoc(doc.DOCUMENT_GUID);

       // 删除关联文档
       RelateDocDao::deleteRelateDocByDocUuId(doc.DOCUMENT_GUID);
       // 删除文档Tag
       DocTagDao::deleteDocTagByDoc(doc.DOCUMENT_GUID);
    }

    DirDao::physicalDelDir();
    DocDao::physicalDelDoc();

}



