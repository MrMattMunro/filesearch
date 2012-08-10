/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QLabel>
#include <QDebug>
#include <QProgressDialog>
#include <QProgressDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QShortcut>
#include <QSettings>
#include <QDateTime>
#include <QTextCodec>

#include "preferences.h"
#include "txteditor.h"
#include "sqlkeywords.h"
#include "utils.h"
#include "db/database.h"


TxtEditor::TxtEditor(QWidget * parent)
	: QMainWindow(parent),
          m_fileWatcher(0)
{

	ui.setupUi(this);

	m_fileName = QString();

        actionSearch = new QAction(Utils::getIcon("help_viewer.png"),tr("&Help"), this);
        actionSearch->setShortcut(tr("Ctrl+F"));
        connect(actionSearch, SIGNAL(triggered()), this, SLOT(actionSearch_triggered()));

        ui.searchFrame->hide();
        QShortcut * alternativeSQLRun = new QShortcut(this);
        alternativeSQLRun->setKey(Qt::CTRL + Qt::Key_F);
        connect(alternativeSQLRun, SIGNAL(activated()), this, SLOT(actionSearch_triggered()));

	ui.previousToolButton->setIcon(Utils::getIcon("go-previous.png"));
	ui.nextToolButton->setIcon(Utils::getIcon("go-next.png"));

	QSettings settings("yarpen.cz", "sqliteman");
        restoreState(settings.value("TxtEditor/state").toByteArray());

      connect(parent, SIGNAL(prefsChanged()), ui.sqlTextEdit, SLOT(prefsChanged()));

      connect(ui.searchEdit, SIGNAL(textChanged(const QString &)), this, SLOT(searchEdit_textChanged(const QString &)));
      connect(ui.previousToolButton, SIGNAL(clicked()), this, SLOT(findPrevious()));
      connect(ui.nextToolButton, SIGNAL(clicked()), this, SLOT(findNext()));
      connect(ui.searchEdit, SIGNAL(returnPressed()), this, SLOT(findNext()));
}

TxtEditor::~TxtEditor()
{
	QSettings settings("yarpen.cz", "sqliteman");
        settings.setValue("TxtEditor/state", saveState());
}

void TxtEditor::showEvent(QShowEvent * event)
{
	ui.sqlTextEdit->setFocus();
}

void TxtEditor::open(const QString &  newFile)
{
	QFile f(newFile);
	if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
	{
                QMessageBox::warning(this, tr("Open File"), tr("Cannot open file %1").arg(newFile));
		return;
	}


        QTextCodec *code= QTextCodec::codecForName("utf8");
	QTextStream in(&f);
        in.setCodec(code); // 输出流的设置编码
	QString line;
	while (!in.atEnd())
	{
                QString temp = in.readLine();
                line.append(temp);
                line.append("\n");
	}

        ui.sqlTextEdit->setPlainText(line);
	f.close();

	m_fileName = newFile;
	setFileWatcher(newFile);
}


void TxtEditor::action_Save_triggered()
{
	if (m_fileName.isNull())
	{
		actionSave_As_triggered();
		return;
	}
	saveFile();
}

void TxtEditor::actionSave_As_triggered()
{
        QString newFile = QFileDialog::getSaveFileName(this, tr("Save"),
                        QDir::currentPath(), tr("All Files (*)"));
	if (newFile.isNull())
		return;
	m_fileName = newFile;
	setFileWatcher(newFile);
	saveFile();
}

void TxtEditor::saveFile()
{
	QFile f(m_fileName);
	if (!f.open(QIODevice::WriteOnly | QIODevice::Text))
	{
                QMessageBox::warning(this, tr("Save File"),
							 tr("Cannot write into file %1").arg(m_fileName));
	}
	else
	{
   	   	// required for Win 
	   	delete(m_fileWatcher);
		m_fileWatcher = 0;

		QTextStream out(&f);
                // out << sqlTextEdit->text();
		f.close();
//   	   	sqlTextEdit->setModified(false);

		setFileWatcher(m_fileName);
   	}
}

bool TxtEditor::changedConfirm()
{
        if (ui.sqlTextEdit->document()->isModified())
        {
                int ret = QMessageBox::question(this, tr("New File"),
                                        tr("All you changes will be lost. Are you sure?"),
                                        QMessageBox::Yes, QMessageBox::No);
	
                if (ret == QMessageBox::No)
                        return false;
        }
	return true;
}

void TxtEditor::saveOnExit()
{
        if (!ui.sqlTextEdit->document()->isModified())
                return;
	int ret = QMessageBox::question(this, tr("Closing SQL Editor"),
				tr("Document has been changed. Do you want do save its content?"),
				QMessageBox::Yes, QMessageBox::No);
	
	if (ret == QMessageBox::No)
			return;
	if (m_fileName.isNull())
		actionSave_As_triggered();
	else
		saveFile();
}

void TxtEditor::setFileName(const QString & fname)
{
	open(fname);
}

void TxtEditor::actionSearch_triggered()
{
    if(!ui.searchFrame->isVisible()){
         ui.searchFrame->show();
    }else{
         ui.searchFrame->hide();
    }

    if (!ui.searchFrame->isVisible())
    {
         ui.sqlTextEdit->setFocus();
         return;
    }
    ui.searchEdit->selectAll();
    ui.searchEdit->setFocus();
}

void TxtEditor::find(QString ttf, bool forward/*, bool backward*/)
{
         QTextDocument* document = ui.sqlTextEdit->document();
         document->undo();

         //bool found = ui.sqlTextEdit->find(ttf, QTextDocument::FindBackward);
         // ui.sqlTextEdit->highlightAllOccurrences(ttf, ui.caseCheckBox->isChecked(), ui.wholeWordsCheckBox->isChecked());
//         QPalette p = ui.searchEdit->palette();
//         p.setColor(QPalette::Active, QPalette::Base, found ? Qt::white : QColor(255, 102, 102));
//         ui.searchEdit->setPalette(p);

        // bool found = ui.sqlTextEdit->find(ttf, QTextDocument::FindBackward);

        // ui.sqlTextEdit->highlightAllOccurrences(ttf, ui.caseCheckBox->isChecked(), ui.wholeWordsCheckBox->isChecked());
//        QPalette p = ui.searchEdit->palette();
//        p.setColor(QPalette::Active, QPalette::Base, found ? Qt::white : QColor(255, 102, 102));
//        ui.searchEdit->setPalette(p);

         bool found = false;
         QTextCursor highlightCursor(document);

         QTextCursor cursor(document);
         cursor.beginEditBlock();
         QTextCharFormat plainFormat(highlightCursor.charFormat());
         QTextCharFormat colorFormat=plainFormat;
         colorFormat.setBackground(Qt::yellow);

         while(!highlightCursor.isNull() && !highlightCursor.atEnd()){

             highlightCursor = document->find(ttf, highlightCursor, QTextDocument::FindWholeWords);
             qDebug() << highlightCursor.isNull();
             if(!highlightCursor.isNull()){
                 found=true;
                 highlightCursor.movePosition(QTextCursor::WordRight,QTextCursor::KeepAnchor);
                 highlightCursor.mergeCharFormat(colorFormat);
             }
         }
         cursor.endEditBlock();
}

void TxtEditor::setCursorPos(int row,int col)
{
    QTextBlock block = ui.sqlTextEdit->document()->findBlockByLineNumber(row -1);
    if(block.isValid()){
      // QTextCursor cursor = QTextEdit::text;
    }
}

void TxtEditor::searchEdit_textChanged(const QString &)
{
       findNext();
}

void TxtEditor::findNext()
{
      find(ui.searchEdit->text(), true);
}

void TxtEditor::findPrevious()
{
	find(ui.searchEdit->text(), false);
}

void TxtEditor::externalFileChange(const QString & path)
{
   	int b = QMessageBox::information(this, tr("Unexpected File Change"),
									 tr("Your currently edited file has been changed outside " \
									 "this application. Do you want to reload it?"),
									 QMessageBox::Yes | QMessageBox::No,
									 QMessageBox::Yes);
	if (b != QMessageBox::Yes)
		return;
	open(path);
}

void TxtEditor::setFileWatcher(const QString & newFileName)
{
	if (m_fileWatcher)
		m_fileWatcher->removePaths(m_fileWatcher->files());
	else
	{
		m_fileWatcher = new QFileSystemWatcher(this);
	   	connect(m_fileWatcher, SIGNAL(fileChanged(const QString &)),
			this, SLOT(externalFileChange(const QString &)));
	}

	m_fileWatcher->addPath(newFileName);
}
