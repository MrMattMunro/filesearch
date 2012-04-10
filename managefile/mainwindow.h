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
#include <mytreelist.h>
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

//#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~MainWindow();
    QSize sizeHint() const;

    TabWidget *tabWidget() const;
    WebView *currentTab() const;
    QByteArray saveState(bool withTabs = true) const;
    bool restoreState(const QByteArray &state);

    enum SearchSet {
        ALLDOC = 1,
        CURRENTDIR = 2,
        CURRENTDIRINCLUESUB = 3,
        ALLTEXT = 4,
        DOCNAMEONLY = 5,
        WEBSEARCH = 6,
        OPTION = 7,
        SAVETOFASTSEARCH = 8
    };

private slots:
    void about();
    void aboutQt();
    void clearHistory();
    void fullScreen();
    void showClassTree();
    void showToolBar();
    void buildDocList();
    void helpDoc();
    void bbs();
    void homepage();

    void importDlg();
    void exportDlg();
    void treeItemActivated();
    void treeContextMenuOpened();
    void tableTree_currentItemChanged();
    void createSubDir();
    void delSubDir();
    void renameSubDir();
    void createRootDir();
    void moveDir();
    void setShowSubDirDoc();
    void setShowSubTagDoc();
    void properties();

    void loadPage(const QString &url);
    void newTag();
    void deleteTag();
    void showPropOfTag();
    void renameSubTag();
    void moveToRoot();
    void movetoTag();
    void slotHome();

    void customToolBar();
    // doc table start
    void openDocInTab();
    // doc table end
    // browser start
    void save();

    void slotLoadProgress(int);
    void slotUpdateStatusbar(const QString &string);
    void slotUpdateWindowTitle(const QString &title = QString());

    void loadUrl(const QUrl &url);
    void slotPreferences();

    void slotFileNew();
    void slotFileOpen();
    void slotFilePrintPreview();
    void slotFilePrint();
    void slotPrivateBrowsing();
    void slotFileSaveAs();
    void slotEditFind();
    void slotEditFindNext();
    void slotEditFindPrevious();
    void slotShowBookmarksDialog();
    void slotAddBookmark();
    void slotViewZoomIn();
    void slotViewZoomOut();
    void slotViewResetZoom();
    void slotViewZoomTextOnly(bool enable);
    void slotViewToolbar();
    void slotViewBookmarksBar();
    void slotViewStatusbar();
    void slotViewPageSource();
    void slotViewFullScreen(bool enable);

    void slotWebSearch();
    void slotToggleInspector(bool enable);
    void slotAboutApplication();
    void slotDownloadManager();
    void slotSelectLineEdit();

    void slotAboutToShowBackMenu();
    void slotAboutToShowForwardMenu();
    void slotAboutToShowWindowMenu();
    void slotOpenActionUrl(QAction *action);
    void slotShowWindow();
    void slotSwapFocus();

    void printRequested(QWebFrame *frame);
    void geometryChangeRequested(const QRect &geometry);
    void updateToolbarActionText(bool visible);
    void updateBookmarksToolbarActionText(bool visible);
    void slotShowSearchSetMenu();
    //void resizeSpace();
    //browser end

protected:
    void closeEvent(QCloseEvent *event);

private:
    QActionGroup *m_feedGroup;
    QModelIndex m_loadingIndex;

    QStringList recentDocs;
    QString m_appName;
    QString m_lang;
    QString m_baseDir;
    // 是否显示文件夹下文件
    bool isShowDocUnderSub;
    bool isShowDocUnderTag;

    QSplitter * splitter;
    QToolBar *toolBar;
    MyTableView *m_doctable;
    myTreeList *q_myTreeList;
    // 空白区域
    QWidget *sapcewidget;
    QAction *m_searchSetAction;

    QAction *importAction;
    QAction *exportAction;
    QAction *saveAsAction;
    QAction *saveToMobiAction;
    QAction *exitAction;
    QAction *fullScreenAction;
    QAction *showClassTreeAction;
    QAction *skinAction;
    QAction *defaultAction;
    QAction *bookAction;
    QAction *grayAction;
    QAction *customToolbarAction;
    QAction *showSatebarAction;
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
    QAction *languageAction;
    QAction *cnAction;
    QAction *enAction;
    QAction *jpAction;

    //Doc ContextMenu
    QAction *makeSubDir;
    QAction *moveToDir;
    QAction *delDir;
    QAction *renameDir;
    QAction *subDirSort;
    QAction *showSubDirDoc;
    QAction *protectDir;
    QAction *propOfDir;

    //Root ContextMenu
    QAction *makeRootDir;
    QAction *dirSort;
    QAction *protectRootDir;
    QAction *optionOfDir;

    //Tag ContextMenu
    QAction *makeSubTag;
    QAction *moveToTag;
    QAction *moveToRootTag;
    QAction *delTag;
    QAction *renameTag;
    QAction *showSubDirTag;
    QAction *propOfTag;

    //Root Tag ContextMenu
    QAction *makeTag;

    //QStatusBar *statusBar;
    QMenu *menu_View;
    QMenu *menu_skin;
    QMenu *menu_language;
    QMenu *menu_File;
    QMenu *menu_Help;
    QMenu *menu_Tool;
    QMenu *contextMenu;
    QMenu *tablecontextMenu;

    void addDoc(const QString & name);
    void initUI();
    void initActions();
    void initMenus();
    void initStatusbar();
    void initToolbar();
    void initDocTableActions();
    void upateToolBar(QStringList waitItems, QStringList selItems);
    void initBrowser();

    // browser start
    void loadDefaultState();
    void setupMenu();
    void setupToolBar();
    void updateStatusbarActionText(bool visible);

    QToolBar *m_navigationBar;
    ToolbarSearch *m_toolbarSearch;
    BookmarksToolBar *m_bookmarksToolbar;
    ChaseWidget *m_chaseWidget;
    TabWidget *m_tabWidget;
    AutoSaver *m_autoSaver;

    QAction *m_historyBack;
    QMenu *m_historyBackMenu;
    QAction *m_historyForward;
    QMenu *m_historyForwardMenu;
    QMenu *m_windowMenu;
    QMenu *m_searchSetMenu;

    QAction *m_stop;
    QAction *m_reload;
    QAction *m_stopReload;
    QAction *m_viewToolbar;
    QAction *m_viewBookmarkBar;
    QAction *m_viewStatusbar;
    QAction *m_restoreLastSession;
    QAction *m_addBookmark;

    QIcon m_reloadIcon;
    QIcon m_stopIcon;

    QString m_lastSearch;
    // browser end

};

#endif // MAINWINDOW_H

