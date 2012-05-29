#pragma once

#ifndef MYSTANDARDITEMMODEL_H
#define MYSTANDARDITEMMODEL_H
#endif

#include<QStandardItemModel>

class MyTableItemModel:public QStandardItemModel
{
public:
        MyTableItemModel(QObject * parent=0)
                :QStandardItemModel(parent){}
        virtual ~ MyTableItemModel(){}

        QVariant data(const QModelIndex & index,
                int role=Qt::DisplayRole) const;
        bool setData(const QModelIndex &index, const QVariant &value, int role);
        QVariant headerData(int section,
                Qt::Orientation orientation,
                int role=Qt::DisplayRole) const;
//        bool removeRows(int position, int rows, const QModelIndex &parent);
//        bool insertRows(int position, int rows, const QModelIndex &parent);

private:

};



