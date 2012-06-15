#include <QProgressDialog>
#include "ui_changepwddialog.h"
#include "requtil.h"

#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class ChangePwdDialog : public QDialog, public Ui::ChangePwdDialog
{
	Q_OBJECT

	public:
                ChangePwdDialog(QWidget * parent = 0);
                bool update;
	private:
                QString m_action;
                QObject * m_parent;
                ReqUtil * requtil;
	private slots:
                void confirmBtn_clicked();
                void cancelBtn_clicked();
                void doConfirmReply();
        signals:

};
