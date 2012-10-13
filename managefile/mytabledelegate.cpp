#include "mytabledelegate.h"
#include "utils.h"
#include "mytableview.h"
#include <QDebug>
#include <QPainter>
#include <QEvent>
#include <document.h>
#include <tableresult.h>
#include <preferences.h>
#include <db/doctagdao.h>

MyTableDelegate::MyTableDelegate(QObject * parent) :QItemDelegate(parent)
{
//    docPixmap = QPixmap(":/doc.ico");
//    pdfPixmap = QPixmap(":/pdf.ico");

}

void MyTableDelegate::paint(QPainter * painter,
                           const QStyleOptionViewItem & option,
                           const QModelIndex & index) const
{
    if(index.data().canConvert<Document>()){
        paintRow(painter, option, index);
    } else{
        if(index.data().canConvert<TableResult>()){
           paintResultRow(painter, option, index);
        }else{
           paintResultHeadRow(painter, option, index);
        }
    }
    return;
}

QSize MyTableDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.data().canConvert<Document>())
        return QSize(option.rect.width(), 45);
    else
        return QSize(option.rect.width(), 25);
}

void MyTableDelegate::paintRow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const bool isSelected = option.state & QStyle::State_Selected;
    const bool isHovered = option.state & QStyle::State_MouseOver;

    Document tp = index.data().value<Document>();

    painter->save();

    QLinearGradient backgroundGradient(QPoint(option.rect.x(), option.rect.y()), QPoint(option.rect.x(), option.rect.y()+option.rect.height()));
    if(isSelected || isHovered) {
        backgroundGradient.setColorAt(0, QColor(109, 164, 219));
        backgroundGradient.setColorAt(1, QColor(61, 138, 212));
        painter->fillRect(option.rect, QBrush(backgroundGradient));

    } else {
        backgroundGradient.setColorAt(0, QColor(245, 245, 245));
        backgroundGradient.setColorAt(1, QColor(240, 240, 240));
        painter->fillRect(option.rect, QBrush(backgroundGradient));
    }

    painter->setPen(QColor(225, 225, 225));
    if(isSelected || isHovered )
    {
        painter->setPen(QColor(37, 105, 169));
        painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
        painter->setPen(Qt::transparent);
    }
    painter->drawLine(option.rect.topLeft(), option.rect.topRight());
    if(!isSelected || !isHovered)
    {
        painter->setPen(QColor(248, 248, 248));
        painter->drawLine(QPoint(option.rect.x(), option.rect.y()+1), QPoint(option.rect.x()+option.rect.width(), option.rect.y()+1));
    }
    // icon
    QString filename = tp.docName();
    int dotpos = filename.lastIndexOf(".");
    QString icon = filename.right(filename.length() - dotpos - 1).toLower();
    icon = icon.append(".ico");
    QIcon qicon = Utils::getIcon(icon);
    painter->drawPixmap(10, option.rect.y() + 10, qicon.pixmap(16,16, QIcon.Normal, QIcon.Off));

    // 名称
    QRect nametextRect(option.rect.x() + 30, option.rect.y() - 20, option.rect.width()-10, option.rect.height());
    painter->setPen(QColor(69, 69, 69));
    QFont textFont(painter->font());
    textFont.setPixelSize(15);
    if(isSelected){
        painter->setPen(QColor(229, 229, 229));
    }
    textFont.setFamily("Helvetica Neue");
    painter->setFont(textFont);
    painter->drawText(nametextRect, Qt::AlignLeft|Qt::AlignVCenter, tp.docName());

    // 动态第二行
    Preferences* p = Preferences::instance();
    QStringList fields = p->getTableSelField();
    // 默认情况下
    if(fields.length() == 0){
       fields.append(QString::number(CREATE_DATE));
       fields.append(QString::number(MODIFIED_DATE));
       fields.append(QString::number(TAGS));
       fields.append(QString::number(URL));
       fields.append(QString::number(LOCATION));
    }
    QString field;

    int y = option.rect.y();
    int  x = option.rect.x() + 30;
    foreach (field, fields) {
        int selFied = field.toInt();

        if(selFied == CREATE_DATE){
            textFont.setPixelSize(12);
            painter->setFont(textFont);

            QRect textRect(x, y, option.rect.width()-10, option.rect.height());
            painter->setPen(QColor(39, 39, 39));
            painter->drawText(textRect, Qt::AlignLeft|Qt::AlignVCenter, tp.dtCreated());
            x = x + 120;
        }
        if(selFied == MODIFIED_DATE){
            textFont.setPixelSize(12);
            painter->setFont(textFont);

            QRect textRect(x, y, option.rect.width()-10, option.rect.height());
            painter->setPen(QColor(39, 39, 39));
            painter->drawText(textRect, Qt::AlignLeft|Qt::AlignVCenter, tp.dtModified());
            x = x + 120;
        }
        if(selFied == ACCESS_DATE){
            textFont.setPixelSize(12);
            painter->setFont(textFont);

            QRect textRect(x, y, option.rect.width()-10, option.rect.height());
            painter->setPen(QColor(39, 39, 39));
            painter->drawText(textRect, Qt::AlignLeft|Qt::AlignVCenter, tp.dtAccessed());
            x = x + 120;
        }
        if(selFied == FILE_SIZE){
            QFileInfo file(tp.docLoc());
           // 计算size K
           textFont.setPixelSize(12);
           painter->setFont(textFont);

           QString size =  QString::number(file.size() / 1000).append("K");
           QRect textRect(x, y, option.rect.width()-10, option.rect.height());
           painter->setPen(QColor(51,102,205));
           painter->drawText(textRect, Qt::AlignLeft|Qt::AlignVCenter, size);
           x = x + size.length() * 7;
        }
        if(selFied == AUTHOR){
            textFont.setPixelSize(12);
            painter->setFont(textFont);

            QString author = tp.docAuthor();
            if(author.length() != 0){
                 QRect textRect(x, y, option.rect.width()-10, option.rect.height());
                 painter->setPen(QColor(39, 39, 39));
                 painter->drawText(textRect, Qt::AlignLeft|Qt::AlignVCenter, author);
                 x = x + author.length() * 10;
            }
        }
        if(selFied == READ_COUNT){
            textFont.setPixelSize(12);
            painter->setFont(textFont);

            QRect textRect(x, y, option.rect.width()-10, option.rect.height());
            painter->setPen(QColor(51,102,205));
            painter->drawText(textRect, Qt::AlignLeft|Qt::AlignVCenter, QString::number(tp.readcount()));
            x = x + 10;
        }
        if(selFied == RELATED_COUNT){
            textFont.setPixelSize(12);
            painter->setFont(textFont);

            QRect textRect(x, y, option.rect.width()-10, option.rect.height());
            painter->setPen(QColor(51,102,205));
            painter->drawText(textRect, Qt::AlignLeft|Qt::AlignVCenter,  QString::number(tp.relateCount()));
            x = x + 10;
        }
        if(selFied == TAGS){
           // 取得Tags
            QList<Tag> sellitems = DocTagDao::selectTagsbyDocUuId(tp.docUuid());
            for (int var = 0; var < sellitems.length(); ++var) {
                 Tag tag = sellitems.at(var);

                 int len = tag.TAG_NAME.length();
                 QBrush bruch(Qt::FDiagPattern);
                 QRectF rectangle(x, y + 20, 10 * len, 20);
                 bruch.setStyle(Qt::NoBrush);

                 painter->setBrush(bruch);
                 painter->drawRect(rectangle);

                 textFont.setPixelSize(11);
                 //textFont.setWeight(QFont::Bold);
                 painter->setFont(textFont);

                 QRect textRect(x, y, option.rect.width()-10, option.rect.height());
                 painter->setPen(QColor(39, 39, 39));
                 painter->drawText(textRect, Qt::AlignLeft|Qt::AlignVCenter, tag.TAG_NAME);
                 x = x + sellitems.length() * 20;
            }
        }
        if(selFied == URL){
           textFont.setPixelSize(12);
           painter->setFont(textFont);
           QString url  = tp.docUrl();
           if(url.length() != 0){
                 QRect textRect(x, y, option.rect.width()-10, option.rect.height());
                 painter->setPen(QColor(39, 39, 39));
                 painter->drawText(textRect, Qt::AlignLeft|Qt::AlignVCenter, url);
                 x = x + 150;
           }
        }
        if(selFied == LOCATION){
            textFont.setPixelSize(12);
            painter->setFont(textFont);

            QRect textRect(option.rect.x() + 30, y + 20, option.rect.width()-10, option.rect.height());
            painter->setPen(QColor(51,102,205));
            painter->drawText(textRect, Qt::AlignLeft|Qt::AlignVCenter, tp.docLoc());
            x = x + 25;
        }
    }

    painter->restore();
}
// 结果集
void MyTableDelegate::paintResultRow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const bool isSelected = option.state & QStyle::State_Selected;
    const bool isHovered = option.state & QStyle::State_MouseOver;

    TableResult tp = index.data().value<TableResult>();

    painter->save();

    QLinearGradient backgroundGradient(QPoint(option.rect.x(), option.rect.y()), QPoint(option.rect.x(), option.rect.y()+option.rect.height()));
    if(isSelected || isHovered) {
        //        painter->fillRect(option.rect, QBrush(QColor(49, 49, 49)));
        backgroundGradient.setColorAt(0, QColor(109, 164, 219));
        backgroundGradient.setColorAt(1, QColor(61, 138, 212));
        painter->fillRect(option.rect, QBrush(backgroundGradient));
        //        painter->fillRect(option.rect, QBrush(QColor(225, 225, 225)));

    } else {
        //        painter->fillRect(option.rect, QBrush(QColor(244, 244, 244)));
        backgroundGradient.setColorAt(0, QColor(245, 245, 245));
        backgroundGradient.setColorAt(1, QColor(240, 240, 240));
        painter->fillRect(option.rect, QBrush(backgroundGradient));
    }

    painter->setPen(QColor(225, 225, 225));
    if(isSelected || isHovered)
    {
        painter->setPen(QColor(37, 105, 169));
        painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
        painter->setPen(Qt::transparent);
    }
    painter->drawLine(option.rect.topLeft(), option.rect.topRight());
    if(!isSelected || !isHovered)
    {
        painter->setPen(QColor(248, 248, 248));
        painter->drawLine(QPoint(option.rect.x(), option.rect.y()+1), QPoint(option.rect.x()+option.rect.width(), option.rect.y()+1));
    }
    //    QString text = index.model()->data(index, Qt::DisplayRole).toString();
    QRect textRect(option.rect.x()+10, option.rect.y(), option.rect.width()-10, option.rect.height());
    painter->setPen(QColor(69, 69, 69));
    QFont textFont(painter->font());
    textFont.setPixelSize(18);
    if(isSelected){
        painter->setPen(QColor(229, 229, 229));
    }


    int y = option.rect.y();
    int  x = option.rect.x() + 30;


    // 位置信息
    QString desp = tp.desp();
    textFont.setPixelSize(12);
    QRect desptextRect(x, y, option.rect.width()-10, option.rect.height());
    painter->setPen(QColor(39, 39, 39));
    painter->drawText(desptextRect, Qt::AlignLeft|Qt::AlignVCenter, desp);
    x = x + desp.length() * 10;

    // 内容信息
    QString content = tp.content().length() > 120?  tp.content().left(120):tp.content();
    textFont.setPixelSize(10);
    textFont.setFamily("Helvetica Neue");
    QRect contenttextRect(x, y, option.rect.width()-10, option.rect.height());
    painter->setPen(QColor(39, 39, 39));
    painter->drawText(contenttextRect, Qt::AlignLeft|Qt::AlignVCenter, content);

    painter->restore();
}

// 结果集文件标题
void MyTableDelegate::paintResultHeadRow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const bool isSelected = option.state & QStyle::State_Selected;
    const bool isHovered = option.state & QStyle::State_MouseOver;

    painter->save();

    QLinearGradient backgroundGradient(QPoint(option.rect.x(), option.rect.y()),
                                       QPoint(option.rect.x(), option.rect.y()+option.rect.height()));

    backgroundGradient.setColorAt(0, QColor(215, 215, 215));
    backgroundGradient.setColorAt(1, QColor(230, 230, 230));
    painter->fillRect(option.rect, QBrush(backgroundGradient));

    painter->setPen(QColor(213, 213, 213));
    painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());

    QFont textFont(painter->font());
    textFont.setPixelSize(15);
    textFont.setFamily("Helvetica Neue");
    painter->setFont(textFont);


    // icon
    QString filename = index.model()->data(index).toString();
    int dotpos = filename.lastIndexOf(".");
    QString icon = filename.right(filename.length() - dotpos - 1).toLower();
    icon = icon.append(".ico");
    QIcon qicon = Utils::getIcon(icon);
    painter->drawPixmap(10, option.rect.y() + 10, qicon.pixmap(16,16, QIcon.Normal, QIcon.Off));


    QRect textRect(option.rect.x() + 30, option.rect.y(), option.rect.width()-10, option.rect.height());
    painter->setPen(QColor(39, 39, 39));
    painter->drawText(textRect, Qt::AlignLeft|Qt::AlignVCenter, filename);

    painter->restore();
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
