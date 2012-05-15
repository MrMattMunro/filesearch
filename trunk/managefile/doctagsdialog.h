#pragma once

#include "ui_doctagsdialog.h"
#include <QProgressDialog>
#include <QStandardItemModel>

class DocTagsDialog : public QDialog, public Ui::DocTagsDialog
{
	Q_OBJECT

	public:
                DocTagsDialog(QWidget * parent = 0);
                bool update;
                QStringList waitItems;
                QStringList sellItems;
	private:
                QObject * m_parent;
                QString  m_selDocUuId;

	private slots:
                void confirmBtn_clicked();
                void cancelBtn_clicked();
        protected:
                bool eventFilter(QObject *obj, QEvent *ev);
        signals:


};
