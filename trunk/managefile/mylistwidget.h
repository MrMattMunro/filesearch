#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H

#include <QListWidget>
#include <QListView>
#include <QListWidgetItem>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QDragEnterEvent>
#include <QDragEnterEvent>
#include <QDebug>
#include <QTextCodec>
#include "utils.h"

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
                        QByteArray txt = event->mimeData()->data("bla/x-something");
                        QByteArray icon = event->mimeData()->data("bla/n-something");
                        QByteArray uuid = event->mimeData()->data("bla/o-something");
                        QListWidgetItem *temp = new QListWidgetItem();
                        temp->setIcon(Utils::getIcon(icon));
                        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
                        QString string = codec->toUnicode(txt);

                        temp->setText(string);
                        temp->setData(Qt::UserRole, icon);
                        temp->setData(Qt::UserRole + 1, uuid);
                        qDebug() << "--------------------";
                        qDebug() << "Item icon:: " << icon;
                        qDebug() << "Item text:: " << txt;
                        addItem(temp);
                } else
                        event->ignore();
        }

        void startDrag(Qt::DropActions)
        {
                QListWidgetItem *item = currentItem();
                QMimeData *mimeData = new QMimeData;

                QByteArray ch = item->text().toUtf8();

                QString iconname = item->data(Qt::UserRole).toString();
                QString key = item->data(Qt::UserRole + 1).toString();

                QByteArray iconbyte = iconname.toLatin1().data();
                QByteArray keybyte = key.toLatin1().data();
                // QByteArray textbyte = ba.toLatin1().data();
                QString theText = "bla/x-something";
                QString name = "bla/n-something";
                QString uuid = "bla/o-something";
                mimeData->setData(theText, ch);
                mimeData->setData(name, iconbyte);
                mimeData->setData(uuid, keybyte);
                QDrag *drag = new QDrag(this);
                drag->setMimeData(mimeData);
                if (drag->exec(Qt::MoveAction) == Qt::MoveAction){
                   delete takeItem(row(item));
                }
        }

        QList<QListWidgetItem*> getAllItems()
        {
           QList<QListWidgetItem*> allitems;
           foreach(QListWidgetItem* listItem, findItems("*", Qt::MatchWildcard)){
              allitems.append(listItem);
           }
           return allitems;
       }
};


class MyListWidget : public QWidget
{
    Q_OBJECT

public:
    MyListWidget(QWidget * parent);
    void setFileName(QString text);
    void addItem(QListWidgetItem *item);
    QList<QListWidgetItem*> getAllItems();

    ListWidget *listWidget;
    QLabel *fileName;
private slots:
    void on_itemSelectionChanged();
};

#endif // MYLISTWIDGET_H
