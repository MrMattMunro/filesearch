/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/

#ifndef IMPORTTABLEDIALOG_H
#define IMPORTTABLEDIALOG_H
#endif
#include <QProgressDialog>
#include "ui_exportdocdialog.h"

#include <QStandardItemModel>

// class QProgressDialog;

/*! \brief Import data into table using various importer types.
\note XML import requires Qt library at least in the 4.3.0 version.
\author Petr Vanek <petr@scribus.info>
*/
class ExportDocDialog : public QDialog, public Ui::ExportDocDialog
{
	Q_OBJECT

	public:
                ExportDocDialog(QWidget * parent = 0,const QString & dirUuid = 0, const QString & dir = 0, const QString & type = 0);
                bool update;
                QStandardItemModel *model;

                QString m_type;
                QString m_dirUuid;
                QString m_exportDir;
                QString m_dir;
	private:
                QObject * m_parent;
                //QProgressDialog * progress;
                bool cancelled;

                int loadFiles(QString parentPath, QStringList excludeTypeList, QStandardItemModel *model);
                bool setProgress(int p);

	private slots:
                void fileSelBtn_clicked();
                void previewBtn_clicked();
                void delBtn_clicked();
                void confirmBtn_clicked();
                void cancelBtn_clicked();

        signals:
                //确定按钮点击
                void  comfirmBtnClk();

};
