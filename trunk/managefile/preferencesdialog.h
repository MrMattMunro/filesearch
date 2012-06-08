/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/

#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>

#include "ui_preferencesdialog.h"
#include "ui_prefsdatastorewidget.h"
#include "ui_prefslnfwidget.h"
#include "ui_prefseditorwidget.h"

class ExtensionModel;


class PrefsDataStoreWidget : public QWidget, public Ui::PrefsDataStoreWidget
{
	Q_OBJECT
	public:
                PrefsDataStoreWidget(QWidget * parent = 0);
};

class PrefsLNFWidget : public QWidget, public Ui::PrefsLNFWidget
{
	Q_OBJECT
	public:
		PrefsLNFWidget(QWidget * parent = 0);
};

class PrefsEditorWidget : public QWidget, public Ui::PrefsEditorWidget
{
	Q_OBJECT
	public:
                PrefsEditorWidget(QWidget * parent = 0);
};


/*! \brief Basic preferences dialog and handling.
It constructs GUI to manage the prefs. The static methods
are used to access the prefs out of this class in the
application guts.
\author Petr Vanek <petr@scribus.info>
*/
class PreferencesDialog : public QDialog, public Ui::PreferencesDialog
{
	Q_OBJECT

	public:
		PreferencesDialog(QWidget * parent = 0);
		~PreferencesDialog(){};

	private:
                PrefsDataStoreWidget * m_prefsData;
		PrefsLNFWidget * m_prefsLNF;
                PrefsEditorWidget * m_prefsEditor;

		//! \brief Update editor preview for new color/font values.
		void resetEditorPreview();

	private slots:
		void restoreDefaults();
                bool saveSettings();
		void activeHighlightButton_clicked();
		void shortcutsButton_clicked();
		//
		void fontComboBox_activated(int);
		void fontSizeSpin_valueChanged(int);

                void mainSelBtn_clicked();
                void indexSelBtn_clicked();
                void backSelBtn_clicked();
                void exportSelBtn_clicked();

                void accept();
};


#endif
