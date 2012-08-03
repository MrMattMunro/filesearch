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
#include <QCryptographicHash>
#include <QSysInfo>
#include <QNetworkInterface>


#include "utils.h"

#define ICON_DIR ":/icon"
#define TRANSLATION_DIR ":/ts"

// 取得操作系统
QString Utils::getSysOs()
{
    if (QSysInfo::WindowsVersion == QSysInfo::WV_32s){
        return "WV_32s";
    }
    if (QSysInfo::WindowsVersion == QSysInfo::WV_95){
        return "WV_95";
    }
    if (QSysInfo::WindowsVersion == QSysInfo::WV_98){
        return "WV_98";
    }
    if (QSysInfo::WindowsVersion == QSysInfo::WV_Me){
        return "WV_Me";
    }
    if (QSysInfo::WindowsVersion == QSysInfo::WV_NT){
        return "WV_NT";
    }
    if (QSysInfo::WindowsVersion == QSysInfo::WV_2000){
        return "WV_2000";
    }
    if (QSysInfo::WindowsVersion == QSysInfo::WV_XP){
        return "WV_XP";
    }
    if (QSysInfo::WindowsVersion == QSysInfo::WV_2003){
        return "WV_2003";
    }
    if (QSysInfo::WindowsVersion == QSysInfo::WV_VISTA){
        return "WV_VISTA";
    }

    return "";
}
// 取得IP
QString Utils::getIPAddress(){
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list)
    {
       if(address.protocol() == QAbstractSocket::IPv4Protocol){
           //IPv4地址
           if (address.toString().contains("127.0.")){
               continue;
           }
           return address.toString();
        }
   }
}

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

    return QString("%1/updater_%2.qm").arg(TRANSLATION_DIR).arg(local);
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

QString Utils::getBackUpPath()
{
    QString locpath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
    locpath.append(QDir::separator()).append("slfile");
    locpath.append(QDir::separator()).append("bakup");
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

QString Utils::getMD5Str(const QString & str)
{

    QString md5;
    QByteArray bb;
    bb = QCryptographicHash::hash (str.toAscii(), QCryptographicHash::Md5 );
    return md5.append(bb.toHex());
}

QString Utils::getSysLang()
{
    return QLocale::system().name().left(2);
}







