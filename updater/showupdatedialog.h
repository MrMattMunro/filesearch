/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/

#ifndef SHOWUPDATEDIALOG_H
#define SHOWUPDATEDIALOG_H
#endif

#include "ui_showupdatedialog.h"

#include <QStandardItemModel>
#include "requtil.h"

/*! \brief Import data into table using various importer types.
\note XML import requires Qt library at least in the 4.3.0 version.
\author Petr Vanek <petr@scribus.info>
*/
class ShowUpdateDialog : public QDialog, public Ui::ShowUpdateDialog
{
	Q_OBJECT

	public:
                ShowUpdateDialog(QWidget * parent = 0);
                bool update;
        private:
                ReqUtil * requtil;
                void updatefiles();
        private slots:
                void doConfirmReply();
                void confirmBtn_clicked();
                void closeBtn_clicked();
        signals:


};
