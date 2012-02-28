#ifndef MYSTANDARDITEMMODEL_H
#define MYSTANDARDITEMMODEL_H
#endif

#include<QStandardItemModel>

class MyStandardItemModel:public QStandardItemModel
{
public:
        MyStandardItemModel(QObject * parent=0)
                :QStandardItemModel(parent){}
        virtual ~ MyStandardItemModel(){}

        QVariant data(const QModelIndex & index,
                int role=Qt::DisplayRole) const;
        QVariant headerData(int section,
                Qt::Orientation orientation,
                int role=Qt::DisplayRole) const;
        void setHoverRow(int row);

private:
        int hoverRow;

};



