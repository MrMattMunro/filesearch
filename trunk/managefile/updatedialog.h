/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/

#ifndef UPDATEDIALOG_H
#define UPDATEDIALOG_H
#endif

#include "ui_updatedialog.h"

#include <QStandardItemModel>
#include "requtil.h"

/*! \brief Import data into table using various importer types.
\note XML import requires Qt library at least in the 4.3.0 version.
\author Petr Vanek <petr@scribus.info>
*/
class UpdateDialog : public QDialog, public Ui::UpdateDialog
{
	Q_OBJECT

	public:
                UpdateDialog(QWidget * parent = 0);
                bool update;
        private:

        private slots:
                void nexttimeBtn_clicked();
                void ingoreBtn_clicked();
                void updateBtn_clicked();
        signals:


};
