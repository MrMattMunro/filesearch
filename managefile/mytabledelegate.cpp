#include "mytabledelegate.h"
#include "utils.h"
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


//    // 正常数据
//    if(index.column() !=  0 || index.column() ==  0 ){
//        QItemDelegate::paint(painter, option, index);
//        return;
//    }

    // 图片
    int row = index.row();
    int column = index.column();

    const QAbstractItemModel * model= index.model();
    QMap<int, QVariant> valuemap = model->itemData(index);

    QList<QVariant> values = valuemap.values();
    QList<int> keys = valuemap.keys();

    if(keys.size() <= 0 || values.size() <= 0 ){
        return;
    }

    QString filename = qvariant_cast<QString> (values.at(0));
    QString ico = qvariant_cast<QString> (values.at(1));
    QString path = qvariant_cast<QString> (values.at(2));
    QString uuId = qvariant_cast<QString> (values.at(3));


    QIcon icon = Utils::getIcon(ico);
    int width=16;
    int height=16;
    QRect rect= option.rect;
    // int x= rect.x() + rect.width()/2-width/2;
    int y= rect.y() + rect.height()/2-height/2;

    //painter->drawPixmap(0, y, icon.pixmap(16,16, QIcon.Normal, QIcon.Off));

    //绘制文本
    QBrush b(QColor(197,229,239));
    painter->setPen(QColor(51,102,205));
//    painter->setBrush(b);
    painter->drawText(QRectF(5, y + 15 ,300,20),Qt::AlignLeft, path);

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
