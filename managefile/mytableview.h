#ifndef  _MYTABLEVIEW_H_
#define  _MYTABLEVIEW_H_


#include<QTableView>
#include<QItemDelegate>
#include<QPixmap>
#include<Qpoint>

#include <QApplication>
#include <QWidget>
#include <QStandardItem>
#include <QMouseEvent>


#include "mytabledelegate.h"
#include "mytableitemmodel.h"
#include "notesdialog.h"
#include "relatedocdialog.h"
#include "doctagsdialog.h"
#include "propofdocdialog.h"
#include "db/docdao.h"
#include "db/resultdao.h"

enum RESULT_FIELD {
    RESULT_FILE_TYPE = Qt::UserRole + 1,
    RESULT_FILE_PATH = Qt::UserRole + 2,
    RESULT_FILE_NAME = Qt::UserRole + 3,
    RESULT_DESP = Qt::UserRole +  4,
    RESULT_CONTENT = Qt::UserRole + 5,
    RESULT_SHEET_NAME = Qt::UserRole +  6,
    RESULT_ROW_NB = Qt::UserRole + 7,
    RESULT_PAGE = Qt::UserRole +  8,
    RESULT_DT_CREATED = Qt::UserRole + 9
};

enum DOC_FIELD {
    DOC_CREATE_DATE = Qt::UserRole + 1,
    DOC_MODIFIED_DATE = Qt::UserRole + 2,
    DOC_ACCESS_DATE = Qt::UserRole + 3,
    DOC_SIZE = Qt::UserRole +  4,
    DOC_AUTHOR = Qt::UserRole + 5,
    DOC_READ_COUNT = Qt::UserRole + 6,
    DOC_RELATED_COUNT = Qt::UserRole +  7,
    DOC_TAGS = Qt::UserRole +  8,
    DOC_URL = Qt::UserRole + 9,
    DOC_LOCATION = Qt::UserRole + 10,
    DOC_NOTES = Qt::UserRole + 11
};

enum TableOptionSet {
    ONE_ROW = 1,
    TWO_ROWS = 2
};

enum SecondRowOptionSet {
    CREATE_DATE = 1,
    MODIFIED_DATE = 2,
    ACCESS_DATE = 3,
    FILE_SIZE = 4,
    AUTHOR = 5,
    READ_COUNT = 6,
    RELATED_COUNT = 7,
    TAGS = 8,
    URL = 9,
    LOCATION = 10
};

class MyTableView : public QTableView
{
Q_OBJECT
public:
        MyTableView(QWidget * parent=0);
        ~MyTableView(){}

        void buildDocList(QList<Doc> doclist);
        void buildSearchResult(QList<Result> resultlist);
        QPoint getCurPoint();               // 取得当前鼠标点击位置
        QString getCurUuid();
        void    enableMouse(bool yesOrNo);  //设置鼠标相应
        bool    getMouseStatus();   //查看是可以使用鼠标
        QString getCurFilePath();   // 取得选择文件路径
        void showNoteDialog();   // 打开显示Dlg
        void secondRowSetMenu();


        QMenu *option_submenu;
        QMenu *m_secondRowSetMenu;

protected:
        void  resizeEvent(QResizeEvent * event);
        void  mouseDoubleClickEvent(QMouseEvent *event);
        void  mousePressEvent(QMouseEvent *event);
        void  changeColor(int row);     //鼠标移动事件
signals:
        //鼠标双击
        void         LBtnDbClk();
        void         shownotes();
        void         showAddNoteWidget();
        void         hideNoteWidget();
        void         reloadTagTree();
private slots:
       void openInSys();
       void openInTab();
       void openInSysExplore();
       void exportConvert();
       void sendMail();
       void notes();
       void relateDocs();
       void docTags();
       void showMainNotes();
       void showMainAddNoteWidget();
       void hideMainAddNoteWidget();
       void reloadMainTagTree();
       void selectAllDoc();
       void print();
       void moveToDir();
       void copyToDir();
       void delDoc();
       void slotShowSecondRowContent(QAction *action);
       // 设定表单第二项选项项目
       void updateSecRow(QList<int> types);
       // 设定表单选项Menu
       QString getTagNames(int row);
       void slotShowTableOption(QAction *action);
       void showToolTip(const QModelIndex &index);
       void propOfDoc();
       // 显示文档属性
       QString getAvailableField(Doc doc);
       void setShowNotesTips();

private:
        MyTableDelegate * delegate;
        MyTableItemModel * model;
        bool    mouseStatus;
        QPoint  curPoint;
        QString  curPath;
        QString  curUuid;
        QStandardItem *curItem;

        // doc table menu start
        QMenu *cmenu;
        QAction *openInSysAction;
        QAction *openInTabAction;
        QAction *openInSysExploreAction;
        QAction *exportDocAction;
        QAction *emailAsAttachAction;
        QAction *noteOfDocAction;
        QAction *relatedDocAction;
        QAction *tagAction;
        QAction *deleteAction;
        QAction *encodeAction;
        QAction *findAndReplaceAction;
        QAction *selectAllAction;
        QAction *printAction;

        QAction *advancedAction;
        QAction *convertDocAction;
        QAction *combineAction;
        QAction *restoreAction;
        QAction *pprintAction;
        QAction *pformatChangeAction;

        QAction *moveToDirAction;
        QAction *copyToDirAction;

        QAction *optionOfDocTableAction;
        QAction *oneRowAction;
        QAction *twoRowAction;
        QAction *twoRowOptionAction;
        QAction *showNotesAction;

        QAction *propAction;

        QAction *office2pdfAction;
        QAction *pdf2officeAction;
        QAction *jpg2pdfAction;
        QAction *ppt2jpgAction;
        // doc table menu end

        NotesDialog *m_notesdlg;
        RelateDocDialog *m_relatedocdlg;
        DocTagsDialog *m_doctagsdlg;
        PropOfDocDialog *m_propOfdocdlg;

        void tableContextMenuOpened();
        void initActions();
};
#endif // MYTABLEVIEW_H
