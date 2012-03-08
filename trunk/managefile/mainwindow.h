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

//#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~MainWindow();

    struct FeedInfo {
        QString name;
        QUrl uri;
        QString query;
        QString embedDiv;
        QString titleFilter;
    };
    FeedInfo currentFeedInfo() const;

private slots:
    void about();
    void aboutQt();
    void clearHistory();
    void enableFindButton(const QString & name);
    void findClicked();
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

private:
    QActionGroup *m_feedGroup;
    QModelIndex m_loadingIndex;

    QStringList recentDocs;
    QString m_appName;
    QString m_lang;
    QString m_baseDir;
    bool isShowDocUnderSub;

    void populateFeedsMenu();


    //Ui::MainWindow ui;
    QSplitter * splitter;
    QToolBar *toolBar;
    QWebView *m_view;
    MyTableView *m_doctable;
    myTreeList *q_myTreeList;

    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *findButton;


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

    QStatusBar *statusBar;
    QMenu *menu_View;
    QMenu *menu_skin;
    QMenu *menu_language;
    QMenu *menu_File;
    QMenu *menu_Help;
    QMenu *menu_Tool;
    QMenu *contextMenu;

    QStandardItemModel *m_rssModel;

    void addDoc(const QString & name);
    void initUI();
    void initActions();
    void initMenus();
    void initStatusbar();
    void initToolbar();

    enum {
        TitleRole = Qt::UserRole + 1,
        AuthorRole,
        DescriptionRole,
        SubTitleRole,
        PageLinkRole,
        DownloadRole,
        PublishedDateRole,
        DurationRole,
        SearchRole
    };
};

Q_DECLARE_METATYPE(MainWindow::FeedInfo);

#endif // MAINWINDOW_H

