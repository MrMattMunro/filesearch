/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/

#ifndef IMPORTTABLEDIALOG_H
#define IMPORTTABLEDIALOG_H
#endif

#include "ui_docnoteinfodialog.h"
#include <QStandardItemModel>


/*! \brief Import data into table using various importer types.
\note XML import requires Qt library at least in the 4.3.0 version.
\author Petr Vanek <petr@scribus.info>
*/
class DocNoteInfoDialog : public QDialog, public Ui::DocNoteInfoDialog
{
	Q_OBJECT

	public:
                DocNoteInfoDialog(QWidget * parent = 0, const QString & dir = 0);
                bool update;
                QStandardItemModel *model;
                QString m_dir;
	private:
                QObject * m_parent;

	private slots:
                void confirmBtn_clicked();
                void cancelBtn_clicked();

        signals:
                //确定按钮点击
                void  comfirmBtnClk();

};
