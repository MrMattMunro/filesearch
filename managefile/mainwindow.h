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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QActionGroup>
#include <QList>
#include <QLabel>
#include <QList>
#include <QPushButton>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QSplitter>
#include <QtGui/QStatusBar>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>
#include <QSystemTrayIcon>
#include <mytreeview.h>
#include <mytableview.h>
#include <browser/tabwidget.h>
#include <browser/toolbarsearch.h>
#include <browser/bookmarks.h>
#include <browser/chasewidget.h>
#include <browser/autosaver.h>
#include <browser/webview.h>
#include <browser/downloadmanager.h>
#include <browser/networkaccessmanager.h>
#include <browser/settings.h>
#include <accountdialog.h>
#include <requtil.h>
#include <jvm.h>
#include <utils.h>
#include <db/dirdao.h>
#include "ueditor.h"

//#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~MainWindow();

    TabWidget *tabWidget() const;
    WebView *currentTab() const;
    QByteArray saveState(bool withTabs = true) const;
    bool restoreState(const QByteArray &state);

    enum SearchSet {
        ALLDOC = 1,
        CURRENTDIR = 2,
        CURRENTDIRINCLUESUB = 3,
        NAME_CONTENT = 4,
        DOC_NAME = 5,
        DOC_CONTENT = 6,
        WEBSEARCH = 7,
        OPTION = 8,
        SAVETOFASTSEARCH = 9
    };

private slots:
    void about();
    void fullScreen();
    void showClassTree();
    void showToolBar();
    void buildDocList();
    void helpDoc();
    void bbs();
    void option();
    void homepage();
    void viewLog();
    void importDlg();
    void exportDlg();

    void showAccountInfo();
    void updateToVip();
    void logoff();

    void customToolBar();
    void openDocInTab();
    void slotShowSearchSetMenu();

    void referee();

    // ËÑË÷ÉèÖÃ
    void slotOpenActionUrl(QAction *action);


    void windowToggleNoteEditor();
    void windowShowNoteEditor();
    void windowHideNoteEditor();
    void shownotes();
    void clearSelNoteUuId();
    void openUrl(QUrl url);
    void dosearch(QString keyword);
    void setSearchDir(QAction *action);
    void setSearchObject(QAction *action);
    void nextSearchCanStart();
    void checkNewVersion();

    void createTrayActions();
    void createTrayIcon();
    void messageClicked();
    void quit();

protected:
    void closeEvent(QCloseEvent *event);

private:
    QActionGroup *m_feedGroup;
    QModelIndex m_loadingIndex;

    QStringList recentDocs;
    QString m_appName;
    QString m_lang;
    QString m_baseDir;

    QSplitter * splitter;
    QToolBar *toolBar;
    MyTableView *m_doctable;
    MyTreeView *q_myTreeList;
    // ¿Õ°×ÇøÓò
    QWidget *sapcewidget;
    QAction *m_searchSetAction;

    QAction *importAction;
    QAction *exportAction;
    QAction *saveAsAction;
    QAction *saveToMobiAction;
    QAction *exitAction;
    QAction *fullScreenAction;
    QAction *showClassTreeAction;
//    QAction *skinAction;
//    QAction *defaultAction;
//    QAction *bookAction;
//    QAction *grayAction;
    QAction *customToolbarAction;
//    QAction *showSatebarAction;
    QAction *showToolbarAction;
    QAction *userBookAction;
    QAction *homepageAction;
    QAction *inviteAction;
    QAction *bbsAction;
    QAction *aboutAction;
    QAction *checkNewAction;
    QAction *optionAction;
    QAction *viewLogAction;
    QAction *pluginAction;
//    QAction *languageAction;
//    QAction *cnAction;
//    QAction *enAction;
//    QAction *jpAction;

    //QStatusBar *statusBar;
    QMenu *menu_View;
//    QMenu *menu_skin;
//    QMenu *menu_language;

    QAction *accountInfoAction;
    QAction *update2VipAction;
    QAction *logoffAction;

    QMenu *menu_File;
    QMenu *menu_Account;
    QMenu *menu_Help;
    QMenu *menu_Tool;


    void addDoc(const QString & name);
    void initUI();
    void initActions();
    void initMenus();
    void initStatusbar();
    void initToolbar();
    void initDocTableActions();
    void upateToolBar(QStringList waitItems, QStringList selItems);
    void initBrowser();

    ToolbarSearch *m_toolbarSearch;
    QMenu *m_searchSetMenu;
    BrowserMainWindow *browser;
    QDockWidget *noteEditorDW;
    AccountDialog *accoutdlg;
    bool isBusySearch;
    QString m_keyWord;
    QList<Result> resultlist;
    QList<QString> objdirList;
    QString searcheObj;


    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    UEditor *noteEditor;

};

#endif // MAINWINDOW_H

