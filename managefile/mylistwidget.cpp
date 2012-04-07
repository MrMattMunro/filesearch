#include "mylistwidget.h"

MyListWidget::MyListWidget(QWidget * parent): QWidget(parent)
{
    fileName = new QLabel;
    //fileName->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    listWidget = new ListWidget(parent);
    listWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    listWidget->setViewMode(QListView::IconMode);

    // QObject::connect(listWidget, SIGNAL(itemSelectionChanged ()), this, SLOT(on_itemSelectionChanged() ));

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(fileName);
    vLayout->addWidget(listWidget);

    // vLayout->addStretch();
    this->setLayout(vLayout);
}

void MyListWidget::setFileName(QString text)
{
    fileName->setText(text);
}

void MyListWidget::addItem(QListWidgetItem *item)
{
    listWidget->addItem(item);
    listWidget->update();
}

QList<QListWidgetItem*> MyListWidget::getAllItems()
{
    return listWidget->getAllItems();
}

void MyListWidget::on_itemSelectionChanged()
{
//    QListWidgetItem *currentItem = listWidget->currentItem();
//    QString fileName = currentItem->data(Qt::UserRole).toString();

//    FileThread *ft = new FileThread(fileName);
//    ft->start(QThread::HighPriority);
}

