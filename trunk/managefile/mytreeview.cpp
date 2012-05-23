//默认的树结构只有一列两个子树
#include <QStandardItem>
#include <QMessageBox>
#include <QModelIndex>
#include <QDir>
#include <QDebug>


#include "mytreeview.h"
#include "utils.h"
#include "fileutils.h"
#include "mytreeitemmodel.h"
#include "db/tagdao.h"
#include "db/docdao.h"
#include "db/dirdao.h"


MyTreeView::MyTreeView(QString title, QWidget *parent) : treeTitle("tree"), QTreeView(parent), numSubTree(2),
    mouseStatus(true), curTitle("title")
{
	//默认两个子树的树形结构
        model = new MyTreeItemModel(parent);
        delegate = new MyTreeDelegate(parent);

        model->setHeaderData(0, Qt::Horizontal, title);

        this->setModel(model);
        this->setItemDelegate(delegate);

        QStandardItem  *allDocItem = new QStandardItem(tr("AllDocs"));
        allDocItem->setData("", Qt::UserRole + 1);  // UUid
        allDocItem->setData("alldocs", Qt::UserRole + 2); // Type
        allDocItem->setData("folder.ico",  Qt::DecorationRole);


        QStandardItem  *allTagItem = new QStandardItem(tr("AllTags"));
        allTagItem->setData("", Qt::UserRole + 1);
        allTagItem->setData("alltags", Qt::UserRole + 2);
        allTagItem->setData("tags.ico",  Qt::DecorationRole);

        QStandardItem  *wasteasketItem = new QStandardItem(tr("WasteBasket"));
        wasteasketItem->setData("", Qt::UserRole + 1);
        wasteasketItem->setData("basket", Qt::UserRole + 2);
        wasteasketItem->setData("basket.ico",  Qt::DecorationRole);

        // QCSS
        this->setStyleSheet(
                    "QTreeView::branch {image:none;}"
                    "QTreeView::item{height: 25px;}"
                    "QTreeView::item:hover{background-color:rgb(100,100,100)}"
                    "QTreeView::item:selected{background-color:rgb(128,128,128)}"
                    "QTreeView::branch:closed:has-children:has-siblings { image: url(:/icons/expander_normal.png);}"
                    "QTreeView::branch:has-children:!has-siblings:closed { image: url(:/icons/expander_normal.png); }"
                    "QTreeView::branch:open:has-children:has-siblings { image: url(:/icons/expander_open.png);}"
                    "QTreeView::branch:open:has-children:!has-siblings { image: url(:/icons/expander_open.png); }"
        );

        if(title == "all"){
            model->setItem(0,0,allDocItem);
            model->setItem(1,0,allTagItem);
            model->setItem(2,0,wasteasketItem);
            loadDirs("", allDocItem);
            loadTagByParent("", allTagItem);
        }
        if(title == "tag"){
            model->setItem(1,0,allTagItem);
            loadTagByParent("", allTagItem);
        }
        if(title == "doc"){
            model->setItem(0,0,allDocItem);
            loadDirs("", allDocItem);
        }
        if(title == "basket"){
            model->setItem(0,0,wasteasketItem);
        }

        // 转移到Tree内部实现
        connect(this, SIGNAL(LBtnDbClk()), this, SLOT(showChildTree()));

        connect(this->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex &,const QModelIndex &)),
                this, SLOT(currentItemChanged(const QModelIndex &, const QModelIndex &)));

        this->setAnimated(true);
        this->setColumnWidth(0,160);

        this->setDragEnabled(true);
        this->setAcceptDrops(true);
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

void MyTreeView::addItem(int subTree, QString itemName, QString path, QString icon)
{
        QStandardItem  *parenItem = model->item(subTree);
        QStandardItem  *childItem =  new QStandardItem(itemName);
        childItem->setData(path, Qt::UserRole + 1);

        childItem->setIcon(Utils::getIcon(icon));
        parenItem->appendRow(childItem);
}

void MyTreeView::addItemByParentItem(QStandardItem *parentItem, QString itemName, QString uuid, QString type, QString icon)
{
        QStandardItem  *childItem =  new QStandardItem(itemName);
        childItem->setData(uuid, Qt::UserRole + 1);
        childItem->setData(type, Qt::UserRole + 2);
        childItem->setData(icon,  Qt::DecorationRole);
        parentItem->appendRow(childItem);
}

bool MyTreeView::delSubItems(QStandardItem *parenItem)
{
    // 清除直接点
    for(int i = 0; i < parenItem->rowCount(); i++)
    {
       parenItem->removeRow (i);
    }
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

    QString uuid = qvariant_cast<QString>(curItem->data(Qt::UserRole + 1));
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
           uuid = qvariant_cast<QString>(tmp->data(Qt::UserRole + 1));
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

                preRow = curIndex.row();
                preColumn = curIndex.column();

                curItem = model->itemFromIndex(curIndex);
                curTitle = curIndex.data().toString();
                curUuId =  qvariant_cast<QString>(curItem->data(Qt::UserRole + 1));
                curType = qvariant_cast<QString>(curItem->data(Qt::UserRole + 2));
		emit LBtnDbClk();
	}
}
//// 右键单击
//void myTreeList::mousePressEvent(QMouseEvent *event)
//{

//        // 左键退出
//        if( Qt::LeftButton == event->button()){
//          return;
//        }

//        if(true == mouseStatus )
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
    // 左键退出
    if( Qt::LeftButton == event->button()){

        curPoint = event->pos();
        curIndex= indexAt(curPoint);
        preRow = curIndex.row();
        preColumn = curIndex.column();

        curItem = model->itemFromIndex(curIndex);
        curTitle = curIndex.data().toString();
        curUuId =  qvariant_cast<QString>(curItem->data(Qt::UserRole + 1));
        curType = qvariant_cast<QString>(curItem->data(Qt::UserRole + 2));
        emit LBtnClk();
        return;
    }

    if(true == mouseStatus && Qt::RightButton == event->button())
    {
            curPoint = event->pos();
            curIndex= indexAt(curPoint);
            preRow = curIndex.row();
            preColumn = curIndex.column();

            curItem = model->itemFromIndex(curIndex);
            curTitle = curIndex.data().toString();
            curUuId =  qvariant_cast<QString>(curItem->data(Qt::UserRole + 1));
            curType = qvariant_cast<QString>(curItem->data(Qt::UserRole + 2));
            emit RBtnClk();
    }
}

//// 根据文件父目录取得子目录树结构
void MyTreeView::loadDirs(QString dirUuId,  QStandardItem *curItem){

    QList<Dir> dirs = DirDao::selectDirsbyParent(dirUuId);

    //迭代出所有子节点
    for(int i = 0; i < dirs.count(); i++)
    {
            Dir dir = dirs.at(i);
            QString icon = dir.DIR_ICON;
            if(icon.isEmpty()){
                icon = "folder.ico";
            }
            addItemByParentItem(curItem, dir.DIR_NAME, dir.DIR_GUID, "doc", icon);
    }
}

// 根据标签来判断
void MyTreeView::loadTagByParent(QString tagUuId, QStandardItem *curItem){
    // 不需要判断tagUuId
    QList<Tag> tags = TagDao::selectTagsbyParent(tagUuId);

    //迭代出所有子节点
    for(int i = 0; i < tags.count(); i++)
    {
            Tag tag = tags.at(i);
            addItemByParentItem(curItem, tag.TAG_NAME, tag.TAG_GUID, "tag", "tag.ico");
    }
}


// 打开当前树节点
void MyTreeView::showChildTree()
{

    QString curUId = getCurUuid();
    QStandardItem* curItem = getCurItem();
    QModelIndex curIndex = getCurIndex();

    QString type = qvariant_cast<QString>(curItem->data(Qt::UserRole + 2));
    // 设置打开状态
    if(isExpanded(curIndex)){
       collapse(curIndex);
    }else{
       expand(curIndex);
    }

    if(curItem->hasChildren()){
       return;
    }

    if(type == "doc" || type == "alldocs"){
       loadDirs(curUId, curItem);
    }

    if(type == "tag" || type == "alltags"){
       loadTagByParent(curUId, curItem);
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

    if(!curType.isEmpty() && curType != "alltags" && curType != "alldocs") {
        delSubItems(curItem);
        curItem->parent()->removeRow(curItem->row());
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
            QString tcurUuid = qvariant_cast<QString>(item->data(Qt::UserRole + 1));
            if(tcurUuid == uuId){
                curItem = item;
                curUuId = qvariant_cast<QString>(item->data(Qt::UserRole + 1));
                curIndex = item->index();
                curTitle = item->data().toString();
            }
    }
}
// 拖放事件
void MyTreeView::dropEvent(QDropEvent *event)
{
    qDebug() << "CLocalDirTreeView::dropEvent(QDropEvent *event)";
    qDebug() << "local::dropEvent mouse pos" << event->pos();
    QObject *source = qobject_cast<QObject *>(event->source());
    if (source && source != this) {
        qDebug() << "CLocalDirTreeView::dropEvent << " << event->mimeData()->text() << event->mimeData()->data("drag/remote");

        QModelIndex dropIndex = indexAt(event->pos());
        if(dropIndex != QModelIndex()) {
            //QDirModel *pModel = qobject_cast<QDirModel *>(model());
            //qDebug() << "drop to local path" << pModel->filePath(dropIndex) << "isdir" << pModel->isDir(dropIndex);
        }

        // 接受
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}
// 改变时间
void  MyTreeView::currentItemChanged(const QModelIndex &current, const QModelIndex &previous){
    qDebug("currentItemChanged");
     // 改变Item背景颜色，表示选中状态
//    QStandardItem* preItem = model->itemFromIndex(previous);
//    if (!current.isValid()|| !previous.isValid()){
//        return;
//    }
//    if(preItem){
//         qDebug("change preItem");
//       preItem->setData(QBrush(QColor(255,255,255)), Qt::BackgroundRole);
//    }
//    QStandardItem* currentItem = model->itemFromIndex(current);
//    if(currentItem){
//           qDebug("change preItem");
//       currentItem->setData(QBrush(QColor(150,150,150)), Qt::BackgroundRole);
//    }
}
// 重新加载Tag树
void MyTreeView::reloadTagTree()
{
       clearTree(1);
       QStandardItem *allTagItem = model->item(1,0);
       loadTagByParent("", allTagItem);
}


