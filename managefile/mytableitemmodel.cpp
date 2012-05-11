#include "mytableitemmodel.h"
#include "utils.h"
#include <QDebug>

QVariant MyTableItemModel::data(const QModelIndex & index, int role) const
{
    qDebug ("data start");
    int column=index.column();

    if(role == Qt::DisplayRole){
       return QStandardItemModel::data(index, role);
    }

    // 改变背景色
    if (Qt::BackgroundColorRole == role)
     {
         if (index.row() == hoverRow){
             return QBrush(QColor(185, 210, 235));
         }
     }

    if(role == Qt::ToolTipRole && column==0){
       return  QStandardItemModel::data(index, role);
    }

    // 图标
    if(role == Qt::DecorationRole || role == Qt::DecorationPropertyRole){
         QString icon = qvariant_cast<QString>(QStandardItemModel::data(index, role));
         return Utils::getIcon(icon);
    }

    qDebug ("data end");
    return QStandardItemModel::data(index,  role);
}

// 记录onhoveRow
void MyTableItemModel::setHoverRow(int row) {
    hoverRow = row;
}

QVariant MyTableItemModel::headerData(int section,
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

bool MyTableItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
//    if(role == Qt::CheckStateRole)
//    {
//        if(value == Qt::Checked)
//        {
//            checkedIndexes.insert(index);
//            if(hasChildren(index) == true)
//            {
//                recursiveCheck(index, value);
//            }
//        }
//        else
//        {
//            checkedIndexes.remove(index);
//            if(hasChildren(index) == true)
//            {
//                recursiveCheck(index, value);
//            }
//        }
//        emit dataChanged(index, index);
//        return true;
//    }
    return QStandardItemModel::setData(index, value, role);
}


