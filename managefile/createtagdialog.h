#include <QProgressDialog>
#include "ui_createtagdialog.h"

#include <QStandardItemModel>

class CreateTagDialog : public QDialog, public Ui::CreateTagDialog
{
	Q_OBJECT

	public:
                CreateTagDialog(QWidget * parent = 0,const QString & m_parentTagUuId = 0);
                bool update;
                QString m_newTagUuId;
                QString m_tagname;

	private:
                QObject * m_parent;
                QString m_parentTagUuId;

	private slots:
                void confirmBtn_clicked();
                void cancelBtn_clicked();

        signals:

};
