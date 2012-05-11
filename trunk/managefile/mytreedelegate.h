#ifndef MYTREEDELEGATE_H
#define MYTREEDELEGATE_H
#endif

#include<QStyledItemDelegate>


class MyTreeDelegate: public QStyledItemDelegate
{
public:
        MyTreeDelegate(QObject * parent=0);
        virtual ~ MyTreeDelegate(){}

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
