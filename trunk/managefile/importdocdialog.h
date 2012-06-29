/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/

#ifndef IMPORTTABLEDIALOG_H
#define IMPORTTABLEDIALOG_H
#endif

#include "ui_importdocdialog.h"

#include <QStandardItemModel>


/*! \brief Import data into table using various importer types.
\note XML import requires Qt library at least in the 4.3.0 version.
\author Petr Vanek <petr@scribus.info>
*/

class ImportDocDialog : public QDialog, public Ui::ImportDocDialog
{
	Q_OBJECT

	public:
                ImportDocDialog(QWidget * parent = 0, const QString & baseUuid = 0, const QString & basedir = 0);
                bool update;
                QStandardItemModel *model;

                QString m_importDir;
	private:
                QObject * m_parent;
                QString m_baseDir;
                QString m_baseUuid;
                int loadFiles(QString parentPath, QStringList filter, QStandardItemModel *model);
                //QProgressDialog * progress;
                bool cancelled;
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
                void  indexfile(QList<QString> filepaths);

};
