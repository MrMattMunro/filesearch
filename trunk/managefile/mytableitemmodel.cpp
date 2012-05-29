#include "mytableitemmodel.h"
#include "mytableview.h"
#include "utils.h"
#include <QDebug>

QVariant MyTableItemModel::data(const QModelIndex & index, int role) const
{
    //qDebug ("MyTableItemModel data start");
    int column= index.column();
    int row = index.row();

//     if(column == 0){
//       QString uuid =  qvariant_cast<QString> (QStandardItemModel::data(index, Qt::UserRole));
//    }

    if( column == 1 && role == Qt::DecorationRole){
       QString ico =  qvariant_cast<QString> (QStandardItemModel::data(index, Qt::DecorationRole));
       return Utils::getIcon(ico);
    }

    if(role == Qt::DisplayRole){
       return QStandardItemModel::data(index, role);
    }

    // ¸Ä±ä±³¾°É«
    if (Qt::BackgroundColorRole == role){
        return QStandardItemModel::data(index,  role);
    }

    return QStandardItemModel::data(index,  role);
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

bool MyTableItemModel::setData(const QModelIndex &index, const QVariant &value,  int role)
{

    if(role == Qt::BackgroundRole){
        emit dataChanged(index, index);
        return true;
    }
    if(role == Qt::DisplayRole){
        emit dataChanged(index, index);
        return QStandardItemModel::setData(index, value, role);
    }
}

//bool MyTableItemModel::removeRows(int position, int rows, const QModelIndex &parent)
// {
//     beginRemoveRows(QModelIndex(), position, position + rows-1);

//     for (int row = 0; row < rows; ++row) {
//         this->removeRow(position + row);
//     }

//     endRemoveRows();
//     return true;
// }

//bool MyTableItemModel::insertRows(int position, int rows, const QModelIndex &parent)
// {
//     beginInsertRows(QModelIndex(), position, position+rows-1);

//     for (int row = 0; row < rows; ++row) {
//         //stringList.insert(position, "");
//     }

//     endInsertRows();
//     return true;
// }





