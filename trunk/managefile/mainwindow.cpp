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
#include "mytreeview.h"

#include "customtooldialog.h"


#include "browser/browsermainwindow.h"
#include "browser/browserapplication.h"
#include "utils.h"
#include "fileutils.h"
#include "db/tagdao.h"
#include "db/dirdao.h"
#include "db/docdao.h"
#include "db/doctagdao.h"
#include "noteeditor.h"
#include "logview.h"
#include "preferencesdialog.h"

extern NoteEditor *noteEditor;

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    initUI();
    initActions();
    initMenus();
    initStatusbar();
    initToolbar();

    m_appName = tr("Local File Manage");
    setContextMenuPolicy(Qt::CustomContextMenu);
}

// 生成文档列表
void MainWindow::buildDocList()
{
    QString curUuid = q_myTreeList->getCurUuid();
    QString curType = q_myTreeList->getCurType();
    if(curType != "doc" && curType != "basket" && curType != "tag" ){
        return;
    }

    // 显示Tag下所有的文件
    Preferences* p = Preferences::instance();
    bool isShowDocUnderSub = p->isShowDocUnderSub();

    // 是否显示子文件夹文档
    QList<Doc> docs;
    // 显示所有垃圾桶的文件
    if(curType == "basket" ){
        if(isShowDocUnderSub){
              // 取得所有文件夹
              QList<Dir> dirs ;
              DirDao::selectAllSubDirbyDir(dirs, curUuid, "1");
              // 根据文件夹取得所有文件
              for(int i = 0 ; i< dirs.size(); i ++){
                 Dir dir = dirs.at(i);
                 docs.append(DocDao::selectDocsbyDir(dir.DIR_GUID, "1"));
              }
              // 取不到被删除的文件夹时,平行地取出所有文件
              if(dirs.size() == 0){
                  docs = DocDao::selectDocsByDelFlg("1");
              }
        }else{
             docs = DocDao::selectDocsbyDir(curUuid,  "1");
        }
        m_doctable->buildDocList(docs);
        return;
    }

    if(curType == "tag" ){
        // 传递选择的docUuid
        if(isShowDocUnderSub){
              // 取得所有子标签
              QList<Tag> tags ;
              TagDao::selectAllSubTagbyTag(tags, curUuid);
              // 根据文件夹取得所有文件
              for(int i = 0 ; i< tags.size(); i ++){
                 Tag tag = tags.at(i);
                 docs.append(DocDao::selectDocsByTag(tag));
              }
        }else{
            Tag tag;
            tag.TAG_GUID = curUuid;
            docs = DocDao::selectDocsByTag(tag);
        }
        m_doctable->buildDocList(docs);
        return;
    }

    if(curType == "doc" ){
        if(isShowDocUnderSub){
              // 取得所有文件夹
              QList<Dir> dirs ;
              DirDao::selectAllSubDirbyDir(dirs, curUuid, "0");
              // 根据文件夹取得所有文件
              for(int i = 0 ; i< dirs.size(); i ++){
                 Dir dir = dirs.at(i);
                 docs.append(DocDao::selectDocsbyDir(dir.DIR_GUID, "0"));
              }
        }else{
             docs = DocDao::selectDocsbyDir(curUuid,  "0");
        }
        m_doctable->buildDocList(docs);
   }
}

// 搜索界面设置Menu
void MainWindow::slotShowSearchSetMenu()
{
    if(m_searchSetMenu->children().length() > 2){
      return;
    }

    // 设置Menu
    QAction *action1 = new QAction(this);
    action1->setData(ALLDOC);
    action1->setCheckable(true);
    action1->setText(tr("ALL Documents"));

    // 设置Menu
    QAction *action2 = new QAction(this);
    action2->setData(CURRENTDIR);
    action2->setCheckable(true);
    action2->setText(tr("Current Directory"));

    // 设置Menu
    QAction *action3 = new QAction(this);
    action3->setData(CURRENTDIRINCLUESUB);
    action3->setCheckable(true);
    action3->setText(tr("Current Directory(Include Sub Directory)"));

    // 设置Menu
    QAction *action4 = new QAction(this);
    action4->setData(ALLTEXT);
    action4->setCheckable(true);
    action4->setText(tr("ALL Text"));

    QAction *action5 = new QAction(this);
    action5->setData(DOCNAMEONLY);
    action5->setCheckable(true);
    action5->setText(tr("Document Name Only"));

    QAction *action6 = new QAction(this);
    action6->setData(WEBSEARCH);
    action6->setCheckable(true);
    action6->setText(tr("Web Search"));

    QAction *action7 = new QAction(this);
    action7->setData(OPTION);
    action7->setCheckable(true);
    action7->setText(tr("Option"));

    QAction *action8 = new QAction(this);
    action8->setData(SAVETOFASTSEARCH);
    action8->setCheckable(true);
    action8->setText(tr("Save To Fast Search"));

    m_searchSetMenu->addAction(action1);
    m_searchSetMenu->addAction(action2);
    m_searchSetMenu->addAction(action3);
    m_searchSetMenu->addSeparator();
    m_searchSetMenu->addAction(action4);
    m_searchSetMenu->addAction(action5);
    m_searchSetMenu->addSeparator();
    m_searchSetMenu->addAction(action6);
    m_searchSetMenu->addSeparator();
    m_searchSetMenu->addAction(action7);
    m_searchSetMenu->addAction(action8);
}

// 初始化界面动作
void MainWindow::initActions()
{

        // 设置搜索面板
        m_searchSetAction = new QAction(tr("Search"), this);
        m_searchSetAction->setIconVisibleInMenu(false);
        m_searchSetMenu = new QMenu(this);
        m_searchSetAction->setMenu(m_searchSetMenu);
        connect(m_searchSetMenu, SIGNAL(aboutToShow()), this, SLOT(slotShowSearchSetMenu()));
        connect(m_searchSetMenu, SIGNAL(triggered(QAction*)),this, SLOT(slotOpenActionUrl(QAction*)));

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
        connect(saveToMobiAction, SIGNAL(triggered()), this, SLOT(exportDlg()));

        // 退出
        exitAction = new QAction(Utils::getIcon("close.png"),tr("&Exit"), this);
        exitAction->setShortcut(tr("Ctrl+Q"));
        connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

        // 全屏
        fullScreenAction = new QAction(Utils::getIcon("view_fullscreen.png"),tr("&Full Screen"), this);
        connect(fullScreenAction, SIGNAL(triggered()), this, SLOT(fullScreen()));

        // 显示/隐藏分类树
        showClassTreeAction = new QAction(Utils::getIcon("view_tree.png"),tr("&Show/Hide Class Tree"), this);
        showClassTreeAction->setShortcut(tr("Ctrl+H"));
        connect(showClassTreeAction, SIGNAL(triggered()), this, SLOT(showClassTree()));

//        // 皮肤
//        skinAction = new QAction(Utils::getIcon("skins.png"),tr("&Skin"), this);
//        menu_skin = new QMenu(this);
//        skinAction->setMenu(menu_skin);

//        //皮肤 默认
//        defaultAction = new QAction(tr("&Defaut"), this);
//        connect(defaultAction, SIGNAL(triggered()), this, SLOT(about()));

//       // 皮肤 书香
//        bookAction = new QAction(tr("&Book"), this);
//        connect(bookAction, SIGNAL(triggered()), this, SLOT(about()));

//        //皮肤 灰色
//        grayAction = new QAction(tr("&Gray"), this);
//        connect(grayAction, SIGNAL(triggered()), this, SLOT(about()));

        // 自定义工具栏
        customToolbarAction = new QAction(Utils::getIcon("toolbar.png"),tr("&Setting ToolBar"), this);
        connect(customToolbarAction, SIGNAL(triggered()), this, SLOT(customToolBar()));

        // 显示/隐藏工具栏
        showToolbarAction = new QAction(Utils::getIcon("status_bar.png"),tr("&Show/Hide Tool Bar"), this);
        connect(showToolbarAction, SIGNAL(triggered()), this, SLOT(showToolBar()));

//        // 显示/隐藏状态栏
//        showSatebarAction = new QAction(Utils::getIcon("status_bar.png"),tr("&Show/Hide Status Bar..."), this);
//        connect(showSatebarAction, SIGNAL(triggered()), this, SLOT(about()));

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
        connect(optionAction, SIGNAL(triggered()), this, SLOT(option()));

        // 查看log
        viewLogAction = new QAction(Utils::getIcon("log.png"),tr("&View Log..."), this);
        viewLogAction->setShortcut(tr("Ctrl+L"));
        connect(viewLogAction, SIGNAL(triggered()), this, SLOT(viewLog()));

        // 插件管理
        pluginAction = new QAction(Utils::getIcon("plugin.png"),tr("Plugins"), this);
        pluginAction->setShortcut(tr("Ctrl+P"));
        connect(pluginAction, SIGNAL(triggered()), this, SLOT(about()));;

        // 账户信息
        accountInfoAction = new QAction(Utils::getIcon("my_account.ico"),tr("Account Information"), this);
        connect(accountInfoAction, SIGNAL(triggered()), this, SLOT(showAccountInfo()));;

        // 升级到VIP
        update2VipAction = new QAction(Utils::getIcon("vip.png"),tr("Update to VIP"), this);
        connect(update2VipAction, SIGNAL(triggered()), this, SLOT(updateToVip()));;

        // 注销
        logoffAction = new QAction(Utils::getIcon("logo_off.png"),tr("Logo Off"), this);
        connect(logoffAction, SIGNAL(triggered()), this, SLOT(logoff()));;

//        // 语言
//        languageAction = new QAction(Utils::getIcon("language.png"),tr("&Language"), this);
//        menu_language = new QMenu(this);
//        languageAction->setMenu(menu_language);

//        // 英文版
//        enAction = new QAction(tr("&English"), this);
//        connect(enAction, SIGNAL(triggered()), this, SLOT(about()));

//        // 中文版
//        cnAction = new QAction(tr("&Chinese"), this);
//        connect(cnAction, SIGNAL(triggered()), this, SLOT(about()));

//        // 日文版
//        jpAction = new QAction(tr("&Japanese"), this);
//        connect(jpAction, SIGNAL(triggered()), this, SLOT(about()));


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

//        menu_View->addAction(skinAction);
//        menu_skin->addAction(defaultAction);
//        menu_skin->addAction(bookAction);
//        menu_skin->addAction(grayAction);
//        menu_View->addAction(menu_skin->menuAction());

//        menu_View->addAction(languageAction);
//        menu_language->addAction(cnAction);
//        menu_language->addAction(enAction);
//        menu_language->addAction(jpAction);
//        menu_View->addAction(menu_language->menuAction());

//        menu_View->addSeparator();
//        menu_View->addAction(showSatebarAction);
        menu_View->addSeparator();
        menu_View->addAction(customToolbarAction);

        menu_Tool =  menuBar()->addMenu(tr("&Tool"));
        menu_Tool->addAction(optionAction);
        menu_Tool->addSeparator();
        menu_Tool->addAction(viewLogAction);
        menu_Tool->addSeparator();
        menu_Tool->addAction(pluginAction);

        menu_Account =  menuBar()->addMenu(tr("&Account"));
        menu_Account->addAction(accountInfoAction);
        menu_Account->addSeparator();
        menu_Account->addAction(update2VipAction);
        menu_Account->addSeparator();
        menu_Account->addAction(logoffAction);
        menu_Account->addSeparator();


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


}

// 状态栏
void MainWindow::initStatusbar()
{
  // QLabel* m_sqliteVersionLabel = new QLabel(this);
  //statusBar()->addPermanentWidget(&m_sqliteVersionLabel);
}

// 工具栏
void MainWindow::initToolbar()
{
    // 读取preferences
    Preferences* p = Preferences::instance();
    QStringList waitItems = p->getWaitToolbarItemList();
    QStringList selItems = p->getSelToolbarItemList();

    toolBar = addToolBar(tr("Tool Bar"));
    if(selItems.length() != 0){
        upateToolBar(waitItems, selItems);
    }else{
        // 默认状态下
        toolBar->addAction(showClassTreeAction);
        toolBar->addSeparator();
        toolBar->addAction(homepageAction);
        toolBar->addAction(inviteAction);
        toolBar->addAction(bbsAction);
        toolBar->addSeparator();
    }

    // 空白区域
    QWidget *twidget = new QWidget(this);
    twidget->setMinimumWidth(this->geometry().width() * 0.1);
    toolBar->addWidget(twidget);

    m_toolbarSearch = new ToolbarSearch();
    connect(m_toolbarSearch, SIGNAL(search(QUrl)), SLOT(loadUrl(QUrl)));

    toolBar->addWidget(m_toolbarSearch);
    toolBar->addAction(m_searchSetAction);
    toolBar->addSeparator();
    toolBar->addAction(fullScreenAction);

    // 空白区域
    sapcewidget = new QWidget(this);
    sapcewidget->setMinimumWidth(m_doctable->width()*1.2);
    toolBar->addWidget(sapcewidget);
}

// 用户手册
void MainWindow::helpDoc()
{
    browser->loadPage("http://www.slfile.net/?page_id=58");
}

// 论坛
void MainWindow::bbs()
{
    browser->loadPage("http://www.slfile.net/?post_type=forum");
}

// 选项
void MainWindow::option()
{
    // curPath 用于判断根节点和子节点
    PreferencesDialog dlg(this);
    dlg.exec();
}

// 主页
void MainWindow::homepage()
{
    browser->loadPage("http://www.slfile.net/");
}

// 查看Log文件
void MainWindow::viewLog()
{
    LogView dlg(this);
    dlg.exec();
}

void MainWindow::initUI()
{
        setWindowTitle(m_appName);

        splitter = new QSplitter(this);
        // 加载分类树
        m_baseDir = Utils::getLocatePath();
        m_baseDir = QDir::toNativeSeparators(m_baseDir);
        q_myTreeList = new MyTreeView("all", this);

        // 空的UuId
        q_myTreeList->enableMouse(true);

        m_doctable = new MyTableView(this);

        splitter->addWidget(q_myTreeList);
        splitter->addWidget(m_doctable);

        BrowserApplication* applcation = BrowserApplication::instance();
        browser = applcation->newMainWindow(splitter);

        splitter->addWidget(browser);
        browser->hide();
        browser->setMaximumWidth(0);
        browser->setMinimumWidth(0);

        connect(browser, SIGNAL(testsingal()), this, SLOT(resizeSpace()));

        connect(q_myTreeList, SIGNAL(LBtnClk()), this, SLOT(buildDocList()));

        // 后期需要调用主界面的动作
        connect(m_doctable, SIGNAL(LBtnDbClk()), this, SLOT(openDocInTab()));
        connect(m_doctable, SIGNAL(showAddNoteWidget()), this, SLOT(windowToggleNoteEditor()));
        connect(m_doctable, SIGNAL(hideNoteWidget()), this, SLOT(windowHideNoteEditor()));
        connect(m_doctable, SIGNAL(reloadTagTree()), q_myTreeList, SLOT(reloadTagTree()));


        // Dock widgets ///////////////////////////////////////////////
        //QDockWidget *dw;
        //if (settings.value("/satellite/noteeditor/isDockWindow",true).toBool())
        //{
            noteEditorDW = new QDockWidget(tr("Note Editor"), this);
            noteEditorDW->setWidget (noteEditor);
            noteEditorDW->setObjectName ("NoteEditor");
            addDockWidget(Qt::RightDockWidgetArea, noteEditorDW);
            noteEditorDW->hide();
            noteEditor->setShowWithMain(true);
            // 从Note编辑界面打开Note
            connect(noteEditor, SIGNAL(showMainNotes()), this, SLOT(shownotes()));

        //} else{
          //  noteEditorDW=NULL;
        //}


        setCentralWidget(splitter);
}

void MainWindow::shownotes(){
    m_doctable->showNoteDialog();
}


MainWindow::~MainWindow()
{
    Preferences::deleteInstance();
}

void MainWindow::closeEvent(QCloseEvent * e)
{
     Preferences::deleteInstance();
}

// 自定义工具栏
void MainWindow::customToolBar()
{
    CustomToolDialog dlg(this);
    dlg.exec();
    if(dlg.update){
        // 更新工具栏
        upateToolBar(dlg.waitItems, dlg.sellItems);
    }
}
// 更新工具栏
void MainWindow::upateToolBar(QStringList waitItems, QStringList selItems)
{

    QList<QAction*> actions = toolBar->actions();

    // 分类树
    if(selItems.contains("view_tree.png") && ! waitItems.contains("view_tree.png")){
        if(!actions.contains(showClassTreeAction)){
             toolBar->addAction(showClassTreeAction);
        }
    }
    if(! selItems.contains("view_tree.png") && waitItems.contains("view_tree.png")){
         if(actions.contains(showClassTreeAction)){
             toolBar->removeAction(showClassTreeAction);
         }
    }
    // 全屏
    if(selItems.contains("view_fullscreen.png") && ! waitItems.contains("view_fullscreen.png")){
          if(!actions.contains(fullScreenAction)){
               toolBar->addAction(fullScreenAction);
          }
    }
    if(! selItems.contains("view_fullscreen.png") && waitItems.contains("view_fullscreen.png")){
          if(actions.contains(fullScreenAction)){
            toolBar->removeAction(fullScreenAction);
          }
    }
    // 个人主页
    if(selItems.contains("homepage.png") && ! waitItems.contains("homepage.png")){
          if(!actions.contains(homepageAction)){
             toolBar->addAction(homepageAction);
          }
    }
    if(! selItems.contains("homepage.png") && waitItems.contains("homepage.png")){
          if(actions.contains(homepageAction)){
             toolBar->removeAction(homepageAction);
          }
    }
    // 邀请朋友
    if(selItems.contains("invite.png") && ! waitItems.contains("invite.png")){
          if(!actions.contains(inviteAction)){
             toolBar->addAction(inviteAction);
          }
    }
    if(! selItems.contains("invite.png") && waitItems.contains("invite.png")){
         if(actions.contains(inviteAction)){
             toolBar->removeAction(inviteAction);
         }
    }
    // 论坛
    if(selItems.contains("forum.png") && ! waitItems.contains("forum.png")){
         if(!actions.contains(bbsAction)){
             toolBar->addAction(bbsAction);
         }
    }
    if(!selItems.contains("forum.png") && waitItems.contains("forum.png")){
          if(actions.contains(bbsAction)){
              toolBar->removeAction(bbsAction);
          }
    }
    // 另存到移动设备
    if(selItems.contains("document-savetomobi.png") && ! waitItems.contains("document-savetomobi.png")){
            if(!actions.contains(saveToMobiAction)){
               toolBar->addAction(saveToMobiAction);
            }
    }
    if(! selItems.contains("document-savetomobi.png") && waitItems.contains("document-savetomobi.png")){
           if(actions.contains(saveToMobiAction)){
               toolBar->removeAction(saveToMobiAction);
           }
    }
    //  导入
    if(selItems.contains("document-import.png") && ! waitItems.contains("document-import.png")){
          if(!actions.contains(importAction)){
             toolBar->addAction(importAction);
          }
    }
    if(! selItems.contains("document-import.png") && waitItems.contains("document-import.png")){
          if(actions.contains(importAction)){
             toolBar->removeAction(importAction);
          }
    }
    //  导出
    if(selItems.contains("document-export.png") && ! waitItems.contains("document-export.png")){
           if(!actions.contains(exportAction)){
              toolBar->addAction(exportAction);
           }
    }
    if(! selItems.contains("document-export.png") && waitItems.contains("document-export.png")){
           if(actions.contains(exportAction)){
             toolBar->removeAction(exportAction);
           }
    }
    // 插件管理
    if(selItems.contains("plugin.png") && ! waitItems.contains("plugin.png")){
         if(!actions.contains(pluginAction)){
               toolBar->addAction(pluginAction);
          }
    }
    if(! selItems.contains("plugin.png") && waitItems.contains("plugin.png")){
         if(actions.contains(pluginAction)){
             toolBar->removeAction(pluginAction);
          }
    }
    toolBar->update();
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About %1").arg(windowTitle()), 
                       tr("Sorry, The function is under construction..."));
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
// 打开导入界面
void MainWindow::importDlg()
{
    q_myTreeList->showImportDlg();
}

// 打开导出界面
void MainWindow::exportDlg()
{
   q_myTreeList->showExportDlg();
}

// 显示账户信息
void MainWindow::showAccountInfo(){
    accoutdlg = new AccountDialog(this);
    connect(accoutdlg, SIGNAL(updateVip()), this, SLOT(updateToVip()));;
    accoutdlg->exec();
}
// 升级到VIP
void MainWindow::updateToVip(){
  // 打开升级到VIP账号
  browser->loadPage("http://www.slfile.net/?page_id=115");
}
// 注销
void MainWindow::logoff(){
    // 改变NoteEditor的属性
    Preferences* p = Preferences::instance();
    p->setUserName("");
    p->setUserEmail("");
    p->setDisplayName("");
    p->setScore("");
    p->setDtExpired("");
    p->setType("");
    p->setLastOpenDocs("");
    // 重新启动
    QCoreApplication::exit(773);
}

// 搜索设置
void MainWindow::slotOpenActionUrl(QAction *action)
{
    int offset = action->data().toInt();

    if(action->isChecked()){
       action->setChecked(true);
    }else{
       action->setChecked(false);
    }

    switch (offset) {
        case ALLDOC:

        case CURRENTDIR:

        case CURRENTDIRINCLUESUB:

        case ALLTEXT:

        case DOCNAMEONLY:
        case OPTION:

        case SAVETOFASTSEARCH:
          ;
    }
 }

void MainWindow::windowToggleNoteEditor()
{
    // 改变NoteEditor的属性
    Preferences* p = Preferences::instance();
    QString docUuid = p->getSelDocUid();

    Doc doc = DocDao::selectDoc(docUuid);
    noteEditorDW->setWindowTitle(doc.DOCUMENT_NAME);
    noteEditorDW->setWindowIcon(Utils::getIcon("note.png"));

    QString selNoteUid = p->getSelNoteUid();
    // 如果为空则是 清空Reset
    if(selNoteUid.isEmpty()){
       noteEditor->reset();
    }else{
        QString notesPath = Utils::getLocateNotesPath();
        QString filename = notesPath.append(QDir::separator());
        filename.append(QDir::separator());
        filename.append(selNoteUid);
        filename.append(".html");
        // load noteUuid
        QFile f( filename );
        if ( !f.open( QIODevice::ReadOnly ) ){
              return;
        }
        QTextStream ts( &f );
        noteEditor->setText(ts.readAll());
        noteEditor->setFilename(filename);
    }
    windowShowNoteEditor();
}

void MainWindow::windowShowNoteEditor()
{
    noteEditor->setShowWithMain(true);
    noteEditor->show();
    noteEditorDW->show();

    m_doctable->hide();
    q_myTreeList->hide();
}

void MainWindow::windowHideNoteEditor()
{
    noteEditor->setShowWithMain(false);
    noteEditor->hide();
    noteEditorDW->hide();

    m_doctable->show();
    q_myTreeList->show();
}


//void MainWindow::geometryChangeRequested(const QRect &geometry)
//{
//    setGeometry(geometry);
//}
// 以tab页打开Doc
void MainWindow::openDocInTab()
{
    QString filepath = m_doctable->getCurFilePath();

    //m_tabWidget->currentLineEdit()->setText(filepath);

//    SqlEditorWidget
    // 改变NoteEditor的属性
    Preferences* p = Preferences::instance();
    QString suffix = FileUtils::suffix(filepath);
    if(p->sources().contains(suffix.toLower())){
            browser->openTxtInTab(filepath);
        //m_tabWidget->newTxtTab(true, filepath);
       // m_tabWidget->loadDocInCurrentTab(filepath);
    }else{
   browser->openDocInTab(filepath);
        //m_tabWidget->newDocTab(true, filepath);
        //m_tabWidget->loadDocInCurrentTab(filepath);
    }
}




