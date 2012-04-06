#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H

#include <QListWidget>
#include <QListView>
#include <QListWidgetItem>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QDragEnterEvent>

class ListWidget : public QListWidget
{
        Q_OBJECT
public:
        ListWidget(QWidget *parent) : QListWidget(parent)
        {
                setDragEnabled(true);
                setAcceptDrops(true);
        }
        void dragEnterEvent(QDragEnterEvent *event)
        {
                if (event->mimeData()->hasFormat("bla/x-something"))
                        event->accept();
                else
                        event->ignore();
        }

        void dragMoveEvent(QDragMoveEvent *event)
        {
                if (event->mimeData()->hasFormat("bla/x-something")) {
                        event->setDropAction(Qt::MoveAction);
                        event->accept();
                } else
                        event->ignore();
        }
        Qt::DropActions supportedDropActions () const
        {
                return Qt::MoveAction;
        }
        void dropEvent(QDropEvent *event)
        {
                if (event->mimeData()->hasFormat("bla/x-something")) {
                        event->accept();
                        event->setDropAction(Qt::MoveAction);
                        QByteArray pieceData = event->mimeData()->data("bla/x-something");
                        addItem(pieceData);
                } else
                        event->ignore();
        }

        void startDrag(Qt::DropActions)
        {
                QListWidgetItem *item = currentItem();
                QMimeData *mimeData = new QMimeData;
                QByteArray ba = item->text().toLatin1().data();
                QString theText = "bla/x-something";
                mimeData->setData(theText, ba);
                QDrag *drag = new QDrag(this);
                drag->setMimeData(mimeData);
                if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
                        delete takeItem(row(item));
        }
};


class MyListWidget : public QWidget
{
    Q_OBJECT

public:
    MyListWidget(QWidget * parent);
    void setFileName(QString text);
    void addItem(QListWidgetItem *item);

    ListWidget *listWidget;
    QLabel *fileName;
private slots:
    void on_itemSelectionChanged();
};

#endif // MYLISTWIDGET_H
