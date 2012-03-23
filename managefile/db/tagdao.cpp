
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
#include "db/tagdao.h"
#include "db/sqlite3.h"

// 异常情况
void TagDao::exception(const QString & message)
{
        QMessageBox::critical(0, tr("SQL Error"), message);
}
// 插入标签
bool TagDao::insertTag(const Tag & tag)
{
    QString sql = Database::getSql("mf_insert_tag.sql");
    //sql = sql.arg(tag.TAG_GUID,tag.TAG_GROUP_GUID,tag.TAG_NAME,tag.TAG_DESCRIPTION, tag.MF_VERSION);
    return Database::execSql(sql);
}

// 根据父标签取得子标签
QList<Tag> TagDao::selectTagsbyGroup(const QString & groupUuid)
{
    QString sql = Database::getSql("mf_select_tag_group.sql");
    sql = sql.arg(groupUuid);
    QSqlQuery query = Database::execSelect(sql);

    QList<Tag> returnList;
    while (query.next()){
            Tag field;
            field.TAG_GUID = query.value(0).toString();
            field.TAG_NAME = query.value(1).toString();
            field.TAG_DESCRIPTION = query.value(2).toString();
            field.DT_MODIFIED = query.value(3).toChar();
            field.MF_VERSION = query.value(4).toInt();
            returnList.append(field);
    }
    return returnList;
}

// 更新子标签
bool TagDao::updateTag(Tag tag){

//    UPDATE TABLE
//        MF_TAG
//    SET TAG_NAME=%1
//        AND TAG_DESCRIPTION=%2
//        AND TAG_GROUP_GUID=%3
//        AND MF_VERSION=%4
//        AND DT_MODIFIED=datetime(CURRENT_TIMESTAMP,'localtime')
//    WHERE TAG_GUID=%5

    QString sql = Database::getSql("mf_update_tag.sql");
    //sql = sql.arg(tag.TAG_NAME,tag.TAG_DESCRIPTION,tag.TAG_GROUP_GUID, tag.MF_VERSION, tag.TAG_GUID);
    return Database::execSql(sql);
}
