#include <QProgressDialog>
#include "ui_scoretovipdialog.h"
#include "requtil.h"
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class ScoreToVipDialog : public QDialog, public Ui::ScoreToVipDialog
{
	Q_OBJECT

	public:
                ScoreToVipDialog(QWidget * parent = 0);
                bool update;
	private:
                QString m_action;
                QObject * m_parent;
                ReqUtil * requtil;
	private slots:
                void confirmBtn_clicked();
                void cancelBtn_clicked();
                void doConfirmReply();
                void countMonth();
        signals:

};
