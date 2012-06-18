#include <QProgressDialog>
#include "ui_accountdialog.h"

#include <QStandardItemModel>

class AccountDialog : public QDialog, public Ui::AccountDialog
{
	Q_OBJECT

	public:
                AccountDialog(QWidget * parent = 0);
                bool update;
	private:
                QObject * m_parent;


	private slots:
                void closeBtn_clicked();
                void changePassword();
                void score4vip();
                void updatevip();

        signals:
               void updateVip();

};
