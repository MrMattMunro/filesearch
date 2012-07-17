#ifndef RefereeDialog_H
#define RefereeDialog_H

#include <QDialog>
#include <QStandardItemModel>
#include "ui_refereedialog.h"
#include "sendmail.h"

class RefereeDialog: public QDialog, public Ui::RefereeDialog
{
        Q_OBJECT
    public:
        RefereeDialog (QWidget *parent=0, const QString & dirUuid = 0);
        bool update;
        QString m_tempAddr;
        bool m_isBusying;
    private:
        QObject * m_parent;
        SendMailObj sendMailObj;

    private slots:
        void closeBtn_clicked();
        void applyBtn_clicked();
        void checkSuccess();
        void changeEmail(QString usrname);

};

#endif // 
