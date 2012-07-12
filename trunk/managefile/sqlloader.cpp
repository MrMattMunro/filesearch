#include <QSettings>
#include <QApplication>
#include <QDir>
#include <QMap>

#include "sqlloader.h"
#include "db/database.h"
#include "utils.h"

SqlLoader* SqlLoader::_instance = 0;
QMap<QString, QString> SqlLoader::sqlMap;


SqlLoader::SqlLoader(QObject *parent)
 : QObject(parent)
{
    QDir dir(Utils::directoryOf("sql"));
    QFileInfoList fileInfoList = dir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList){
        if(fileInfo.fileName() == "." || fileInfo.fileName() == ".."){
           continue;
        }
        if(fileInfo.isFile() && fileInfo.suffix().endsWith("sql")){
           QString filename = fileInfo.fileName();
           QString filepath = fileInfo.filePath();
           sqlMap.insert(filename, Database::getSql(filepath));
        }
    }
}

SqlLoader::~SqlLoader()
{

}

SqlLoader* SqlLoader::instance()
{
    if (_instance == 0){
         _instance = new SqlLoader();
    }

    return _instance;
}

void SqlLoader::deleteInstance()
{
    if (_instance)
        delete _instance;
    _instance = 0;
}


QString SqlLoader::getSql(QString key)
{
  QString sql = sqlMap.value(key);
  return sql;
}

