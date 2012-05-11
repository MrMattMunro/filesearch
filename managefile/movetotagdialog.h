#include <QProgressDialog>
#include "ui_movetotagdialog.h"
#include "mytreeview.h"

#include <QStandardItemModel>

class MoveToTagDialog : public QDialog, public Ui::MoveToTagDialog
{
	Q_OBJECT

	public:
                MoveToTagDialog(QWidget * parent = 0,const QString & uuId = 0);
                bool update;
                QString m_uuId;
                QString m_selUuId;
	private:
                QObject * m_parent;
                MyTreeView *q_myTreeList;

	private slots:
                void confirmBtn_clicked();
                void cancelBtn_clicked();

        signals:
                // 确定按钮点击
                void  comfirmBtnClk();

};
