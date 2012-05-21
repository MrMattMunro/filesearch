#include <QProgressDialog>
#include "ui_movetodirdialog.h"
#include "mytreeview.h"

#include <QStandardItemModel>

class MoveToDirDialog : public QDialog, public Ui::MoveToDirDialog
{
	Q_OBJECT

	public:
                MoveToDirDialog(QWidget * parent = 0,const QString & curUuid = 0, const QString & dir = 0);
                bool update;
                QString m_dir;

                QString m_curUuid;
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
