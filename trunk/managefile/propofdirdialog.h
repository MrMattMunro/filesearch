#include <QProgressDialog>
#include "ui_propofdirdialog.h"

#include <QStandardItemModel>

class PropOfDirDialog : public QDialog, public Ui::PropOfDirDialog
{
	Q_OBJECT

	public:
                PropOfDirDialog(QWidget * parent = 0,const QString & curUuid = 0, const QString & dir = 0);
                bool update;

                QString m_curUuid;
                QString m_dir;
        private:
                QObject * m_parent;

	private slots:
                void confirmBtn_clicked();
                void cancelBtn_clicked();

        signals:

};
