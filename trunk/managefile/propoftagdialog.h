#include <QProgressDialog>
#include "ui_propoftagdialog.h"

#include <QStandardItemModel>

class PropOfTagDialog : public QDialog, public Ui::PropOfTagDialog
{
	Q_OBJECT

	public:
                PropOfTagDialog(QWidget * parent = 0,const QString & tagUuId = 0, const QString & tagname = 0
                          ,const QString & desp = 0);
                bool update;
                QString m_tagUuId;
                QString m_tagname;
                QString m_desp;

	private:
                QObject * m_parent;

	private slots:
                void confirmBtn_clicked();
                void cancelBtn_clicked();

        signals:

};
