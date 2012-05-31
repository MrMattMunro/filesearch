#ifndef PropOfDirDialog_H
#define PropOfDirDialog_H

#include <QDialog>
#include <QStandardItemModel>
#include "ui_propofdirdialog.h"

class PropOfDirDialog: public QDialog, public Ui::PropOfDirDialog
{
        Q_OBJECT
    public:
        PropOfDirDialog (QWidget *parent=0, const QString & dirUuid = 0);

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
