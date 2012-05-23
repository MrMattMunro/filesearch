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
#include "db/docdao.h"


class MyTableView : public QTableView
{
Q_OBJECT
public:
        MyTableView(QWidget * parent=0);
        ~MyTableView(){}
        enum TableOptionSet {
            ONE_ROW = 1,
            TWO_ROWS = 2,
            SHOW_NOTES = 3
        };

        enum SecondRowOptionSet {
            CREATE_DATE = 1,
            MODIFIED_DATE = 2,
            ACCESS_DATE = 3,
            SIZE = 4,
            AUTHOR = 5,
            READ_COUNT = 6,
            RELATED_COUNT = 7,
            TAGS = 8,
            URL = 9
        };


        void buildDocList(QList<Doc> doclist);
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
        void  leaveEvent (QEvent * event );
        void  updateRow(int row);
        void  wheelEvent(QWheelEvent * event );
        bool  eventFilter(QObject* object,QEvent* event);
        void  mouseMoveEvent(QMouseEvent * event);

        void  resizeEvent(QResizeEvent * event);

        void  mouseDoubleClickEvent(QMouseEvent *event);
        void  mousePressEvent(QMouseEvent *event);
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
       void slotShowTableOption(QAction *action);

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

        void tableContextMenuOpened();
        void initActions();
};
#endif // MYTABLEVIEW_H
