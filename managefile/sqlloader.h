/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/

#ifndef SqlLoader_H
#define SqlLoader_H

#include <QObject>
#include <QMap>
#include <QColor>
#include <QFont>
#include <QVariant>

class SqlLoader : public QObject
{
Q_OBJECT
        public:
                SqlLoader(QObject *parent = 0);
                ~SqlLoader();

                static SqlLoader* instance();
		static void deleteInstance();
                static QString getSql(QString key);

	signals:

	private:
                static QMap<QString, QString> sqlMap;
                static SqlLoader* _instance;

};

#endif
