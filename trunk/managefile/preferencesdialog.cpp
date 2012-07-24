/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/

#include <QDir>
#include <QStyleFactory>
#include <QSettings>
#include <QColorDialog>
#include <QFileDialog>
#include "preferencesdialog.h"
#include "preferences.h"
#include "shortcuteditordialog.h"
#include "utils.h"
#include "extensionmodel.h"


PrefsDataStoreWidget::PrefsDataStoreWidget(QWidget * parent)
	: QWidget(parent)
{
	setupUi(this);
}

PrefsLNFWidget::PrefsLNFWidget(QWidget * parent)
	: QWidget(parent)
{
	setupUi(this);
}

PrefsEditorWidget::PrefsEditorWidget(QWidget * parent)
	: QWidget(parent)
{
	setupUi(this);

#if QT_VERSION < 0x040300
	useShortcutsBox->hide();
	shortcutsButton->hide();
#endif

}

PreferencesDialog::PreferencesDialog(QWidget * parent)
	: QDialog(parent)
{
	setupUi(this);

        m_prefsData = new PrefsDataStoreWidget(this);
	m_prefsLNF = new PrefsLNFWidget(this);
        m_prefsEditor = new PrefsEditorWidget(this);

	stackedWidget->addWidget(m_prefsLNF);
	stackedWidget->addWidget(m_prefsData);
        stackedWidget->addWidget(m_prefsEditor);
	stackedWidget->setCurrentIndex(0);

	listWidget->addItem(new QListWidgetItem(Utils::getIcon("preferences-desktop-display.png"),
                                                tr("Look and Feel"), listWidget));
	listWidget->addItem(new QListWidgetItem(Utils::getIcon("table.png"),
                                                tr("  Data Store"), listWidget));
	listWidget->addItem(new QListWidgetItem(Utils::getIcon("kate.png"),
                                                tr("  Txt Editor"), listWidget));
	listWidget->setCurrentRow(0);

        connect(m_prefsEditor->activeHighlightButton, SIGNAL(clicked()),
			this, SLOT(activeHighlightButton_clicked()));
	connect(buttonBox->button(QDialogButtonBox::RestoreDefaults),
			SIGNAL(clicked()), this, SLOT(restoreDefaults()));
        connect(buttonBox->button(QDialogButtonBox::Ok),
                        SIGNAL(clicked()), this, SLOT(saveSettings()));

        connect(m_prefsEditor->fontComboBox, SIGNAL(activated(int)),
			this, SLOT(fontComboBox_activated(int)));
        connect(m_prefsEditor->fontSizeSpin, SIGNAL(valueChanged(int)),
			this, SLOT(fontSizeSpin_valueChanged(int)));
        connect(m_prefsEditor->shortcutsButton, SIGNAL(clicked()),
			this, SLOT(shortcutsButton_clicked()));
	// change prefs widgets
	connect(listWidget, SIGNAL(currentRowChanged(int)),
			stackedWidget, SLOT(setCurrentIndex(int)));

	Preferences * prefs = Preferences::instance();

       // avail langs
        QDir d("ts", "*.qm");
        m_prefsLNF->languageComboBox->addItem(tr("From Locales"));
        foreach (QString f, d.entryList())
                m_prefsLNF->languageComboBox->addItem(f.remove("managefile_").remove(".qm"));
        m_prefsLNF->languageComboBox->setCurrentIndex(prefs->GUItranslator());

	m_prefsLNF->fontComboBox->setCurrentFont(prefs->GUIfont());
	m_prefsLNF->fontSpinBox->setValue(prefs->GUIfont().pointSize());
	m_prefsLNF->recentlyUsedSpinBox->setValue(prefs->recentlyUsedCount());
	m_prefsLNF->openLastDBCheckBox->setChecked(prefs->openLastDB());
	m_prefsLNF->openLastSqlFileCheckBox->setChecked(prefs->openLastSqlFile());

        // Data Store
        m_prefsData->mainPath->setText(prefs->getMainPath());
        m_prefsData->indexPath->setText(prefs->getIndexPath());
        m_prefsData->backPath->setText(prefs->getBackPath());
        m_prefsData->exportPath->setText(prefs->getExportPath());
        connect(m_prefsData->mainSelBtn, SIGNAL(clicked()), this, SLOT(mainSelBtn_clicked()));
        connect(m_prefsData->indexSelBtn, SIGNAL(clicked()), this, SLOT(indexSelBtn_clicked()));
        connect(m_prefsData->backSelBtn, SIGNAL(clicked()), this, SLOT(backSelBtn_clicked()));
        connect(m_prefsData->exportSelBtn, SIGNAL(clicked()), this, SLOT(exportSelBtn_clicked()));


        m_prefsEditor->fontComboBox->setCurrentFont(prefs->sqlFont());
        m_prefsEditor->fontSizeSpin->setValue(prefs->sqlFontSize());
        m_prefsEditor->useActiveHighlightCheckBox->setChecked(prefs->activeHighlighting());
        m_prefsEditor->activeHighlightButton->setPalette(prefs->activeHighlightColor());
        m_prefsEditor->useTextWidthMarkCheckBox->setChecked(prefs->textWidthMark());
        m_prefsEditor->textWidthMarkSpinBox->setValue(prefs->textWidthMarkSize());
        m_prefsEditor->useCompletionCheck->setChecked(prefs->codeCompletion());
        m_prefsEditor->completionLengthBox->setValue(prefs->codeCompletionLength());
        m_prefsEditor->useShortcutsBox->setChecked(prefs->useShortcuts());

        resetEditorPreview();

}

bool PreferencesDialog::saveSettings()
{
	Preferences * prefs = Preferences::instance();
	prefs->setGUItranslator(m_prefsLNF->languageComboBox->currentIndex());
	QFont guiFont(m_prefsLNF->fontComboBox->currentFont());
	guiFont.setPointSize(m_prefsLNF->fontSpinBox->value());
	prefs->setGUIfont(guiFont);
	prefs->setRecentlyUsedCount(m_prefsLNF->recentlyUsedSpinBox->value());
	prefs->setOpenLastDB(m_prefsLNF->openLastDBCheckBox->isChecked());
	prefs->setOpenLastSqlFile(m_prefsLNF->openLastSqlFileCheckBox->isChecked());

        // Data Store
        prefs->setMainPath( m_prefsData->mainPath->text());
        prefs->setIndexPath(m_prefsData->indexPath->text());
        prefs->setBackPath( m_prefsData->backPath->text());
        prefs->setExportPath( m_prefsData->exportPath->text());

	// sql editor
        prefs->setSqlFont(m_prefsEditor->fontComboBox->currentFont());
        prefs->setSqlFontSize(m_prefsEditor->fontSizeSpin->value());
        prefs->setActiveHighlighting(m_prefsEditor->useActiveHighlightCheckBox->isChecked());
        prefs->setActiveHighlightColor(m_prefsEditor->activeHighlightButton->palette().color(QPalette::Background));
        prefs->setTextWidthMark(m_prefsEditor->useTextWidthMarkCheckBox->isChecked());
        prefs->setTextWidthMarkSize(m_prefsEditor->textWidthMarkSpinBox->value());
        prefs->setCodeCompletion(m_prefsEditor->useCompletionCheck->isChecked());
        prefs->setCodeCompletionLength(m_prefsEditor->completionLengthBox->value());
        prefs->setUseShortcuts(m_prefsEditor->useShortcutsBox->isChecked());

	return true;
}

void PreferencesDialog::accept(){
    saveSettings();
    this->close();
}

void PreferencesDialog::restoreDefaults()
{
	m_prefsLNF->languageComboBox->setCurrentIndex(0);
	m_prefsLNF->recentlyUsedSpinBox->setValue(5);
	m_prefsLNF->openLastDBCheckBox->setChecked(true);
	m_prefsLNF->openLastSqlFileCheckBox->setChecked(true);

	QFont fTmp;
        m_prefsEditor->fontComboBox->setCurrentFont(fTmp);
        m_prefsEditor->fontSizeSpin->setValue(fTmp.pointSize());
        m_prefsEditor->useActiveHighlightCheckBox->setChecked(true);
        m_prefsEditor->activeHighlightButton->setPalette(Preferences::stdDarkColor());
        m_prefsEditor->useTextWidthMarkCheckBox->setChecked(true);
        m_prefsEditor->textWidthMarkSpinBox->setValue(75);
        m_prefsEditor->useCompletionCheck->setChecked(false);
        m_prefsEditor->completionLengthBox->setValue(3);
        m_prefsEditor->useShortcutsBox->setChecked(false);

        // Data Store
        m_prefsData->mainPath->setText(Utils::getLocatePath());
        m_prefsData->indexPath->setText(Utils::getLocateIndexPath());
        m_prefsData->backPath->setText(Utils::getBackUpPath());
        m_prefsData->exportPath->setText("");

	resetEditorPreview();

}


void PreferencesDialog::activeHighlightButton_clicked()
{
    QColor nCol = QColorDialog::getColor(m_prefsEditor->activeHighlightButton->palette().color(QPalette::Background), this);
    if (nCol.isValid())
    {
            m_prefsEditor->activeHighlightButton->setPalette(nCol);
            resetEditorPreview();
    }
}

void PreferencesDialog::shortcutsButton_clicked()
{
	ShortcutEditorDialog d;
	d.exec();
}

void PreferencesDialog::fontComboBox_activated(int)
{
	resetEditorPreview();
}

void PreferencesDialog::fontSizeSpin_valueChanged(int)
{
	resetEditorPreview();
}

void PreferencesDialog::mainSelBtn_clicked(){

    QString path = QFileDialog::getExistingDirectory(this, tr("Select existing directory"),
                                                    m_prefsData->mainPath->text(), QFileDialog::ShowDirsOnly);
    if (path.isEmpty()){
         return;
    }
    path = QDir::toNativeSeparators(path);
    m_prefsData->mainPath->setText(path);
}

void PreferencesDialog::indexSelBtn_clicked(){
    QString path = QFileDialog::getExistingDirectory(this, tr("Select existing directory"),
                                                    m_prefsData->indexPath->text(), QFileDialog::ShowDirsOnly);
    if (path.isEmpty()){
         return;
    }
    path = QDir::toNativeSeparators(path);
    m_prefsData->indexPath->setText(path);

}
void PreferencesDialog::backSelBtn_clicked(){
    QString path = QFileDialog::getExistingDirectory(this, tr("Select existing directory"),
                                                   m_prefsData->backPath->text(), QFileDialog::ShowDirsOnly);
    if (path.isEmpty()){
         return;
    }
    path = QDir::toNativeSeparators(path);
    m_prefsData->backPath->setText(path);

}
void PreferencesDialog::exportSelBtn_clicked(){
    QString path = QFileDialog::getExistingDirectory(this, tr("Select existing directory"),
                                                   m_prefsData->exportPath->text(), QFileDialog::ShowDirsOnly);
    if (path.isEmpty()){
         return;
    }
    path = QDir::toNativeSeparators(path);
    m_prefsData->exportPath->setText(path);

}

void PreferencesDialog::resetEditorPreview()
{
//	QsciLexerSQL *lexer = qobject_cast<QsciLexerSQL*>(m_prefsSQL->syntaxPreviewEdit->lexer());

//	QFont newFont(m_prefsSQL->fontComboBox->currentFont());
//	newFont.setPointSize(m_prefsSQL->fontSizeSpin->value());
//	lexer->setFont(newFont);

//	lexer->setColor(m_syDefaultColor, QsciLexerSQL::Default);
//	lexer->setColor(m_syKeywordColor, QsciLexerSQL::Keyword);
//	QFont defFont(lexer->font(QsciLexerSQL::Keyword));
//	defFont.setBold(true);
//	lexer->setFont(defFont, QsciLexerSQL::Keyword);
//	lexer->setColor(m_syNumberColor, QsciLexerSQL::Number);
//	lexer->setColor(m_syStringColor, QsciLexerSQL::SingleQuotedString);
//	lexer->setColor(m_syStringColor, QsciLexerSQL::DoubleQuotedString);
//	lexer->setColor(m_syCommentColor, QsciLexerSQL::Comment);
//	lexer->setColor(m_syCommentColor, QsciLexerSQL::CommentLine);
//	lexer->setColor(m_syCommentColor, QsciLexerSQL::CommentDoc);
}
