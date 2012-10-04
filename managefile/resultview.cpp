#include "resultview.h"
#include "tableresult.h"
#include "db/resultdao.h"

bool sortTableResult(const TableResult &p1, const TableResult &p2)
{
    return p1.filename() < p2.filename();
}

TableResultView::TableResultView(QWidget *parent) :
    QListView(parent)
{
    setItemDelegate(new ResultDelegate(this));
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setFrameShape(QFrame::NoFrame);
    setAttribute(Qt::WA_MacShowFocusRect, false);
    verticalScrollBar()->setPageStep(3);
    verticalScrollBar()->setSingleStep(1);

    _model = new QStandardItemModel(this);
    setModel(_model);
}

void TableResultView::setTableResult(QList<TableResult> &tableResult)
{
    setModel(NULL);
    _model->clear();

    // qSort(TableResult.begin(), TableResult.end(), sortTableResult);
    QString letter = "";
    for(int i = 0; i < tableResult.size(); i ++)
    {
        /* If letter is different than the first letter of the TableResult's surname */
        /* it means that we must change letter and so add an header to display it */
        if(letter != tableResult.at(i).filename().at(0).toLower())
        {
            letter = tableResult.at(i).filename().at(0).toLower();
            QStandardItem *item = new QStandardItem(letter);
            _model->appendRow(item);
        }

        QStandardItem *item = new QStandardItem();
        item->setData(QVariant::fromValue(tableResult.at(i)), Qt::DisplayRole);
        _model->appendRow(item);
    }

    setModel(_model);
}
