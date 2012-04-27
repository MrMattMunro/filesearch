
#include <QApplication>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlError>
#include <QTextStream>
#include <QVariant>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QObject>

#include "db/database.h"
#include "db/dirdao.h"
#include "db/sqlite3.h"

// 异常情况
void DirDao::exception(const QString & message)
{
        QMessageBox::critical(0, tr("SQL Error"), message);
}
// 插入文件夹
bool DirDao::insertDir(Dir dir)
{
    QString sql = Database::getSql("mf_insert_dir.sql");
    sql = sql.arg(dir.DIR_GUID, dir.DIR_PARENT_UUID, dir.DIR_NAME, dir.DIR_DESCRIPTION, dir.DIR_ICON,
                   QString::number(dir.DIR_ORDER), QString::number(dir.MF_VERSION));
    return Database::execSql(sql);
}
// 删除文件夹
bool DirDao::deleteDir(QString dirUuId)
{
    QString sql = Database::getSql("mf_delete_dir.sql");
    sql = sql.arg(dirUuId);
    return Database::execSql(sql);
}

// 根据父目录取得子目录
QList<Dir> DirDao::selectDirsbyParent(const QString & groupUuid)
{
    QString sql = Database::getSql("mf_select_dir_parent.sql");
    sql = sql.arg(groupUuid);
    QSqlQuery query = Database::execSelect(sql);

    QList<Dir> returnList;
    while (query.next()){
            Dir field;
            field.DIR_GUID = query.value(0).toString();
            field.DIR_NAME = query.value(1).toString();
            field.DIR_DESCRIPTION = query.value(2).toString();
            field.DIR_ICON = query.value(3).toString();
            field.DIR_ORDER = query.value(4).toInt();
            field.DT_MODIFIED = query.value(5).toChar();
            field.MF_VERSION = query.value(6).toInt();
            returnList.append(field);
    }
    return returnList;
}

// 根据标签uuId获取标签
Dir DirDao::selectDir(const QString & uuid)
{
    QString sql = Database::getSql("mf_select_dir_uuid.sql");
    sql = sql.arg(uuid);
    QSqlQuery query = Database::execSelect(sql);

    while (query.next()){
            Dir field;
            field.DIR_GUID = query.value(0).toString();
            field.DIR_PARENT_UUID = query.value(1).toString();
            field.DIR_NAME = query.value(2).toString();
            field.DIR_DESCRIPTION = query.value(3).toString();
            field.DIR_ICON = query.value(4).toString();
            field.DIR_ORDER = query.value(5).toInt();
            field.DT_MODIFIED = query.value(6).toChar();
            field.MF_VERSION = query.value(7).toInt();
            return field;
    }
}

// 更新目录
bool DirDao::updateDir(Dir dir){

    // 取得数据库原来的
    Dir orgDir = selectDir(dir.DIR_GUID);

    // 取得数据库存在的目录
    QString dirparentuuid = orgDir.DIR_PARENT_UUID;
    QString dirname = orgDir.DIR_NAME;
    QString dirdesp = orgDir.DIR_DESCRIPTION;
    QString diricon = orgDir.DIR_ICON;
    int dirorder = orgDir.DIR_ORDER;
    int version = orgDir.MF_VERSION;

    if(! dir.DIR_PARENT_UUID.isEmpty()){
       dirparentuuid = dir.DIR_DESCRIPTION;
    }

    if(! dir.DIR_NAME.isEmpty()){
       dirname = dir.DIR_NAME;
    }

    if(! dir.DIR_DESCRIPTION.isEmpty()){
       dirdesp = dir.DIR_DESCRIPTION;
    }

    if(! dir.DIR_ICON.isEmpty()){
       diricon = dir.DIR_ICON;
    }

    if(dir.DIR_ORDER != 0){
       dirorder = dir.DIR_ORDER;
    }

    if(dir.MF_VERSION != 0){
       version = dir.MF_VERSION;
    }

    QString sql = Database::getSql("mf_update_dir.sql");
    sql = sql.arg(dirparentuuid, dirname, dirdesp, diricon, QString::number(dirorder), QString::number(version), dir.DIR_GUID);
    return Database::execSql(sql);
}
