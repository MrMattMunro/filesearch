#ifndef MYTABLEVIEW_H
#define MYTABLEVIEW_H
#endif // MYTABLEVIEW_H

#include<QTableView>
#include<QItemDelegate>
#include<QPixmap>

#include "myitemdelegate.h"
#include "mystandarditemmodel.h"

class MyTableView:public QTableView
{
public:
        MyTableView(QWidget * parent=0);
        virtual ~ MyTableView(){}
        void buildDocList(QStringList files);

protected:
        void leaveEvent (QEvent * event );
        void updateRow(int row);
        void wheelEvent(QWheelEvent * event );
        bool eventFilter(QObject* object,QEvent* event);
        void mouseMoveEvent(QMouseEvent * event);
        void resizeEvent(QResizeEvent * event);
private:
        MyItemDelegate * delegate;
        MyStandardItemModel * themodel;

};
