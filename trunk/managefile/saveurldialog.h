#include <QProgressDialog>
#include "ui_saveurldialog.h"
#include "mytreeview.h"

#include <QStandardItemModel>

class SaveUrlDialog : public QDialog, public Ui::SaveUrlDialog
{
	Q_OBJECT

	public:
                SaveUrlDialog(QWidget * parent = 0);
                bool update;

                QString m_toUuid;
                QString m_seldir;
	private:
                QObject * m_parent;
                MyTreeView *q_myTreeList;

	private slots:
                void confirmBtn_clicked();
                void cancelBtn_clicked();
                void newDirBtn_clicked();

        signals:
                // 确定按钮点击
                void  comfirmBtnClk();

};
