#include <QProgressDialog>
#include "ui_createsubdirdialog.h"

#include <QStandardItemModel>

class CreateSubDirDialog : public QDialog, public Ui::CreateSubDirDialog
{
	Q_OBJECT

	public:
                CreateSubDirDialog(QWidget * parent = 0,const QString & curUuid = 0, const QString & dir = 0);
                bool update;

                QString m_newUuid;
	private:
                QObject * m_parent;
                QString m_curUuid;
                QString m_dir;

	private slots:
                void confirmBtn_clicked();
                void cancelBtn_clicked();

        signals:
                // 确定按钮点击
                void  comfirmBtnClk();

};
