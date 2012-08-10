#ifndef OptOfSearchDialog_H
#define OptOfSearchDialog_H

#include <QDialog>
#include <QStandardItemModel>
#include "ui_optofsearchdialog.h"

class OptOfSearchDialog: public QDialog, public Ui::OptOfSearchDialog
{
        Q_OBJECT
    public:
        OptOfSearchDialog (QWidget *parent=0);

        bool update;
        int sumofindexfile;
    private:
        QObject * m_parent;

    private slots:
        void closeBtn_clicked();
        void updateBtn_clicked();
        void reCreateBtn_clicked();
};

#endif // 
