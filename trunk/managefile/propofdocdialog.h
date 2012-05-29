#ifndef PropOfDocDialog_H
#define PropOfDocDialog_H

#include <QDialog>
#include <QStandardItemModel>
#include "ui_propofdocdialog.h"

class PropOfDocDialog: public QDialog, public Ui::PropOfDocDialog
{
        Q_OBJECT
    public:
        PropOfDocDialog (QWidget *parent=0,const QString & docUuid = 0);

        bool update;
        QString m_curUuid;
        QStandardItemModel *model;
    private:
        QObject * m_parent;

    private slots:
        void closeBtn_clicked();
        void applyBtn_clicked();
};

#endif // 
