#pragma once

#ifndef MYTABLEDELEGATE_H
#define MYTABLEDELEGATE_H
#endif

#include<QItemDelegate>

class MyTableDelegate: public QItemDelegate
{
public:
        MyTableDelegate(QObject * parent=0);
        virtual ~ MyTableDelegate(){}

        void paint(QPainter * painter,
                const QStyleOptionViewItem & option,
                const QModelIndex & index) const;

        bool editorEvent(QEvent * event,
                QAbstractItemModel * model,
                const QStyleOptionViewItem & option,
                const QModelIndex & index);

        QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:

        void paintRow(QPainter * painter,
                      const QStyleOptionViewItem & option,
                      const QModelIndex & index) const;

        void paintResultHeadRow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

        void paintResultRow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

//        QPixmap docPixmap;
//        QPixmap pdfPixmap;

};
