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
        void buildDocList(QString datpath);

//        static const int wordItemType = Qt::UserRole + 2;
//        static const int excelItemType = Qt::UserRole + 3;
//        static const int pptItemType = Qt::UserRole + 4;
//        static const int pdfItemType = Qt::UserRole + 5;
//        static const int txtItemType = Qt::UserRole + 6;
//        static const int javaItemType = Qt::UserRole + 7;
//        static const int cplusItemType = Qt::UserRole + 8;
//        static const int jsItemType = Qt::UserRole + 9;
//        static const int picItemType = Qt::UserRole + 10;
//        static const int movieItemType = Qt::UserRole + 11;
//        static const int htmlItemType = Qt::UserRole + 12;
//        static const int swfItemType = Qt::UserRole + 13;
//        static const int sourceItemType = Qt::UserRole + 14;
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
