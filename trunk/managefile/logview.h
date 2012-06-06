/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/

#ifndef LogView_H
#define LogView_H

#include <QWidget>
#include <QFileSystemWatcher>

#include "ui_logview.h"

class QTextDocument;
class QLabel;
class QProgressDialog;


/*!
\brief Execute Query dialog. Simple SQL editor.
It allows simple editing capabilities for user. There is a simple
syntax highlighting (see SqlHighlighter class).
\author Petr Vanek <petr@scribus.info>
 */
class LogView : public QDialog
{
	Q_OBJECT

	public:
                LogView(QWidget * parent = 0);
                ~LogView();

		void saveOnExit();

		void setFileName(const QString & fname);
		QString fileName() { return m_fileName; };

                void open(const QString & newFile);

   	signals:
		/*! \brief This signal is emitted when user clicks on the one
		of "run" actions. It's handled in main window later.
		\param command current SQL statement in the editor.
		*/
		void showSqlResult(QString command);
		//! \brief It's emitted when the script is started
		void sqlScriptStart();
		/*! \brief Emitted on demand in the script.
		Line is appended to the script output. */
		void showSqlScriptResult(QString line);

		/*! \brief Request for complete object tree refresh.
		It's used in "Run as Script" */
		void buildTree();
		/*! \brief Rebuild part of the tree */
		void rebuildViewTree(QString schema, QString name);

	private:
                Ui::LogView ui;

		QString m_fileName;
		QFileSystemWatcher * m_fileWatcher;

		QString cursorTemplate;

		void showEvent(QShowEvent * event);
		bool changedConfirm();
                void saveFile();

		void find(QString ttf, bool forward/*, bool backward*/);

		//! Reset the QFileSystemWatcher for new name.
		void setFileWatcher(const QString & newFileName);

                QAction *actionSearch;

	private slots:

		void action_Save_triggered();
		void actionSave_As_triggered();

		// searching
		void actionSearch_triggered();
		void searchEdit_textChanged(const QString & text);
		void findPrevious();
		void findNext();

		//! \brief Watch file for changes from external apps
		void externalFileChange(const QString & path);

};

#endif
