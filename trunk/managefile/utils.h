/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/

#ifndef UTILS_H
#define UTILS_H
#include <QString>
#include <QDir>
#include <QIcon>
#include <QPixmap>
#include <QListWidgetItem>

//! Various helper functions
namespace Utils {
	
/*! A set of helper functions for simpler code
*/
QIcon getIcon(const QString & fileName);
QPixmap getPixmap(const QString & fileName);

QString getTranslator(const QString & localeName);

//! \brief Check if the object tre should be refileld depending on sql statement
bool updateObjectTree(const QString & sql);
QString getLocatePath();
QString getLocateNotesPath();
QString getLocateIndexPath();
QString getLocateDbPath();
QString getSavePagePath();
QString getSaveDocPath();
QString getSaveLogPath();
QString getDirNameByPath(const QString & path);
QDir directoryOf(const QString & subdir);

};

#endif
