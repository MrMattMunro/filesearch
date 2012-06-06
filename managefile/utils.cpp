/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/

#include <QIcon>
#include <QPixmapCache>
#include <QDir>
#include <QDesktopServices>
#include <QApplication>
#include <QListWidgetItem>
#include <QObject>
#include "utils.h"

#define ICON_DIR ":/icons"
#define TRANSLATION_DIR ":/ts"



QIcon Utils::getIcon(const QString & fileName)
{
	QPixmap pm;

	if (! QPixmapCache::find(fileName, &pm))
	{
                QPixmap npm(QString(ICON_DIR) + QDir::separator() + fileName);
		QPixmapCache::insert(fileName, npm);
		return npm;
	}

	return pm;
}

QPixmap Utils::getPixmap(const QString & fileName)
{
        return QPixmap(QString(ICON_DIR)  + QDir::separator() + fileName);
}

QString Utils::getTranslator(const QString & localeName)
{
    QString local(localeName);
    if( localeName == "zh"){
        local = "zh_cn";
    }

    return QString("%1/managefile_%2.qm").arg(TRANSLATION_DIR).arg(local);
}

bool Utils::updateObjectTree(const QString & sql)
{
	if (sql.isNull())
		return false;
	QString tmp(sql.trimmed().toUpper());
	if (tmp.left(4) == "DROP" || tmp.left(6) == "CREATE" || tmp.left(5) == "ALTER")
		return true;
	return false;
}

QString Utils::getLocatePath()
{
    QString locpath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
    locpath.append(QDir::separator()).append("slfile");
    QDir *dir=new QDir(locpath);
    if(!dir->exists()){
       dir->mkdir(locpath);
    }
    return locpath;
}

QString Utils::getLocateNotesPath()
{
    QString locpath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
    locpath.append(QDir::separator()).append("slfile");
    locpath.append(QDir::separator()).append("note");
    QDir *dir=new QDir(locpath);
    if(!dir->exists()){
       dir->mkdir(locpath);
    }
    return locpath;
}

QString Utils::getLocateIndexPath()
{
    QString locpath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
    locpath.append(QDir::separator()).append("slfile");
    locpath.append(QDir::separator()).append("index");
    QDir *dir=new QDir(locpath);
    if(!dir->exists()){
       dir->mkdir(locpath);
    }
    return locpath;
}

QString Utils::getLocateDbPath()
{
    QString locpath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
    locpath.append(QDir::separator()).append("slfile");
    locpath.append(QDir::separator()).append("db");
    QDir *dir=new QDir(locpath);
    if(!dir->exists()){
       dir->mkdir(locpath);
    }
    return locpath;
}

QString Utils::getSavePagePath()
{
    QString locpath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
    locpath.append(QDir::separator()).append("slfile");
    locpath.append(QDir::separator()).append("page");
    QDir *dir=new QDir(locpath);
    if(!dir->exists()){
       dir->mkdir(locpath);
    }
    return locpath;
}

QString Utils::getSaveDocPath()
{
    QString locpath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
    locpath.append(QDir::separator()).append("slfile");
    locpath.append(QDir::separator()).append("doc");
    QDir *dir=new QDir(locpath);
    if(!dir->exists()){
       dir->mkdir(locpath);
    }
    return locpath;
}

QString Utils::getSaveLogPath()
{
    QString locpath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
    locpath.append(QDir::separator()).append("slfile");
    locpath.append(QDir::separator()).append("log");
    QDir *dir=new QDir(locpath);
    if(!dir->exists()){
       dir->mkdir(locpath);
    }
    return locpath;
}

// 根据目录path取得最底层目录名
QString Utils::getDirNameByPath(const QString & path)
{
    QString temp = path;
    temp = temp.right(temp.length() - temp.lastIndexOf(QDir::separator()) - 1);
    return temp;
}

QDir Utils::directoryOf(const QString & subdir)
{

    QDir dir(QApplication::applicationDirPath());
    #if defined(Q_OS_WIN)
        if (dir.dirName().toLower() == "debug"
                || dir.dirName().toLower() == "release"
                || dir.dirName().toLower() == "bin"){
            dir.cdUp();
        }

    #elif defined(Q_OS_MAC)
        if (dir.dirName() == "MacOS") {
            dir.cdUp();
            dir.cdUp();
            dir.cdUp();
        }
    #endif
    dir.cd(subdir);
    return dir;
}







