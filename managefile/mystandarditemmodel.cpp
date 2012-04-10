#include "mystandarditemmodel.h"
#include <QDebug>

QVariant MyStandardItemModel::data( const QModelIndex & index, int role) const
{
    qDebug ("data start");
    int column=index.column();

    if(role==Qt::DisplayRole){
       return QStandardItemModel::data(index,role);
    }

    // 改变背景色
    if (Qt::BackgroundColorRole == role)
     {
         if (index.row() == hoverRow){
             return QBrush(QColor(185, 210, 235));
         }
     }

    if(role == Qt::ToolTipRole && column==0){
       return  QStandardItemModel::data(index,role);
    }

    qDebug ("data end");
    return QStandardItemModel::data(index,role);
}

// 记录onhoveRow
void MyStandardItemModel::setHoverRow(int row) {
    hoverRow = row;

}

QVariant MyStandardItemModel::headerData(int section,
                                         Qt::Orientation orientation,
                                         int role) const
{

    return "";
//    if(section==0 && orientation==Qt::Horizontal){

//        if(role==Qt::DecorationRole){
//           return QIcon(":/favourite.png");
//        }
//        if(role==Qt::DisplayRole){
//           return "";
//        }
//        if(role==Qt::ToolTipRole){
//          return tr("love");
//        }
//    }
//    return QStandardItemModel::headerData(section, orientation, role);
}

