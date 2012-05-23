#include "mytreedelegate.h"
#include "utils.h"
#include <QDebug>
#include <QPainter>
#include <QEvent>
#include <QStyledItemDelegate>



MyTreeDelegate::MyTreeDelegate(QObject * parent) :QStyledItemDelegate (parent)
{
//    docPixmap = QPixmap(":/doc.ico");
//    pdfPixmap = QPixmap(":/pdf.ico");

}

void MyTreeDelegate::paint(QPainter * painter,
                           const QStyleOptionViewItem & option,
                           const QModelIndex & index) const
{
    // 正常数据
    if(index.column() !=  0 || index.column() ==  0 ){
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }
    // 图片
    const QAbstractItemModel * model= index.model();
    QMap<int, QVariant> valuemap = model->itemData(index);

    QList<QVariant> values = valuemap.values();
    QList<int> keys = valuemap.keys();

    if(keys.size() <= 0 || values.size() <= 0 ){
      return;
    }

    QVariant path = values.at(0);
    int key = keys.at(0);

//    // 自绘表格
     QIcon star  = Utils::getIcon("doc.ico");
////    if(key == MyTableView.wordItemType ){
////        //star = docPixmap;
////    }
////    if(key == MyTableView.pdfItemType ){
////        //star = pdfPixmap;
////    }


    int width=16;
    int height=16;
    QRect rect=option.rect;
    int x=rect.x() + rect.width()/2-width/2;
    int y=rect.y() + rect.height()/2-height/2;

    painter->drawPixmap(x, y, star.pixmap(16,16, QIcon.Normal, QIcon.Off));
    qDebug("paint end");
}

bool MyTreeDelegate::editorEvent(QEvent * event, QAbstractItemModel * model,
                                 const QStyleOptionViewItem & /*option*/,
                                 const QModelIndex & index)
{
    // 左键点击
    if(event->type()==QEvent::MouseButtonPress && index.column()==0 ){
        QVariant var=model->data(index,Qt::CheckStateRole);
        bool isFavourite=var.toBool();
        if(var.isValid()){
            isFavourite=isFavourite?false:true;
        } else{
            isFavourite=true;
        }
        // model->setData(index,isFavourite,Qt::CheckStateRole);
        return true;//I have handled the event
    }

    return false;
}
