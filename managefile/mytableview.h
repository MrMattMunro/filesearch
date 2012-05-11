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
#include "db/docdao.h"


class MyTableView : public QTableView
{
Q_OBJECT
public:
        MyTableView(QWidget * parent=0);
        ~MyTableView(){}
        void buildDocList(QList<Doc> doclist);
        QPoint getCurPoint();               // 取得当前鼠标点击位置
        QString getCurUuid();
        void    enableMouse(bool yesOrNo);  //设置鼠标相应
        bool    getMouseStatus();   //查看是可以使用鼠标
        QString getCurFilePath();   // 取得选择文件路径

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
private slots:
       void openInSys();
       void openInTab();
       void openInSysExplore();
       void exportConvert();
       void sendMail();
       void notes();
       void showMainNotes();
       void showMainAddNoteWidget();

private:
        MyTableDelegate * delegate;
        MyTableItemModel * model;
        bool    mouseStatus;
        QPoint  curPoint;
        QString  curPath;
        QString  curUuid;

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
        QAction *propAction;

        QAction *office2pdfAction;
        QAction *pdf2officeAction;
        QAction *jpg2pdfAction;
        QAction *ppt2jpgAction;
        // doc table menu end

        NotesDialog *m_notesdlg;

        void tableContextMenuOpened();
        void initActions();
};
#endif // MYTABLEVIEW_H
