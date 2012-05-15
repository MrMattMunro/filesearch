#pragma once

#include "ui_relatedocdialog.h"

#include <QStandardItemModel>
#include <QModelIndex>


/*! \brief Import data into table using various importer types.
\Doc XML import requires Qt library at least in the 4.3.0 version.
\author Petr Vanek <petr@scribus.info>
*/
class RelateDocDialog : public QDialog, public Ui::RelateDocDialog
{
	Q_OBJECT

	public:
                RelateDocDialog(QWidget * parent = 0);
                bool update;
                QStandardItemModel *model;
                QString m_docUuid;
                QString m_docPath;
                QModelIndex selIndex;
	private:
                void initDocs();
	private slots:
                void deleteRelateDoc();
                void deleteAllRelateDoc();
                void contextMenuRequested(const QPoint &position);
                void openRelateDoc();
        signals:

};
