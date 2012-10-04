#ifndef ResultDELEGATE_H
#define ResultDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include "tableresult.h"
#include "db/resultdao.h"

class ResultDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ResultDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    void paintResult(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paintLetter(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

};

#endif // ResultDELEGATE_H
