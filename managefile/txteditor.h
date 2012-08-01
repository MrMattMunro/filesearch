/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/

#ifndef TxtEditor_H
#define TxtEditor_H

#include <QWidget>
#include <QFileSystemWatcher>

#include "ui_TxtEditor.h"

class QTextDocument;
class QLabel;
class QProgressDialog;


/*!
\brief Execute Query dialog. Simple SQL editor.
It allows simple editing capabilities for user. There is a simple
syntax highlighting (see SqlHighlighter class).
\author Petr Vanek <petr@scribus.info>
 */
class TxtEditor : public QMainWindow
{
	Q_OBJECT

	public:
                TxtEditor(QWidget * parent = 0);
                ~TxtEditor();

		void saveOnExit();

		void setFileName(const QString & fname);
		QString fileName() { return m_fileName; };

                void open(const QString & newFile);
   	signals:

	private:
        Ui::TxtEditor ui;

		QString m_fileName;
		QFileSystemWatcher * m_fileWatcher;

		QString cursorTemplate;

		void showEvent(QShowEvent * event);
		bool changedConfirm();
                void saveFile();

		void find(QString ttf, bool forward/*, bool backward*/);
                void setCursorPos(int row, int column);

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
