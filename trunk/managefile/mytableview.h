#ifndef MYTABLEVIEW_H
#define MYTABLEVIEW_H
#endif // MYTABLEVIEW_H

#include<QTableView>
#include<QItemDelegate>
#include<QPixmap>
#include<Qpoint>


#include "myitemdelegate.h"
#include "mystandarditemmodel.h"

class MyTableView : public QTableView
{
public:
        MyTableView(QWidget * parent=0);
        virtual ~ MyTableView(){}
        void buildDocList(QStringList files);
        QPoint getCurPoint();
        void    enableMouse(bool yesOrNo);  //设置鼠标相应
        bool    getMouseStatus();   //查看是可以使用鼠标

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
        void         LBtn_DbClk();
        //鼠标单击
        void         LBtn_Clk();
        //选中某个Item
        void         RBtn_Clk();
private:
        MyItemDelegate * delegate;
        MyStandardItemModel * themodel;
        bool    mouseStatus;
        QPoint  curPoint;

};
