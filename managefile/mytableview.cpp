#include<QPainter>
#include<QMouseEvent>
#include<QStandardItem>
#include<QHeaderView>
#include<QDir>
#include<QAction>
#include<QMenu>
#include<QMessageBox>
#include<QDesktopServices>
#include<QProcess>
#include<QDebug>
#include <QToolTip>

#include"mytableview.h"
#include"fileUtils.h"
#include "preferences.h"
#include "utils.h"
#include "exportconvertdialog.h"
#include "doctodirdialog.h"
#include "relatedocdialog.h"
#include "notesdialog.h"
#include "doctagsdialog.h"
#include "propofdocdialog.h"
#include "Common.h"
#include "mytreeitemmodel.h"
#include "db/docdao.h"
#include "db/notedao.h"
#include "printerwidget.h"
#include "QSettings"

static int preRow;
static int firstRow;
static int secRow;
MyTableView::MyTableView(QWidget * parent) : QTableView(parent), mouseStatus(true)
{
    delegate = new MyTableDelegate(parent);
    model = new MyTableItemModel(parent);

    this->setItemDelegate(delegate);

    horizontalHeader()->setMouseTracking (true);

    this->resizeColumnsToContents();
    this->resizeRowsToContents();
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);

    this->setMouseTracking(true);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setAcceptDrops(true);
    this->setShowGrid(true);

    // 可以设置第一行 选择排序控件
    // this->setItemDelegateForRow();

//    this->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
   // this->setAutoFillBackground(true);
//    this->setAlternatingRowColors(true);

    this->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
    this->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);


//    this->setObjectName(QString::fromUtf8("m_table"));
//    this->setAutoFillBackground(true);
//    this->setFrameShape(QFrame::NoFrame);
//    this->setFrameShadow(QFrame::Plain);
//    this->setLineWidth(0);
//    this->setEditTriggers(QAbstractItemView::AllEditTriggers);

//    this->setAlternatingRowColors(true);
//    this->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
//    this->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
//     this->setGridStyle(Qt::SolidLine);

//    this->horizontalHeader()->setVisible(true);
//    this->verticalHeader()->setVisible(false);

    connect(this, SIGNAL(entered(QModelIndex)),this, SLOT(showToolTip(QModelIndex)));

//    QDesktopServices::setUrlHandler( "mailto", this, "mailTo" );

    initActions();
}

// Action 数据
void MyTableView::initActions ()
{
    // 系统默认打开
    openInSysAction = new QAction(tr("&Open in System soft"), this);
    connect(openInSysAction, SIGNAL(triggered()), this, SLOT(openInSys()));

    // 在新tab页中打开
    openInTabAction = new QAction(tr("&Open in tab page"), this);
    connect(openInTabAction, SIGNAL(triggered()), this, SLOT(openInTab()));

    // 以资源管理器打开
    openInSysExploreAction = new QAction(tr("&Open in System Explorer"), this);
    connect(openInSysExploreAction, SIGNAL(triggered()), this, SLOT(openInSysExplore()));

    // 导出
    exportDocAction = new QAction(tr("&Export.."), this);
    connect(exportDocAction, SIGNAL(triggered()), this, SLOT(exportConvert()));

    // 以附件形式发送邮件
    emailAsAttachAction = new QAction(tr("&Send Email As Attachment"), this);
    connect(emailAsAttachAction, SIGNAL(triggered()), this, SLOT(sendMail()));

    // 文档笔记
    noteOfDocAction = new QAction(tr("&Notes"), this);
    connect(noteOfDocAction, SIGNAL(triggered()), this, SLOT(notes()));

    // 关联文档
    relatedDocAction = new QAction(tr("&Related Documents"), this);
    connect(relatedDocAction, SIGNAL(triggered()), this, SLOT(relateDocs()));

    // 标签
    tagAction = new QAction(tr("&Tags"), this);
    connect(tagAction, SIGNAL(triggered()), this, SLOT(docTags()));

    // 删除
    deleteAction = new QAction(tr("&Delete(Move to the Wastebasket)"), this);
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(delDoc()));

    // 加密
    encodeAction = new QAction(Utils::getIcon("vip.png"), tr("&Encrypt"), this);
    connect(encodeAction, SIGNAL(triggered()), this, SLOT(about()));

    // 查找替换
    findAndReplaceAction = new QAction(Utils::getIcon("vip.png"), tr("&Find and Replace"), this);
    connect(findAndReplaceAction, SIGNAL(triggered()), this, SLOT(about()));

    // 全选
    selectAllAction = new QAction(tr("&Select All"), this);
    connect(selectAllAction, SIGNAL(triggered()), this, SLOT(selectAllDoc()));

    // 打印
    printAction = new QAction(tr("&Print"), this);
    connect(printAction, SIGNAL(triggered()), this, SLOT(print()));

    // 高级
   advancedAction = new QAction(Utils::getIcon("vip.png"),tr("&Advanced"), this);
   QMenu *menu_ad = new QMenu(this);
   advancedAction->setMenu(menu_ad);
   // 转换文档
   convertDocAction = new QAction(tr("&Convert Document"), this);
   connect(convertDocAction, SIGNAL(triggered()), this, SLOT(about()));
   QMenu *menu_covert = new QMenu(this);
   convertDocAction->setMenu(menu_covert);
   office2pdfAction = new QAction(tr("&Convert Office to Pdf"), this);
   pdf2officeAction = new QAction(tr("&Convert Pdf to Office"), this);
   jpg2pdfAction = new QAction(tr("&Convert Picture to Pdf"), this);
   ppt2jpgAction = new QAction(tr("&Convert Ppt to Picture"), this);
   menu_covert->addAction(office2pdfAction);
   menu_covert->addAction(pdf2officeAction);
   menu_covert->addAction(jpg2pdfAction);
   menu_covert->addAction(ppt2jpgAction);

   // 合并文档
   combineAction = new QAction(tr("&Merge Document"), this);
   connect(combineAction, SIGNAL(triggered()), this, SLOT(about()));
   // 修复文档
   restoreAction = new QAction(tr("&Restore And Repair Document"), this);
   connect(restoreAction, SIGNAL(triggered()), this, SLOT(about()));
   // 批量打印文档
   pprintAction = new QAction(tr("&Print Documents In Batch"), this);
   connect(pprintAction, SIGNAL(triggered()), this, SLOT(about()));
   // 改变文档格式
   pformatChangeAction = new QAction(tr("&Change format in the Document"), this);
   connect(pformatChangeAction, SIGNAL(triggered()), this, SLOT(about()));
   menu_ad->addAction(convertDocAction);
   menu_ad->addAction(combineAction);
   menu_ad->addAction(restoreAction);
   menu_ad->addAction(pprintAction);
   menu_ad->addAction(pformatChangeAction);


   // 移动到文件夹
   moveToDirAction = new QAction(tr("&Move to..."), this);
   connect(moveToDirAction, SIGNAL(triggered()), this, SLOT(moveToDir()));
   // 复制到文件夹
   copyToDirAction = new QAction(tr("&Copy to..."), this);
   connect(copyToDirAction, SIGNAL(triggered()), this, SLOT(copyToDir()));
   // 选项 <选择第一行 以及第二行的内容>
   optionOfDocTableAction = new QAction(tr("&Option"), this);
   connect(optionOfDocTableAction, SIGNAL(triggered()), this, SLOT(about()));
   option_submenu = new QMenu(this);
   optionOfDocTableAction->setMenu(option_submenu);

   oneRowAction = new QAction(tr("&One Row"), this);
   oneRowAction->setData(ONE_ROW);
   oneRowAction->setCheckable(true);
   twoRowAction = new QAction(tr("&Two Rows"), this);
   twoRowAction->setData(TWO_ROWS);
   twoRowAction->setCheckable(true);
   twoRowOptionAction = new QAction(tr("&The second Row's Option"), this);
   showNotesAction = new QAction(tr("&Show notes of Document on Tooltip"), this);
   showNotesAction->setCheckable(true);

   option_submenu->addAction(oneRowAction);
   option_submenu->addAction(twoRowAction);
   option_submenu->addSeparator();
   option_submenu->addAction(twoRowOptionAction);
   option_submenu->addSeparator();
   option_submenu->addAction(showNotesAction);
   connect(option_submenu, SIGNAL(triggered(QAction*)), this, SLOT(slotShowTableOption(QAction*)));
   // 设定第二行的内容Menu
   secondRowSetMenu();
   twoRowOptionAction->setMenu(m_secondRowSetMenu);
   connect(m_secondRowSetMenu, SIGNAL(triggered(QAction*)), this, SLOT(slotShowSecondRowContent(QAction*)));

   // 属性
   propAction = new QAction(tr("&Properties"), this);
   connect(propAction, SIGNAL(triggered()), this, SLOT(propOfDoc()));

   // 右键
   cmenu = new QMenu(this);
   cmenu->setStyleSheet(
               "QMenu::item{height: 25px}"
               "QMenu::item:hover{background-color:rgb(100,100,100)}"
               "QMenu::item:selected{background-color:rgb(128,128,128)}"
   );
   cmenu->hide();

   // 右键表菜单
   cmenu->addAction(openInSysAction);
   cmenu->addAction(openInTabAction);
   cmenu->addAction(openInSysExploreAction);
   cmenu->addSeparator();
   cmenu->addAction(exportDocAction);
   cmenu->addAction(emailAsAttachAction);
   cmenu->addSeparator();
   cmenu->addAction(noteOfDocAction);
   cmenu->addAction(relatedDocAction);
   cmenu->addAction(tagAction);
   cmenu->addSeparator();
   cmenu->addAction(encodeAction);
   cmenu->addAction(findAndReplaceAction);
   cmenu->addAction(selectAllAction);
   cmenu->addAction(printAction);

   cmenu->addSeparator();
   cmenu->addAction(advancedAction);
   cmenu->addSeparator();

   cmenu->addAction(moveToDirAction);
   cmenu->addAction(copyToDirAction);
   cmenu->addAction(deleteAction);
   cmenu->addAction(optionOfDocTableAction);
   cmenu->addAction(propAction);
}

// 窗口大小调节各列的长度
void MyTableView::resizeEvent(QResizeEvent * event){
    int tablewidth = this->width();
    this->setColumnWidth(2, tablewidth * 1- 20);
}

void MyTableView::buildDocList(QList<Doc> doclist)
{
    Preferences* p = Preferences::instance();

    delete model;
    qDebug("buildDocList start");

    model = new MyTableItemModel();
    model->setColumnCount(3);
    this->hideColumn(0);

    // 设置各列比例,使其占满全行
    int tablewidth = this->width();
    this->setColumnWidth(1, 20);
    this->setColumnWidth(2, tablewidth);

    // 取得选择模式
    QString selModel = p->getTableSelMode();
    int intselModel = selModel.toInt();

    for (int var = 0; var < doclist.size(); ++var) {
         Doc doc = doclist.at(var);
         QString str = doc.DOCUMENT_LOCATION;
         QString docUuid = doc.DOCUMENT_GUID;

         QString filename = doc.DOCUMENT_NAME;
         int dotpos = filename.lastIndexOf(".");

         QString icon = filename.right(filename.length() - dotpos - 1).toLower();
         QString dotsuffix = filename.right(filename.length() - dotpos);
         QString suffix = "*" + dotsuffix;

         if(intselModel == ONE_ROW){
             // 第一行
             QList<QStandardItem*> items;

             QStandardItem* item = new QStandardItem();
             item->setData(docUuid, Qt::UserRole);
             items.append(item);
             // 支持的文件类型
             if(p->word().contains(suffix, Qt::CaseInsensitive)
                     || p->excel().contains(suffix, Qt::CaseInsensitive)
                     || p->ppt().contains(suffix, Qt::CaseInsensitive)
                     || p->pdf().contains(suffix, Qt::CaseInsensitive)
                     || p->htmls().contains(suffix, Qt::CaseInsensitive)
                     || p->pics().contains(suffix, Qt::CaseInsensitive)
                     || p->swfs().contains(suffix, Qt::CaseInsensitive)
                     || p->sources().contains(suffix, Qt::CaseInsensitive)
                     || p->txts().contains(suffix, Qt::CaseInsensitive)
                     || p->movies().contains(suffix, Qt::CaseInsensitive)
                     || p->ppt().contains(suffix, Qt::CaseInsensitive)
                     || p->ppt().contains(suffix, Qt::CaseInsensitive)){

                item = new QStandardItem();
                icon = icon.append(".ico");
                item->setData(icon,  Qt::DecorationRole);
                items.append(item);

                item = new QStandardItem();
                item->setBackground(QBrush(QColor(255, 255, 255)));
                item->setTextAlignment(Qt::AlignLeft);
                item->setFont(QFont( "Times", 10,  QFont::Normal ));
                item->setData(filename, Qt::DisplayRole);
                items.append(item);
             }

             if(p->allsupported().contains(suffix, Qt::CaseInsensitive)){
                 model->appendRow(items);
             }
         } else {
             // 第一行
             QList<QStandardItem*> items;
             // 第二行
             QList<QStandardItem*> secitems;

             QStandardItem* item = new QStandardItem();
             item->setData(docUuid, Qt::UserRole);
             items.append(item);
             // 支持的文件类型
             if(p->word().contains(suffix, Qt::CaseInsensitive)
                     || p->excel().contains(suffix, Qt::CaseInsensitive)
                     || p->ppt().contains(suffix, Qt::CaseInsensitive)
                     || p->pdf().contains(suffix, Qt::CaseInsensitive)
                     || p->htmls().contains(suffix, Qt::CaseInsensitive)
                     || p->pics().contains(suffix, Qt::CaseInsensitive)
                     || p->swfs().contains(suffix, Qt::CaseInsensitive)
                     || p->sources().contains(suffix, Qt::CaseInsensitive)
                     || p->txts().contains(suffix, Qt::CaseInsensitive)
                     || p->movies().contains(suffix, Qt::CaseInsensitive)
                     || p->ppt().contains(suffix, Qt::CaseInsensitive)
                     || p->ppt().contains(suffix, Qt::CaseInsensitive)){

                item = new QStandardItem();
                icon = icon.append(".ico");
                item->setData(icon,  Qt::DecorationRole);
                items.append(item);

                item = new QStandardItem();
                item->setBackground(QBrush(QColor(255, 255, 255)));
                item->setTextAlignment(Qt::AlignLeft);
                item->setFont(QFont( "Times", 10,  QFont::Normal ));
                item->setData(filename, Qt::DisplayRole);
                items.append(item);

                item = new QStandardItem();
                item->setData(docUuid, Qt::UserRole);
                secitems.append(item);

                item = new QStandardItem();
                item->setData("", Qt::DisplayRole);
                secitems.append(item);

                // 动态的第二项
                item = new QStandardItem();
                item->setData(getAvailableField(doc), Qt::DisplayRole);
                item->setTextAlignment(Qt::AlignTop);
                secitems.append(item);
                // 在第二个动态项中加入所有其他数据
                item->setData(doc.DT_CREATED , DOC_CREATE_DATE);
                item->setData(doc.DT_MODIFIED, DOC_MODIFIED_DATE);
                item->setData(doc.DT_ACCESSED, DOC_ACCESS_DATE);
                // 计算size K
                QFileInfo file(doc.DOCUMENT_LOCATION);
                item->setData(QString::number(file.size() / 1000)+ "K", DOC_SIZE);
                item->setData(doc.DOCUMENT_AUTHOR, DOC_AUTHOR);
                item->setData(doc.DOCUMENT_READ_COUNT, DOC_READ_COUNT);
                item->setData(doc.DOCUMENT_RELATE_COUNT, DOC_RELATED_COUNT);
                // 取得Tags <延后加载>
                // item->setData(doc.DT_CREATED, DOC_TAGS);

                item->setData(doc.DOCUMENT_URL, DOC_URL);
                item->setData(doc.DOCUMENT_LOCATION, DOC_LOCATION);
                // 取得Notes <延后加载>
                // item->setData(doc.DT_CREATED, DOC_NOTES);
             }

             if(p->allsupported().contains(suffix, Qt::CaseInsensitive)){
                 model->appendRow(items);
                 model->appendRow(secitems);
             }

         }
    }



//    int wide = this->columnWidth(0);
//    int nRow = model->rowCount();

//    for(int i =0; i< nRow; i++)
//    {
//       this->setColumnWidth(0, wide);
//       this->setRowHeight(i, 20);
//    }

    this->hideColumn(0);

    // 恢复QTableView的为未合并前的样子
//    for (int i = 0; i < model->rowCount(); ++i) {
//        this->setSpan(i, 1, 2, 1);
////        this->setSpan(i, 10, 1, 1);

//    }



    this->setModel(model);

    qDebug("buildDocList end");
}

// Show tooltip
void MyTableView::showToolTip(const QModelIndex &index)
{
    if (!index.isValid()) {
       return;
    }
    Preferences p = Preferences::instance();
    bool isShowNotes = p.isShowNotesOnTips();
    if(isShowNotes){
       if(! curUuid.isEmpty()){
            QString tips;
            QList<Note> list = NoteDao::selectNotesbyDocUuId(curUuid);
            for (int var = 0; var < list.size(); ++var) {
                Note note = list.at(var);
                tips.append(note.NOTE_CONTENT + "\n");
            }
            QToolTip::showText(QCursor::pos(), tips);
       }
    }
}

// 左键双击
void MyTableView::mouseDoubleClickEvent(QMouseEvent *event)
{

        if(true == mouseStatus && Qt::LeftButton == event->button())
        {

                curPoint = event->pos();
                QModelIndex  index = indexAt(curPoint);
                curItem = model->itemFromIndex(index);
                curPath = qvariant_cast<QString>(curItem->data(Qt::DisplayRole));

                int row = index.row();
                QStandardItem *uuidItem = model->item(row, 0);
                curUuid = qvariant_cast<QString>(uuidItem->data(Qt::UserRole));

                changeColor(row);
                emit LBtnDbClk();
        }
}
// 右键单击
void MyTableView::mousePressEvent(QMouseEvent *event)
{

        curPoint = event->pos();
        QModelIndex  index = indexAt(curPoint);
        curItem = model->itemFromIndex(index);
        curPath = qvariant_cast<QString>(curItem->data(Qt::DisplayRole));

        int row = index.row();
        QStandardItem *uuidItem = model->item(row, 0);
        curUuid = qvariant_cast<QString>(uuidItem->data(Qt::UserRole));
        // 左键退出
        if( Qt::LeftButton == event->button()){  
            changeColor(row);
            return;
        }
        // 右键显示菜单
        if(true == mouseStatus )
        {
            changeColor(row);
            tableContextMenuOpened();
        }
}

// 只需改变颜色
void MyTableView::changeColor(int curRow){


    int columnCount = model->columnCount();
    if(columnCount == 0){
        return;
    }

    QBrush white = QBrush(QColor(255, 255, 255));
    QBrush blue = QBrush(QColor(185, 210, 235));

    if(preRow %2 == 0 ){
       firstRow = preRow;
       secRow = firstRow + 1;
    }else{
        firstRow = preRow;
        secRow = firstRow - 1;
    }

    for(int i = 0; i< columnCount; i ++){
       QStandardItem *item = model->item(firstRow, i);
       if(item){
           item->setData(white, Qt::BackgroundRole);
       }
       item = model->item(secRow, i);
       if(item){
           item->setData(white, Qt::BackgroundRole);
       }
    }

    if(curRow %2 == 0 ){
       firstRow = curRow;
       secRow = firstRow + 1;
    }else{
        firstRow = curRow;
        secRow = firstRow - 1;
    }
    for(int i = 0; i< columnCount; i ++){
        QStandardItem *item = model->item(firstRow, i);
        if(item){
            item->setData(blue, Qt::BackgroundRole);
        }
        item = model->item(secRow, i);
        if(item){
            item->setData(blue, Qt::BackgroundRole);
        }
    }

    preRow = curRow;
}

QPoint MyTableView::getCurPoint(){
    return curPoint;
}

QString MyTableView::getCurUuid(){
    return curUuid;
}

QString MyTableView::getCurFilePath(){
    return curPath;
}

void MyTableView::enableMouse(bool yesOrNo)
{
    mouseStatus = yesOrNo;
}

bool MyTableView::getMouseStatus()
{
    return mouseStatus;
}
// 以系统工具打开
void MyTableView::openInSys()
{
    QFileInfo fileInfo(curPath);
    if(!fileInfo.exists()){
        QMessageBox::warning(this, tr("Warning"), tr("Please Confirm The original file  has Deleted Or Moved. "), QMessageBox::Yes);
        return;
    }
    QDesktopServices::openUrl ( QUrl::fromLocalFile(curPath) );
}
// 主界面Tab页打开
void MyTableView::openInTab()
{
    // 相当于双击
    emit LBtnDbClk();
}

// 在资源管理器中打开
void MyTableView::openInSysExplore()
{
    // 无需要 判断文件是否存在
    QFileInfo fileInfo(curPath);
    if(!fileInfo.exists()){
        QMessageBox::warning(this, tr("Warning"), tr("Please Confirm The original file  has Deleted Or Moved. "), QMessageBox::Yes);
    }

    QString path = fileInfo.absolutePath();
    QDesktopServices::openUrl(QUrl("file:///" + path));
}

// 显示导出转换文档界面
void MyTableView::exportConvert()
{
    bool hasSelRight = false;
    // 需选中文档
    if(!curPath.isEmpty()) {
        hasSelRight = true;
        ExportConvertDialog dlg(this, curPath);
        dlg.exec();
        if(dlg.update){
          // 不做任何操作
        }
    }
    // 如果没有选中子目录节点
    if(!hasSelRight){
        QMessageBox::warning(0, tr("Warning"), tr("Please Select an Document."), QMessageBox::Yes);
        return;
    }
}

// 显示导出转换文档界面
void MyTableView::sendMail()
{

    QFileInfo fileInfo(curPath);
    if(!fileInfo.exists()){
        QMessageBox::critical(this, tr("Error"), tr("Please Confirm The original file  has Deleted Or Moved. "), QMessageBox::Yes);
        return;
    }

//    Common* com = new Common();
//    QString mailcontent = "mailto:";
//    mailcontent.append("test@tom.com");
//    mailcontent.append("&subject=");
//    mailcontent.append(fileInfo.fileName());
//    mailcontent.append("&body=");
//    mailcontent.append(fileInfo.fileName() + tr("\n\nReview this document please."));
//    mailcontent.append("&attachment=");
//    mailcontent.append(curPath);

    // com->mailTo(QUrl(mailcontent, QUrl::TolerantMode));
    // QProcess::execute("7z", QStringList() << "e" << "C:\\docxTest\\1\\1.zip"  << "-oC:\\docxTest\\1\\unzip\\");

//    QString mail = QSettings( "HKEY_CURRENT_USER\\Software\\Clients\\Mail",
//            QSettings::NativeFormat ).value( "." ).toString();

//    QProcess* foo= new QProcess( this );
//    foo->setProcessChannelMode(QProcess::MergedChannels);
//    foo->setEnvironment( QProcess::systemEnvironment() );
//    foo->start( "outlook" );

//    if( !foo->waitForFinished() ) {
//        qDebug() << QDir( foo->workingDirectory() ).entryList();
//        qDebug() << "Fail:" << foo->errorString();
//        qDebug() << "Exit = " << foo->exitCode();
//    } else {
//        qDebug() << "Output:" << foo->readAll();
//    }


    QString regPath = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Office\\";
    QStringList officeverList;
    officeverList << "14.0";
    officeverList << "12.0";
    officeverList << "11.0";
    officeverList << "10.0";
    officeverList << "9.0";
    officeverList << "8.0";
    QString outLookPath;
    for (int var = 0; var < officeverList.length(); ++var) {
        QString version = officeverList.at(var);
        QString temp = regPath + version + "\\Outlook\\InstallRoot\\";
        QSettings *settings = new QSettings(temp, QSettings::NativeFormat);
        outLookPath = settings->value("Path", "").toString();
        QFileInfo outPath(outLookPath);
        if(outPath.exists()){
            break;
        }
    }

    QString program = outLookPath + "\\OUTLOOK.EXE";
    QStringList arguments;
    arguments.append("/a");
    arguments.append(curPath);
    QProcess *myProcess = new QProcess(this);
    myProcess->start(program, arguments);


    // 去掉所有符号
//    >     QString s = "{a fishy string?}";
//    >     QByteArray ba = QUrl::toPercentEncoding(s, QByteArray(),
//    > s.toLatin1());
//    >     qDebug() << ba;

}

// 显示出文档笔记
void MyTableView::notes()
{
    // 传递选择的docUuid
    Preferences* p = Preferences::instance();
    p->setSelDocUid(curUuid);

    m_notesdlg = new NotesDialog(this);
    connect(m_notesdlg, SIGNAL(showAddNoteWidget()), this, SLOT(showMainAddNoteWidget()));
    connect(m_notesdlg, SIGNAL(closeNoteWidget()), this, SLOT(hideMainAddNoteWidget()));

    bool hasSelRight = false;
    // 需选中文档
    if(!curUuid.isEmpty()) {
        hasSelRight = true;
        m_notesdlg->exec();
        if(m_notesdlg->update){
          // 不做任何操作
        }
    }
    // 如果没有选中子目录节点
    if(!hasSelRight){
        QMessageBox::warning(0, tr("Warning"), tr("Please Select an Document."), QMessageBox::Yes);
        return;
    }
}

// 显示Notes
void MyTableView::showNoteDialog()
{
    notes();
}

// 显示出文档笔记
void MyTableView::showMainAddNoteWidget()
{
    emit showAddNoteWidget();
}

// 隐藏文档笔记
void MyTableView::hideMainAddNoteWidget()
{
    if(m_notesdlg->needCloseNoteWiget){
          emit hideNoteWidget();
    }
}

// 显示出关联文档
void MyTableView::relateDocs()
{
    // 传递选择的docUuid
    Preferences* p = Preferences::instance();
    p->setSelDocUid(curUuid);

    m_relatedocdlg = new RelateDocDialog(this);

    bool hasSelRight = false;
    // 需选中文档
    if(!curPath.isEmpty()) {
        hasSelRight = true;
        m_relatedocdlg->exec();
        if(m_relatedocdlg->update){
          // 不做任何操作
        }
    }
    // 如果没有选中子目录节点
    if(!hasSelRight){
        QMessageBox::warning(0, tr("Warning"), tr("Please Select an Document."), QMessageBox::Yes);
        return;
    }
}

// 显示出文档Tag
void MyTableView::docTags()
{
    // 传递选择的docUuid
    m_doctagsdlg = new DocTagsDialog(this, curUuid);

    connect(m_doctagsdlg, SIGNAL(reloadTagTree()), this, SLOT(reloadMainTagTree()));

    bool hasSelRight = false;
    // 需选中文档
    if(!curUuid.isEmpty()) {
        hasSelRight = true;
        m_doctagsdlg->exec();
        if(m_doctagsdlg->update){
          // 不做任何操作
        }
    }
    // 如果没有选中子目录节点
    if(!hasSelRight){
        QMessageBox::warning(0, tr("Warning"), tr("Please Select an Document."), QMessageBox::Yes);
        return;
    }
}

// 删除文档(多选删除)
void MyTableView::delDoc()
{
    // 传递选择的docUuid
    Preferences* p = Preferences::instance();
    p->setSelDocUid(curUuid);

    int ret = QMessageBox::question(this, "", tr("Are you sure that delete the document ?"),
                                    QMessageBox::Yes, QMessageBox::No);
    if(ret == QMessageBox::Yes){
            if(!curUuid.isEmpty()){
                 // 保证右键选择的删除
                Doc doc;
                doc.DOCUMENT_GUID = curUuid;
                doc.DELETE_FLAG = "1";
                DocDao::updateDoc(doc);

                model->removeRow(firstRow);
                model->removeRow(secRow);

                // 选中的逻辑删除
                QItemSelectionModel *selections = this->selectionModel();
                QModelIndexList selected = selections->selectedIndexes();
                QMap<int, int> rowMap;

                foreach (QModelIndex index, selected)
                {
                    QStandardItem* item = model->itemFromIndex(index);
                    QString  docUuid = qvariant_cast<QString>(item->data(Qt::UserRole));
                    Doc doc;
                    doc.DOCUMENT_GUID = docUuid;
                    doc.DELETE_FLAG = "1";
                    DocDao::updateDoc(doc);

                    rowMap.insert(index.row(), 0);
                }

                int rowToDel;
                QMapIterator<int, int> rowMapIterator(rowMap);
                rowMapIterator.toBack();
                while (rowMapIterator.hasPrevious())
                {
                    rowMapIterator.previous();
                    rowToDel = rowMapIterator.key();
                    model->removeRow(rowToDel);
                }
            }
     }
    if(ret == QMessageBox::No){
           return;
    }
}

// 打开右键菜单
void MyTableView::tableContextMenuOpened()
{
    QPoint pos = getCurPoint();

    if (cmenu->actions().count() > 0){
        // 改变颜色
        QModelIndex  index = indexAt(pos);
        QStandardItem * selrange = model->itemFromIndex(index);

//        selrange->setData(QBrush(QColor(185, 210, 235)), Qt::BackgroundRole);
        cmenu->exec(this->viewport()->mapToGlobal(pos));
    }
}

// 打开主界面Notes
void MyTableView::showMainNotes()
{
    emit shownotes();
}

// 通知主界面重新Load标签树
void MyTableView::reloadMainTagTree()
{
    emit reloadTagTree();
}

// TODO 选中全部文件
void MyTableView::selectAllDoc()
{
      this->selectAll();
}

// 打印选中文件
void MyTableView::print()
{
    PrinterWidget diew = new PrinterWidget(this);
    diew.printer();
}

// 移动到文件夹
void MyTableView::moveToDir()
{

    DocToDirDialog dlg(this, curPath, curUuid, false);
    dlg.exec();
    if(dlg.update){
          // 删除主界面选中的节点
          model->removeRow(curItem->row());
    }
}

// 拷贝到文件夹
void MyTableView::copyToDir()
{
    DocToDirDialog dlg(this, curPath, curUuid, true);
    dlg.exec();
    if(dlg.update){
        // do nothing
    }
}

// 设定表单第二项选项项目
void MyTableView::secondRowSetMenu()
{
    m_secondRowSetMenu = new QMenu(this);
    // 设置Menu
    QAction *action1 = new QAction(this);
    action1->setData(CREATE_DATE);
    action1->setCheckable(true);
    action1->setText(tr("Create Date"));

    // 设置Menu
    QAction *action2 = new QAction(this);
    action2->setData(MODIFIED_DATE);
    action2->setCheckable(true);
    action2->setText(tr("Modified Date"));

    // 设置Menu
    QAction *action3 = new QAction(this);
    action3->setData(ACCESS_DATE);
    action3->setCheckable(true);
    action3->setText(tr("Accessed Date"));

    // 设置Menu
    QAction *action4 = new QAction(this);
    action4->setData(SIZE);
    action4->setCheckable(true);
    action4->setText(tr("Size"));

    QAction *action5 = new QAction(this);
    action5->setData(AUTHOR);
    action5->setCheckable(true);
    action5->setText(tr("Author"));

    QAction *action6 = new QAction(this);
    action6->setData(READ_COUNT);
    action6->setCheckable(true);
    action6->setText(tr("Read Count"));

    QAction *action7 = new QAction(this);
    action7->setData(RELATED_COUNT);
    action7->setCheckable(true);
    action7->setText(tr("Related Count"));

    QAction *action8 = new QAction(this);
    action8->setData(TAGS);
    action8->setCheckable(true);
    action8->setText(tr("Tags"));

    QAction *action9 = new QAction(this);
    action9->setData(URL);
    action9->setCheckable(true);
    action9->setText(tr("URL"));

    m_secondRowSetMenu->addAction(action1);
    m_secondRowSetMenu->addAction(action2);
    m_secondRowSetMenu->addAction(action3);
    m_secondRowSetMenu->addAction(action4);
    m_secondRowSetMenu->addAction(action5);
    m_secondRowSetMenu->addAction(action6);
    m_secondRowSetMenu->addAction(action7);
    m_secondRowSetMenu->addAction(action8);
    m_secondRowSetMenu->addAction(action9);
}

// 设定表单第二项选项项目
void MyTableView::slotShowSecondRowContent(QAction* action)
{
    QList<QAction*> actionList = m_secondRowSetMenu->actions();
    QAction* tmpaction;
    foreach(tmpaction, actionList){
        tmpaction->setChecked(false);
    }
    action->setChecked(true);

    int offset = action->data().toInt();
    updateSecRow(offset);
}

// 设定表单第二项选项项目
void MyTableView::updateSecRow(int type)
{
    int rowCount = model->rowCount();
    for(int i = 0; i< rowCount; i++){

        if(i%2 == 1){
            QModelIndex index = model->index(i, 2);
            QStandardItem *item = model->itemFromIndex(index);
            QString temp;
            // 表示第二行显示
            switch (type) {
                case CREATE_DATE:
                   temp =  qvariant_cast<QString>(model->data(index, DOC_CREATE_DATE));
                   break;
                case MODIFIED_DATE:
                   temp =  qvariant_cast<QString>(model->data(index, DOC_MODIFIED_DATE));
                   break;
                case ACCESS_DATE:
                   temp =  qvariant_cast<QString>(model->data(index, DOC_ACCESS_DATE));
                   break;
                case SIZE:
                   temp =  qvariant_cast<QString>(model->data(index, DOC_SIZE));
                    break;
                case AUTHOR:
                   temp =  qvariant_cast<QString>(model->data(index, DOC_AUTHOR));
                   break;
                case READ_COUNT:
                   temp =  qvariant_cast<QString>(model->data(index, DOC_READ_COUNT));
                    break;
                case RELATED_COUNT:
                   temp =  qvariant_cast<QString>(model->data(index, DOC_RELATED_COUNT));
                   break;
                case TAGS:
                   temp =  qvariant_cast<QString>(model->data(index, DOC_TAGS));
                   break;
                case URL:
                   temp =  qvariant_cast<QString>(model->data(index, DOC_URL));
                   break;
                case LOCATION:
                   temp =  qvariant_cast<QString>(model->data(index, DOC_LOCATION));
                   break;
                case NOTES:
                   temp =  qvariant_cast<QString>(model->data(index, DOC_NOTES));
                   break;
                 ;
            }
            item->setData(temp, Qt::DisplayRole);
        }
    }
}

// 设定表单选项Menu
void MyTableView::slotShowTableOption(QAction* action)
{
    int offset = action->data().toInt();

    Preferences p = Preferences::instance();
    // 设定其他的项目
    if(offset == 1){
       twoRowAction->setChecked(!oneRowAction->isChecked());
       p.setTableSelMode(QString::number(ONE_ROW));
    }
    // 设定其他的项目
    if(offset == 2){
       oneRowAction->setChecked(!twoRowAction->isChecked());
       p.setTableSelMode(QString::number(TWO_ROWS));
    }
}

// 显示文档属性
void MyTableView::propOfDoc()
{
    m_propOfdocdlg = new PropOfDocDialog(this, curUuid);

    bool hasSelRight = false;
    // 需选中文档
    if(!curUuid.isEmpty()) {
        hasSelRight = true;
        m_propOfdocdlg->exec();
        if(m_propOfdocdlg->update){
          // 不做任何操作
        }
    }
    // 如果没有选中子目录节点
    if(!hasSelRight){
        QMessageBox::warning(0, tr("Warning"), tr("Please Select an Document."), QMessageBox::Yes);
        return;
    }
}

// 显示文档属性
QString MyTableView::getAvailableField(Doc doc)
{
    Preferences p = Preferences::instance();
    QString field = p.getTableSelField();
    int selFied = field.toInt();

    if(selFied == CREATE_DATE){
       return doc.DT_CREATED;
    }
    if(selFied == MODIFIED_DATE){
       return doc.DT_MODIFIED;
    }
    if(selFied == ACCESS_DATE){
       return doc.DT_ACCESSED;
    }
    if(selFied == SIZE){
       // 计算size K
       QFileInfo file(doc.DOCUMENT_LOCATION);
       return QString::number(file.size() / 1000);
    }
    if(selFied == AUTHOR){
       return doc.DOCUMENT_AUTHOR;
    }
    if(selFied == READ_COUNT){
       return doc.DOCUMENT_READ_COUNT;
    }
    if(selFied == RELATED_COUNT){
       return doc.DOCUMENT_RELATE_COUNT;
    }
    if(selFied == TAGS){
       // 取得Tags
       return doc.DT_CREATED;
    }
    if(selFied == URL){
       return doc.DOCUMENT_URL;
    }

    return doc.DT_MODIFIED;
}




