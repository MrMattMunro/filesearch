/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the Graphics Dojo project on Qt Labs.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 or 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.  Please review the following information to ensure GNU
** General Public Licensing requirements will be met:
** http://www.fsf.org/licensing/licenses/info/GPLv2.html and
** http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include <QtGui>
#include <QtNetwork>
#include <QtWebKit>
#include <QtXmlPatterns>

#include <QTreeWidget>
#include <QTableView>
#include <QSplitter>
#include <QMenuBar>
#include <QMenu>
#include <QTime>
#include <QPoint>

#include <QInputDialog>
#include <QFileInfo>
#include <QDirModel>
#include <QTreeWidgetItem>
#include <QList>
#include <QDebug>
#include <QUuid>

#include "preferences.h"
#include "mainwindow.h"
#include "myTreeList.h"
#include "importdocdialog.h"
#include "exportdocdialog.h"
#include "createsubdirdialog.h"
#include "movetodirdialog.h"
#include "propofdirdialog.h"
#include "utils.h"
#include "fileutils.h"

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags), m_view(0)

{
    initUI();
    initActions();
    initMenus();
    initStatusbar();
    initToolbar();

    QWebSettings *defaultSettings = QWebSettings::globalSettings();
    defaultSettings->setAttribute(QWebSettings::JavascriptEnabled, true);
    defaultSettings->setAttribute(QWebSettings::PluginsEnabled, true);
    QWebSettings::setOfflineStoragePath(QDesktopServices::storageLocation(QDesktopServices::DataLocation));
    QWebSettings::setOfflineStorageDefaultQuota(500000);

     m_rssModel = new QStandardItemModel(this);
     setContextMenuPolicy(Qt::CustomContextMenu);
}

// 生成文档列表
void MainWindow::buildDocList()
{
    QString curPath = q_myTreeList->getCurPath();
    if(curPath == "alldocs" || curPath == "alltags" ){
        // 处理总根目录 TODO
        return;
    }

    // 是否显示子文件夹文档
    QStringList files;
    if(isShowDocUnderSub){
        QString datPath = curPath + QDir::separator();
        files = FileUtils::readAllDatFile(datPath, files);
    }else{
        QString datPath = curPath + QDir::separator() + "files.dat";
        files = FileUtils::readFile(datPath);
    }
    m_doctable->buildDocList(files);
}

// 初始化界面动作
void MainWindow::initActions()
{
        // 导入
        importAction = new QAction(Utils::getIcon("document-import.png"),tr("&Import..."), this);
        importAction->setShortcut(tr("Ctrl+I"));
        connect(importAction, SIGNAL(triggered()), this, SLOT(importDlg()));

        // 导出
        exportAction = new QAction(Utils::getIcon("document-export.png"),tr("&Export..."), this);
        exportAction->setShortcut(tr("Ctrl+E"));
        connect(exportAction, SIGNAL(triggered()), this, SLOT(exportDlg()));

        // 另存为
        saveAsAction = new QAction(Utils::getIcon("document-save-as.png"),tr("&Save As..."), this);
        saveAsAction->setShortcut(tr("Ctrl+S"));
        connect(saveAsAction, SIGNAL(triggered()), this, SLOT(about()));

        // 另存到移动设备
        saveToMobiAction = new QAction(Utils::getIcon("document-savetomobi.png"),tr("&Save To Mobile..."), this);
        connect(saveToMobiAction, SIGNAL(triggered()), this, SLOT(about()));

        // 退出
        exitAction = new QAction(Utils::getIcon("close.png"),tr("&Exit"), this);
        exitAction->setShortcut(tr("Ctrl+Q"));
        connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

        // 全屏
        fullScreenAction = new QAction(Utils::getIcon("view_fullscreen.png"),tr("&Full Screen"), this);
        fullScreenAction->setShortcut(tr("Ctrl+F"));
        connect(fullScreenAction, SIGNAL(triggered()), this, SLOT(fullScreen()));

        // 显示/隐藏分类树
        showClassTreeAction = new QAction(Utils::getIcon("view_tree.png"),tr("&Show/Hide Class Tree"), this);
        showClassTreeAction->setShortcut(tr("Ctrl+T"));
        connect(showClassTreeAction, SIGNAL(triggered()), this, SLOT(showClassTree()));

        // 皮肤
        skinAction = new QAction(Utils::getIcon("skins.png"),tr("&Skin"), this);
        menu_skin = new QMenu(this);
        skinAction->setMenu(menu_skin);

        //皮肤 默认
        defaultAction = new QAction(tr("&Defaut"), this);
        connect(defaultAction, SIGNAL(triggered()), this, SLOT(about()));

       // 皮肤 书香
        bookAction = new QAction(tr("&Book"), this);
        connect(bookAction, SIGNAL(triggered()), this, SLOT(about()));

        //皮肤 灰色
        grayAction = new QAction(tr("&Gray"), this);
        connect(grayAction, SIGNAL(triggered()), this, SLOT(about()));

        // 自定义工具栏
        customToolbarAction = new QAction(Utils::getIcon("toolbar.png"),tr("&Setting ToolBar"), this);
        connect(customToolbarAction, SIGNAL(triggered()), this, SLOT(about()));

        // 显示/隐藏工具栏
        showToolbarAction = new QAction(Utils::getIcon("status_bar.png"),tr("&Show/Hide Tool Bar"), this);
        connect(showToolbarAction, SIGNAL(triggered()), this, SLOT(showToolBar()));

        // 显示/隐藏状态栏
        showSatebarAction = new QAction(Utils::getIcon("status_bar.png"),tr("&Show/Hide Status Bar..."), this);
        connect(showSatebarAction, SIGNAL(triggered()), this, SLOT(about()));

        // 用户手册
        userBookAction = new QAction(Utils::getIcon("help_viewer.png"),tr("&Help"), this);
        userBookAction->setShortcut(tr("F2"));
        connect(userBookAction, SIGNAL(triggered()), this, SLOT(helpDoc()));

        // 个人主页
        homepageAction = new QAction(Utils::getIcon("homepage.png"),tr("&HomePage"), this);
        connect(homepageAction, SIGNAL(triggered()), this, SLOT(homepage()));

        // 邀请朋友
        inviteAction = new QAction(Utils::getIcon("invite.png"),tr("&Invite Friends..."), this);
        connect(inviteAction, SIGNAL(triggered()), this, SLOT(about()));

        // 论坛
        bbsAction = new QAction(Utils::getIcon("forum.png"),tr("&Forum"), this);
        connect(bbsAction, SIGNAL(triggered()), this, SLOT(bbs()));

        // 关于
        aboutAction = new QAction(Utils::getIcon("about.png"),tr("&About"), this);
        connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

        // 检查新版本
        checkNewAction = new QAction(Utils::getIcon("update_product.png"),tr("&Update"), this);
        connect(checkNewAction, SIGNAL(triggered()), this, SLOT(about()));

        // 选项
        optionAction = new QAction(Utils::getIcon("option.png"),tr("&Option"), this);
        optionAction->setShortcut(tr("Ctrl+O"));
        connect(optionAction, SIGNAL(triggered()), this, SLOT(about()));

        // 查看log
        viewLogAction = new QAction(Utils::getIcon("log.png"),tr("&View Log..."), this);
        viewLogAction->setShortcut(tr("Ctrl+L"));
        connect(viewLogAction, SIGNAL(triggered()), this, SLOT(about()));

        // 插件管理
        pluginAction = new QAction(Utils::getIcon("plugin.png"),tr("Plugins"), this);
        pluginAction->setShortcut(tr("Ctrl+P"));
        connect(pluginAction, SIGNAL(triggered()), this, SLOT(about()));;

        // 皮肤
        languageAction = new QAction(Utils::getIcon("language.png"),tr("&Language"), this);
        menu_language = new QMenu(this);
        languageAction->setMenu(menu_language);

        // 英文版
        enAction = new QAction(tr("&English"), this);
        connect(enAction, SIGNAL(triggered()), this, SLOT(about()));

        // 中文版
        cnAction = new QAction(tr("&Chinese"), this);
        connect(cnAction, SIGNAL(triggered()), this, SLOT(about()));

        // 日文版
        jpAction = new QAction(tr("&Japanese"), this);
        connect(jpAction, SIGNAL(triggered()), this, SLOT(about()));


        //Doc ContextMenu
        makeSubDir = new QAction(tr("&New Sub Dir"), this);
        connect(makeSubDir, SIGNAL(triggered()), this, SLOT(createSubDir()));
        moveToDir= new QAction(tr("&Move To Dir"), this);
        connect(moveToDir, SIGNAL(triggered()), this, SLOT(moveDir()));
        delDir= new QAction(tr("&Delete"), this);
        connect(delDir, SIGNAL(triggered()), this, SLOT(delSubDir()));
        renameDir= new QAction(tr("&Rename"), this);
        connect(renameDir, SIGNAL(triggered()), this, SLOT(renameSubDir()));
        subDirSort= new QAction(tr("&Sort SubDirs"), this);
        connect(subDirSort, SIGNAL(triggered()), this, SLOT(about()));

        showSubDirDoc= new QAction(tr("&Show docs under subDir"), this);
        showSubDirDoc->setCheckable(true);

        Preferences* p = Preferences::instance();
        showSubDirDoc->setChecked(p->isShowDocUnderSub());

        connect(showSubDirDoc, SIGNAL(triggered()), this, SLOT(setShowSubDirDoc()));

        protectDir= new QAction(tr("&Protect"), this);
        connect(protectDir, SIGNAL(triggered()), this, SLOT(about()));
        propOfDir= new QAction(tr("&Properties"), this);
        connect(propOfDir, SIGNAL(triggered()), this, SLOT(properties()));

        //Root ContextMenu
        makeRootDir= new QAction(tr("&New Root Dir"), this);
        connect(makeRootDir, SIGNAL(triggered()), this, SLOT(createRootDir()));
        dirSort= new QAction(tr("&Sort Dir"), this);
        connect(dirSort, SIGNAL(triggered()), this, SLOT(about()));
        protectRootDir= new QAction(tr("&Protect"), this);
        connect(protectRootDir, SIGNAL(triggered()), this, SLOT(about()));
        optionOfDir= new QAction(tr("&Option"), this);
        connect(optionOfDir, SIGNAL(triggered()), this, SLOT(about()));

        //Tag ContextMenu
        makeSubTag= new QAction(tr("&New Sub Tag"), this);
        connect(makeSubTag, SIGNAL(triggered()), this, SLOT(about()));
        moveToTag= new QAction(tr("&Move to Tag"), this);
        connect(moveToTag, SIGNAL(triggered()), this, SLOT(about()));
        moveToRootTag= new QAction(tr("&Move to Root Tag"), this);
        connect(moveToRootTag, SIGNAL(triggered()), this, SLOT(about()));
        delTag= new QAction(tr("&Delete"), this);
        connect(delTag, SIGNAL(triggered()), this, SLOT(about()));
        renameTag= new QAction(tr("&Rename"), this);
        connect(renameTag, SIGNAL(triggered()), this, SLOT(about()));
        showSubDirTag= new QAction(tr("&Show docs under subDir"), this);
        connect(showSubDirTag, SIGNAL(triggered()), this, SLOT(about()));
        propOfTag= new QAction(tr("&Properties"), this);
        connect(propOfTag, SIGNAL(triggered()), this, SLOT(about()));

        //Root Tag ContextMenu
        makeTag= new QAction(tr("&New Tag"), this);
        connect(makeTag, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::initMenus()
{
        menu_File = menuBar()->addMenu(tr("&File"));
        menu_File->addAction(importAction);
        menu_File->addAction(exportAction);
        menu_File->addSeparator();
        menu_File->addAction(saveAsAction);
        menu_File->addAction(saveToMobiAction);
        menu_File->addSeparator();
        menu_File->addAction(exitAction);

        menu_View = menuBar()->addMenu(tr("&View"));
        menu_View->addAction(fullScreenAction);
        menu_View->addAction(showClassTreeAction);
        menu_View->addAction(showToolbarAction);
        menu_View->addAction(skinAction);

        menu_skin->addAction(defaultAction);
        menu_skin->addAction(bookAction);
        menu_skin->addAction(grayAction);
        menu_View->addAction(menu_skin->menuAction());

        menu_View->addAction(languageAction);
        menu_language->addAction(cnAction);
        menu_language->addAction(enAction);
        menu_language->addAction(jpAction);
        menu_View->addAction(menu_language->menuAction());

        menu_View->addSeparator();
        menu_View->addAction(showSatebarAction);
        menu_View->addSeparator();
        menu_View->addAction(customToolbarAction);

        menu_Tool =  menuBar()->addMenu(tr("&Tool"));
        menu_Tool->addAction(optionAction);
        menu_Tool->addSeparator();
        menu_Tool->addAction(viewLogAction);
        menu_Tool->addSeparator();
        menu_Tool->addAction(pluginAction);

        menu_Help =  menuBar()->addMenu(tr("&Help"));
        menu_Help->addAction(userBookAction);
        menu_Help->addAction(homepageAction);
        menu_Help->addSeparator();
        menu_Help->addAction(inviteAction);
        menu_Help->addSeparator();
        menu_Help->addAction(checkNewAction);
        menu_Help->addSeparator();
        menu_Help->addAction(bbsAction);
        menu_Help->addAction(aboutAction);
        menu_Help->addSeparator();

        // 右键
        contextMenu = new QMenu(this);
        contextMenu->setStyleSheet(
                    "QMenu::item{height: 20px;}"
                    "QMenu::item:hover{background-color:rgb(100,100,100)}"
                    "QMenu::item:selected{background-color:rgb(128,128,128)}"
        );
        contextMenu->hide();
}
// 状态栏
void MainWindow::initStatusbar()
{
//    QLabel* m_sqliteVersionLabel = new QLabel(this);
//    statusBar()->addPermanentWidget(&m_sqliteVersionLabel);
}

// 工具栏
void MainWindow::initToolbar()
{
    toolBar = addToolBar(tr("Tool Bar"));
    toolBar->addAction(showClassTreeAction);
    toolBar->addAction(fullScreenAction);
    toolBar->addSeparator();


    label = new QLabel(tr("Find &what:"));
    lineEdit = new QLineEdit;
    label->setBuddy(lineEdit);

    lineEdit->setMaximumWidth(120);
    findButton = new QPushButton(tr("&Search"));
    findButton->setDefault(true);
    findButton->setEnabled(false);

    connect(lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(enableFindButton(const QString&)));
    connect(findButton, SIGNAL(clicked()), this, SLOT(findClicked()));

    toolBar->addWidget(label);
    toolBar->addWidget(lineEdit);
    toolBar->addWidget(findButton);
}

// 用户手册
void MainWindow::helpDoc()
{
   m_view->load(QUrl("http://www.slfile.net/?page_id=58"));
}

// 论坛
void MainWindow::bbs()
{
   m_view->load(QUrl("http://www.slfile.net/?post_type=forum"));
}

// 主页
void MainWindow::homepage()
{
   m_view->load(QUrl("http://www.slfile.net/"));
}

// 设置是否显示子文件夹下的文件
void MainWindow::setShowSubDirDoc()
{
    // 反向选择
    isShowDocUnderSub = showSubDirDoc->isChecked();
    Preferences* p = Preferences::instance();
    p->setShowDocUnderSub(isShowDocUnderSub);
}

void MainWindow::enableFindButton(const QString &text)
{
     findButton->setEnabled(!text.isEmpty());
}

void MainWindow::findClicked()
{
     QString text = lineEdit->text();
     //emit findPrevious(text, cs);
}

// 打开导入界面
void MainWindow::importDlg()
{
    QString curPath = q_myTreeList->getCurPath();
    bool hasSelRight = false;

    // 需选中子节点
    if(!curPath.isEmpty() && curPath != "alldocs" && curPath != "alltags") {
        hasSelRight = true;
        ImportDocDialog dlg(this, m_baseDir, q_myTreeList->getCurPath());
        dlg.exec();
        if(dlg.update){
            int row= dlg.model->rowCount();
            // 创建路径列表
            FileUtils::copyDirectory(QDir(dlg.m_importDir),QDir(curPath));


            QMap<QString, QStringList> writeMap;

            for (int var = 0; var < row; ++var) {
                QStandardItem* temp = dlg.model->item(var);
                QString path = temp->text();

                QString filepath = path.left(path.lastIndexOf(QDir::separator()));
                filepath = filepath.replace("\"","");

                // 设置目标目录
                QString destDir = filepath.remove(0, dlg.m_importDir.length());
                QString tempPath = curPath;
                QString datfilepath = tempPath.append(destDir).append(QDir::separator()).append("files.dat");

                QUuid uuid = QUuid::createUuid();
                if(writeMap.contains(datfilepath)){
                    QStringList files = writeMap[datfilepath];
                    files << uuid.toString().append(",").append(path);
                    writeMap.insert(datfilepath, files);
                } else {
                    QStringList files;
                    files << uuid.toString().append(",").append(path);
                    writeMap.insert(datfilepath, files);
                }

            }

            // 一次写入文件
            QMapIterator<QString, QStringList> rowMapIterator(writeMap);
            rowMapIterator.toBack();
            while (rowMapIterator.hasPrevious())
            {
                rowMapIterator.previous();
                QString datfilepath = rowMapIterator.key();
                QStringList files = rowMapIterator.value();
                FileUtils::writeFile(datfilepath, files);
            }

            // 清除空目录<既无子文件夹也无files.dat文件>
            FileUtils::delDirectory(QDir(curPath));
            // 重新加载树节点
            QStandardItem* curItem = q_myTreeList->getCurItem();
            q_myTreeList->delSubItems(curItem);
            QString curPath = q_myTreeList->getCurPath();
            q_myTreeList->loadDirByLay(curPath, 1, curItem);
        }
    }
    // 如果没有选中子目录节点
    if(!hasSelRight){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select an sub directory."), QMessageBox::Yes);
        return;
    }
}

// 打开导出界面
void MainWindow::exportDlg()
{
    QString curPath = q_myTreeList->getCurPath();
    bool hasSelRight = false;

    // 需选中子节点
    if(!curPath.isEmpty() && curPath != "alldocs" && curPath != "alltags") {
        hasSelRight = true;
        ExportDocDialog dlg(this, m_baseDir, q_myTreeList->getCurPath());
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
void MainWindow::properties()
{
    QString curPath = q_myTreeList->getCurPath();
    bool hasSelRight = false;

    // 需选中子节点
    if(!curPath.isEmpty() && curPath != "alltags") {
        hasSelRight = true;
        PropOfDirDialog dlg(this, m_baseDir, q_myTreeList->getCurPath());
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



void MainWindow::initUI()
{
        setWindowTitle(m_appName);

        splitter = new QSplitter(this);

        m_view = new QWebView(this);
        m_view->move(-1000, -1000);
        m_view->page()->mainFrame()->load(QUrl("http://www.slfile.net"));


        // 加载分类树
        m_baseDir = Utils::getLocatePath();
        m_baseDir = QDir::toNativeSeparators(m_baseDir);
        q_myTreeList = new myTreeList("", this);

        q_myTreeList->loadDirByLay(m_baseDir, 0, 0);
        q_myTreeList->enableMouse(true);

        m_doctable = new MyTableView(this);



        splitter->addWidget(q_myTreeList);
        splitter->addWidget(m_doctable);
        splitter->addWidget(m_view);

        // connect(q_myTreeList, SIGNAL(LBtnDbClk()), this, SLOT(showChildTree()));
        connect(q_myTreeList, SIGNAL(RBtnClk()), this, SLOT(treeContextMenuOpened()));
        connect(q_myTreeList, SIGNAL(LBtnClk()), this, SLOT(buildDocList()));

        setCentralWidget(splitter);
}


////// 根据文件父目录取得子目录树结构
//int MainWindow::loadDirByLay(QString parentPath, int lay, QStandardItem *curItem){
//    //目录
//    QDir dir(parentPath);
//    if (!dir.exists()) {
//        return -1;
//    }
//    // 取到所有的文件和文件名，但是去掉.和..的文件夹（这是QT默认有的）
//    dir.setFilter(QDir::Dirs|QDir::Files|QDir::NoDotAndDotDot);

//    //文件夹优先
//    dir.setSorting(QDir::DirsFirst);

//    //转化成一个list
//    QFileInfoList list = dir.entryInfoList();
//    if(list.size()< 1 ) {
//        return -1;
//    }

//    int i=0;
//    // 顶层目录
//    do{
//        QFileInfo fileInfo = list.at(i);
//        QString filename = fileInfo.fileName();
//        QString filepath = fileInfo.filePath();
//        filepath = QDir::toNativeSeparators(filepath);
//        //如果是文件夹
//        bool bisDir = fileInfo.isDir();
//        if(bisDir) {
//            if(lay == 0){
//              q_myTreeList->addItem(lay, filename, filepath, "expander_normal.png");
//            }else{
//              q_myTreeList->addItemByParentItem(curItem, filename, filepath, "expander_normal.png");
//            }
//        }
//        i++;
//    } while(i < list.size());
//}


MainWindow::~MainWindow()
{
}

// 创建子文件夹
void MainWindow::createSubDir()
{
    QString curPath = q_myTreeList->getCurPath();
    bool hasSelRight = false;

    // 需选中 总节点和子节点
    if(!curPath.isEmpty() && curPath != "alltags") {
        hasSelRight = true;
        CreateSubDirDialog dlg(this, m_baseDir, q_myTreeList->getCurPath());
        dlg.exec();
        if(dlg.update){
            // 刷新选中的树
            QString tempPath = curPath;
            tempPath.append(QDir::separator()).append(dlg.dirName->text());

            QStandardItem* curItem = q_myTreeList->getCurItem();
            q_myTreeList->addItemByParentItem(curItem, dlg.dirName->text(), tempPath, "expander_normal.png");
            curItem->setIcon(Utils::getIcon("expander_open.png"));
            q_myTreeList->expand(q_myTreeList->getCurIndex());
        }
    }
    // 如果没有选中子目录节点
    if(!hasSelRight){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select an directory."), QMessageBox::Yes);
        return;
    }
}

// 移动文件夹
void MainWindow::moveDir()
{
    QString curPath = q_myTreeList->getCurPath();
    QStandardItem* curItem = q_myTreeList->getCurItem();
    bool hasSelRight = false;

    // 需选中 文件 子节点
    if(!curPath.isEmpty() && curPath != "alltags" && curPath != "alldocs") {
        hasSelRight = true;
        MoveToDirDialog dlg(this, m_baseDir, q_myTreeList->getCurPath());
        dlg.exec();
        if(dlg.update){
              // 取得子界面选中的path
              QString mselDir = dlg.m_curPath;
              // 删除主界面选中的节点
              curItem->parent()->removeRow(curItem->row());


              // 设置主界面的节点 (子界面新建文件夹情况下不成功)
              q_myTreeList->setCurItemByPath(mselDir);

              QString curPath = q_myTreeList->getCurPath();
              if(!curPath.isEmpty()){
                  QStandardItem* curItem = q_myTreeList->getCurItem();
                  QString temp = dlg.m_seldir;
                  temp = temp.right(temp.length() - temp.lastIndexOf(QDir::separator()) - 1);
                  q_myTreeList->addItemByParentItem(curItem, temp, dlg.m_seldir, "expander_normal.png");
                  curItem->setIcon(Utils::getIcon("expander_open.png"));
                  q_myTreeList->expand(q_myTreeList->getCurIndex());
              }
        }
    }
    // 如果没有选中子目录节点
    if(!hasSelRight){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select an directory."), QMessageBox::Yes);
        return;
    }
}


// 改变子文件夹名称
void MainWindow::renameSubDir()
{
    QString curPath = q_myTreeList->getCurPath();
    QStandardItem* curItem = q_myTreeList->getCurItem();
    QString curTitle = q_myTreeList->getCurTitle();
    bool hasSelRight = false;

    // 需选中 总节点和子节点
    if(!curPath.isEmpty() && curPath != "alltags") {
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
                QString newPath = curPath;
                QDir dir(curPath);
                newPath = newPath.left(curPath.lastIndexOf(QDir::separator())).append(QDir::separator()).append(text);
                dir.rename(curPath, newPath);
        }

    }
    // 如果没有选中子目录节点
    if(!hasSelRight){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select an directory."), QMessageBox::Yes);
        return;
    }
}

// 新建根节点
void MainWindow::createRootDir()
{
    QString curPath = q_myTreeList->getCurPath();
    bool hasSelRight = false;

    // 需选中 总节点
    if(curPath == "alldocs") {
        hasSelRight = true;
        bool ok;
        QString text = QInputDialog::getText(this, m_appName, tr("New Roor Directory name:"), QLineEdit::Normal, "", &ok);
        if (ok && !text.isEmpty()) {
                if (text == ""){
                  return;
                }
                // 刷新选中的树
                QString tempPath = m_baseDir;
                tempPath.append(QDir::separator()).append(text);

                // 新建文件夹
                QDir *mdir = new QDir(m_baseDir);
                if(mdir->exists()){
                    if(!mdir->mkdir(text)){
                        QMessageBox::warning(this, tr("Error"), tr("Create New Root Directory failed. "), QMessageBox::Yes);
                        return;
                    }
                }

                QStandardItem* curItem = q_myTreeList->getCurItem();
                q_myTreeList->addItemByParentItem(curItem, text, tempPath, "expander_normal.png");
                curItem->setIcon(Utils::getIcon("expander_open.png"));
                q_myTreeList->expand(q_myTreeList->getCurIndex());

        }
    }
    // 如果没有选中子目录节点
    if(!hasSelRight){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select an directory."), QMessageBox::Yes);
        return;
    }
}




void MainWindow::about()
{
    QMessageBox::about(this, tr("About %1").arg(windowTitle()), 
                       tr("Local file Manage Version"));
}

// 删除子文件夹
void MainWindow::delSubDir()
{
    q_myTreeList->delSubTree();
}

// 全屏
void MainWindow::fullScreen()
{
    if(m_doctable->isHidden()){
       m_doctable->show();
    }else{
       m_doctable->hide();
    }

    if(q_myTreeList->isHidden()){
       q_myTreeList->show();
    }else{
       q_myTreeList->hide();
    }
}

// 显示/隐藏分类树
void MainWindow::showClassTree()
{
    if(q_myTreeList->isHidden()){
       q_myTreeList->show();
    }else{
       q_myTreeList->hide();
    }
}
// 显示/隐藏工具栏
void MainWindow::showToolBar()
{

    if(toolBar->isHidden()){
       toolBar->show();
    }else{
       toolBar->hide();
    }
}
// 当树节点被选中
void MainWindow::treeItemActivated()
{
        QString curPath = q_myTreeList->getCurPath();
        // 如果
        if(curPath == "alldocs" ||curPath == "alltags"){
          // 表内显示所有文档

        } else{

        }
}

// 打开右键菜单
void MainWindow::treeContextMenuOpened()
{
        tableTree_currentItemChanged();
        QPoint pos = q_myTreeList->getCurPoint();
        if (contextMenu->actions().count() > 1){
           contextMenu->exec(q_myTreeList->viewport()->mapToGlobal(pos));
        }
}
// 打开右键菜单
void MainWindow::tableTree_currentItemChanged()
{
        contextMenu->clear();

        QString tcurPath = q_myTreeList->getCurPath();
        // 如果选择Root
        if(tcurPath == "alldocs"){
            contextMenu->addAction(makeRootDir);
            contextMenu->addSeparator();
            contextMenu->addAction(dirSort);
            contextMenu->addSeparator();
            contextMenu->addAction(protectRootDir);
            contextMenu->addSeparator();
            contextMenu->addAction(optionOfDir);
        } else if(tcurPath == "alltags"){
            //Tag ContextMenu
            contextMenu->addAction(makeTag);
            contextMenu->addSeparator();
            contextMenu->addAction(showSubDirTag);
            contextMenu->addAction(propOfTag);
            contextMenu->addSeparator();
        }  else if(tcurPath == "tag"){
            contextMenu->addAction(makeSubTag);
            contextMenu->addSeparator();
            contextMenu->addAction(moveToTag);
            contextMenu->addAction(moveToRootTag);
            contextMenu->addAction(delTag);
            contextMenu->addAction(renameTag);
            contextMenu->addSeparator();
            contextMenu->addAction(showSubDirTag);
            contextMenu->addSeparator();
            contextMenu->addAction(propOfTag);
        } else {
            contextMenu->addAction(makeSubDir);
            contextMenu->addSeparator();
            contextMenu->addAction(moveToDir);
            contextMenu->addAction(delDir);
            contextMenu->addAction(renameDir);
            contextMenu->addSeparator();
            contextMenu->addAction(subDirSort);
            contextMenu->addSeparator();
            contextMenu->addAction(showSubDirDoc);
            contextMenu->addAction(subDirSort);
            contextMenu->addAction(protectDir);
            contextMenu->addAction(subDirSort);
            contextMenu->addAction(propOfDir);
        }
        return;
}


void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::clearHistory()
{
    //ui.webView->page()->mainFrame()->evaluateJavaScript("clearHistory()");
    //statusBar()->showMessage(tr("History cleared"));
}
