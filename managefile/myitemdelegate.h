#ifndef MYITEMDELEGATE_H
#define MYITEMDELEGATE_H
#endif

#include<QItemDelegate>

class MyItemDelegate:public QItemDelegate
{
public:
        MyItemDelegate(QObject * parent=0);
        virtual ~ MyItemDelegate(){}

        void paint(QPainter * painter,
                const QStyleOptionViewItem & option,
                const QModelIndex & index) const;
        bool editorEvent(QEvent * event,
                QAbstractItemModel * model,
                const QStyleOptionViewItem & option,
                const QModelIndex & index);
private:
//        QPixmap docPixmap;
//        QPixmap pdfPixmap;

};
