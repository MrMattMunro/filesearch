#include <QProgressDialog>
#include "ui_propofdirdialog.h"

#include <QStandardItemModel>

class PropOfDirDialog : public QDialog, public Ui::PropOfDirDialog
{
	Q_OBJECT

	public:
                PropOfDirDialog(QWidget * parent = 0,const QString & basedir = 0, const QString & dir = 0);
                bool update;

                QString m_exportDir;
                QString m_dir;
        private:
                QObject * m_parent;
                QString m_baseDir;

	private slots:
                void confirmBtn_clicked();
                void cancelBtn_clicked();

        signals:

};
