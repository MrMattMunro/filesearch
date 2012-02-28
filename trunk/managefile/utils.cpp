/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/

#include <QIcon>
#include <QPixmapCache>
#include <QDir>

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

