#include "mytabledelegate.h"
#include "utils.h"
#include "mytableview.h"
#include <QDebug>
#include <QPainter>
#include <QEvent>
MyTableDelegate::MyTableDelegate(QObject * parent) :QItemDelegate(parent)
{
//    docPixmap = QPixmap(":/doc.ico");
//    pdfPixmap = QPixmap(":/pdf.ico");

}

void MyTableDelegate::paint(QPainter * painter,
                           const QStyleOptionViewItem & option,
                           const QModelIndex & index) const
{


    // 正常数据
    if(index.column() ==  0){
        QItemDelegate::paint(painter, option, index);
        return;
    }

   // qDebug("MyTableDelegate paint start");

    int row = index.row();
    int column = index.column();

    const QAbstractItemModel * model= index.model();
    QMap<int, QVariant> valuemap = model->itemData(index);

//    QList<QVariant> values = valuemap.values();
//    QList<int> keys = valuemap.keys();

    // ICON
    int y = (row -1) * 40;
    if(column = 1){
        QItemDelegate::paint(painter, option, index);
        return;
    }

    QFont pathfont("Arial",8, QFont::Light,true);
    QFont namefont("Arial", 12, QFont::Black, true);
    if(column = 2){
        painter->setFont(namefont);
        QString createdate = qvariant_cast<QString> (valuemap.value(Qt::DisplayRole));
        painter->setPen(QColor(0,0,0));
        painter->drawText(QRectF(20, y, 300, 15),Qt::AlignLeft, createdate);
        return;
    }


//    QRect rect= option.rect;
//    int y = rect.y() + rect.height()/2;






   // qDebug() << row;
    //qDebug() << column;

//    //qDebug("MyTableDelegate paint start 1 end");
//    if(keys.size() <= 0 || values.size() <= 0 ){
//        return;
//    }
//    //qDebug("MyTableDelegate paint start 2 end");
//    int key;


//    if(valuemap.contains(DOC_ICON)){
//        QString temp = qvariant_cast<QString> (valuemap.value(DOC_ICON));
//        QIcon icon = Utils::getIcon(temp);
//        painter->drawPixmap(0, y, icon.pixmap(16,16, QIcon.Normal, QIcon.Off));
//    }
//    if(valuemap.contains(DOC_NAME)){
//        painter->setFont(namefont);
//        QString createdate = qvariant_cast<QString> (valuemap.value(DOC_NAME));
//        painter->setPen(QColor(0,0,0));
//        painter->drawText(QRectF(20, y, 300, 15),Qt::AlignLeft, createdate);
//    }
//    if(valuemap.contains(DOC_LOCATION)){
//        painter->setFont(pathfont);
//        QString createdate = qvariant_cast<QString> (valuemap.value(DOC_LOCATION));
//        painter->setPen(QColor(51,102,205));
//        painter->drawText(QRectF(0, y + 15 ,600, 15),Qt::AlignLeft, createdate);
//    }


//        if(key = DOC_NOTES ){
//            QString createdate = qvariant_cast<QString> (valuemap.value(key));
//            painter->setPen(QColor(51,102,205));
//            painter->drawText(QRectF(5, y + 15 ,300,20),Qt::AlignLeft, createdate);
//        }

//        if(key = DOC_CREATE_DATE ){
//            QString createdate = qvariant_cast<QString> (valuemap.value(key));
//            painter->setPen(QColor(51,102,205));
//            painter->drawText(QRectF(5, y + 15 ,300,20),Qt::AlignLeft, createdate);
//        }
//        if(key = DOC_MODIFIED_DATE ){
//            QString modifydate = qvariant_cast<QString> (valuemap.value(key));
//            painter->setPen(QColor(51,102,205));
//            painter->drawText(QRectF(5, y + 15 ,300,20),Qt::AlignLeft, modifydate);
//        }
//        if(key = DOC_ACCESS_DATE ){
//            QString accessdate = qvariant_cast<QString> (valuemap.value(key));
//            painter->setPen(QColor(51,102,205));
//            painter->drawText(QRectF(5, y + 15 ,300,20),Qt::AlignLeft, accessdate);
//        }
//        if(key = DOC_SIZE ){
//           QString size = qvariant_cast<QString> (valuemap.value(key));
//           painter->setPen(QColor(51,102,205));
//           painter->drawText(QRectF(5, y + 15 ,300,20),Qt::AlignLeft, size);
//        }
//        if(key = DOC_AUTHOR ){
//           QString author = qvariant_cast<QString> (valuemap.value(key));
//           painter->setPen(QColor(51,102,205));
//           painter->drawText(QRectF(5, y + 15 ,300,20),Qt::AlignLeft, author);
//        }
//        if(key = DOC_READ_COUNT ){
//           QString readcount = qvariant_cast<QString> (valuemap.value(key));
//           painter->setPen(QColor(51,102,205));
//           painter->drawText(QRectF(5, y + 15 ,300,20),Qt::AlignLeft, readcount);
//        }
//        if(key = DOC_RELATED_COUNT ){
//           QString relatecount = qvariant_cast<QString> (valuemap.value(key));
//           painter->setPen(QColor(51,102,205));
//           painter->drawText(QRectF(5, y + 15 ,300,20),Qt::AlignLeft, relatecount);
//        }
//        if(key = DOC_TAGS ){
//           QString tags = qvariant_cast<QString> (valuemap.value(key));
//           painter->drawText(QRectF(5, y + 15 ,300,20),Qt::AlignLeft, tags);
//        }
//        if(key = DOC_URL ){
//           QString url = qvariant_cast<QString> (valuemap.value(key));
//           painter->drawText(QRectF(5, y + 15 ,300,20),Qt::AlignLeft, url);
//        }

    QItemDelegate::paint(painter, option, index);
    return;
}

bool MyTableDelegate::editorEvent(QEvent * event, QAbstractItemModel * model,
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
