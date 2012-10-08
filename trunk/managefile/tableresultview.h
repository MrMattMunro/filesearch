#ifndef TableResultVIEW_H
#define TableResultVIEW_H

#include <QListView>
#include <QStandardItemModel>
#include <QScrollBar>

#include "tableresult.h"
#include "resultdelegate.h"

class TableResultView : public QListView
{
    Q_OBJECT
public:
    explicit TableResultView(QWidget *parent = 0);

    void setTableResult(QList<TableResult> &TableResult);

private:
    QStandardItemModel *_model;
};

#endif // TableResultVIEW_H
