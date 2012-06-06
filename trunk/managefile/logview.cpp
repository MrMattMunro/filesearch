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
#include <QProgressDialog>
#include <QProgressDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QShortcut>
#include <QSettings>
#include <QDateTime>

#include <qscintilla2/Qt4/Qsci/qscilexer.h>

#include "preferences.h"
#include "logview.h"
#include "sqlkeywords.h"
#include "utils.h"
#include "db/database.h"


LogView::LogView(QWidget * parent)
        : QDialog(parent),
   	  m_fileWatcher(0)
{
	ui.setupUi(this);

	m_fileName = QString();
	ui.sqlTextEdit->prefsChanged();

        actionSearch = new QAction(Utils::getIcon("help_viewer.png"),tr("&Help"), this);
        actionSearch->setShortcut(tr("Ctrl+F"));
        connect(actionSearch, SIGNAL(triggered()), this, SLOT(actionSearch_triggered()));

        ui.searchFrame->show();

        QShortcut * alternativeSQLRun = new QShortcut(this);
        alternativeSQLRun->setKey(Qt::CTRL + Qt::Key_F);
        connect(alternativeSQLRun, SIGNAL(activated()), this, SLOT(actionSearch_triggered()));

	ui.previousToolButton->setIcon(Utils::getIcon("go-previous.png"));
	ui.nextToolButton->setIcon(Utils::getIcon("go-next.png"));

        connect(parent, SIGNAL(prefsChanged()), ui.sqlTextEdit, SLOT(prefsChanged()));

        connect(ui.searchEdit, SIGNAL(textChanged(const QString &)), this, SLOT(searchEdit_textChanged(const QString &)));
	connect(ui.previousToolButton, SIGNAL(clicked()), this, SLOT(findPrevious()));
	connect(ui.nextToolButton, SIGNAL(clicked()), this, SLOT(findNext()));
	connect(ui.searchEdit, SIGNAL(returnPressed()), this, SLOT(findNext()));

        QString logfile = Utils::getSaveLogPath().append(QDir::separator()).append("mflog.log");
        open(logfile);

        QCursor lastrow;
        lastrow.setPos(QPoint(0, 1000));
        ui.sqlTextEdit->setCursor(lastrow);

        ui.sqlTextEdit->setWindowTitle(tr("Log Viewer"));
}

LogView::~LogView()
{
}

void LogView::showEvent(QShowEvent * event)
{
	ui.sqlTextEdit->setFocus();
}

void LogView::open(const QString &  newFile)
{
	QFile f(newFile);
	if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::warning(this, tr("Open SQL Script"), tr("Cannot open file %1").arg(newFile));
		return;
	}

	int prgTmp = 0;
	ui.sqlTextEdit->clear();

	QTextStream in(&f);
	QString line;
	QStringList strList;
	while (!in.atEnd())
	{
		line = in.readLine();
		strList.append(line);
		prgTmp += line.length();
	}

	f.close();

	m_fileName = newFile;
	setFileWatcher(newFile);

	ui.sqlTextEdit->append(strList.join("\n"));
}


void LogView::action_Save_triggered()
{
	if (m_fileName.isNull())
	{
		actionSave_As_triggered();
		return;
	}
	saveFile();
}

void LogView::actionSave_As_triggered()
{
	QString newFile = QFileDialog::getSaveFileName(this, tr("Save SQL Script"),
			QDir::currentPath(), tr("SQL file (*.sql);;All Files (*)"));
	if (newFile.isNull())
		return;
	m_fileName = newFile;
	setFileWatcher(newFile);
	saveFile();
}

void LogView::saveFile()
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
		out << ui.sqlTextEdit->text();
		f.close();
   	   	ui.sqlTextEdit->setModified(false);

		setFileWatcher(m_fileName);
   	}
}

bool LogView::changedConfirm()
{
	if (ui.sqlTextEdit->isModified())
	{
		int ret = QMessageBox::question(this, tr("New File"),
					tr("All you changes will be lost. Are you sure?"),
					QMessageBox::Yes, QMessageBox::No);
	
		if (ret == QMessageBox::No)
			return false;
	}
	return true;
}

void LogView::saveOnExit()
{
	if (!ui.sqlTextEdit->isModified())
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

void LogView::setFileName(const QString & fname)
{
	open(fname);
}

void LogView::actionSearch_triggered()
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

void LogView::find(QString ttf, bool forward/*, bool backward*/)
{
        bool found = ui.sqlTextEdit->findFirst(ttf,false,ui.caseCheckBox->isChecked(),
									ui.wholeWordsCheckBox->isChecked(),
									true,
									forward);
         ui.sqlTextEdit->highlightAllOccurrences(ttf, ui.caseCheckBox->isChecked(), ui.wholeWordsCheckBox->isChecked());
	QPalette p = ui.searchEdit->palette();
	p.setColor(QPalette::Active, QPalette::Base, found ? Qt::white : QColor(255, 102, 102));
	ui.searchEdit->setPalette(p);
}

void LogView::searchEdit_textChanged(const QString &)
{
	findNext();
}

void LogView::findNext()
{
	find(ui.searchEdit->text(), true);
}

void LogView::findPrevious()
{
	find(ui.searchEdit->text(), false);
}

void LogView::externalFileChange(const QString & path)
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

void LogView::setFileWatcher(const QString & newFileName)
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
