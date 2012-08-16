
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
#include "sqlloader.h"

// 异常情况
void TagDao::exception(const QString & message)
{
        QMessageBox::critical(0, tr("SQL Error"), message);
}
// 插入标签
bool TagDao::insertTag(Tag tag)
{
    SqlLoader* sqlLoader = SqlLoader::instance();
    QString sql = sqlLoader->getSql("mf_insert_tag.sql");
    sql = sql.arg(tag.TAG_GUID, tag.TAG_GROUP_GUID, tag.TAG_NAME, tag.TAG_DESCRIPTION, QString::number(tag.MF_VERSION));
    return Database::execSql(sql);
}
// 删除标签
bool TagDao::deleteTag(QString tagUuId)
{
    SqlLoader* sqlLoader = SqlLoader::instance();
    QString sql = sqlLoader->getSql("mf_delete_tag.sql");
    sql = sql.arg(tagUuId);
    return Database::execSql(sql);
}

// 根据父标签取得子标签
QList<Tag> TagDao::selectTagsbyParent(const QString & groupUuid)
{
    SqlLoader* sqlLoader = SqlLoader::instance();
    QString sql = sqlLoader->getSql("mf_select_tag_group.sql");
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

// 递归迭代子标签取得所有层级子标签
void TagDao::selectAllSubTagbyTag(QList<Tag> & selTagList, const QString & tagUuid){

    QList<Tag> tmpList = selectTagsbyParent(tagUuid);
    selTagList.append(tmpList);
    if(tmpList.size() > 0){
        do
        {
            Tag first = (Tag)tmpList.takeFirst();
            selectAllSubTagbyTag(selTagList, first.TAG_GUID);

        }while(tmpList.size() != 0);
    }
}

// 根据标签uuId获取标签
Tag TagDao::selectTag(const QString & uuid)
{
    SqlLoader* sqlLoader = SqlLoader::instance();
    QString sql = sqlLoader->getSql("mf_select_tag_uuid.sql");
    sql = sql.arg(uuid);
    QSqlQuery query = Database::execSelect(sql);

    while (query.next()){
            Tag field;
            field.TAG_GUID = query.value(0).toString();
            field.TAG_NAME = query.value(1).toString();
            field.TAG_GROUP_GUID = query.value(2).toString();
            field.TAG_DESCRIPTION = query.value(3).toString();
            field.DT_MODIFIED = query.value(4).toChar();
            field.MF_VERSION = query.value(5).toInt();
            return field;
    }
}

// 取得所有标签
QList<Tag> TagDao::selectAllTags()
{
    QString sql = "SELECT TAG_GUID,TAG_NAME,TAG_GROUP_GUID,TAG_DESCRIPTION,DT_MODIFIED,MF_VERSION FROM MF_TAG ";
    QSqlQuery query = Database::execSelect(sql);
    QList<Tag> returnList;
    while (query.next()){
            Tag field;
            field.TAG_GUID = query.value(0).toString();
            field.TAG_NAME = query.value(1).toString();
            field.TAG_GROUP_GUID = query.value(2).toString();
            field.TAG_DESCRIPTION = query.value(3).toString();
            field.DT_MODIFIED = query.value(4).toChar();
            field.MF_VERSION = query.value(5).toInt();
            returnList.append(field);
    }
    return returnList;
}

// 更新子标签
bool TagDao::updateTag(Tag tag){

    // 取得数据库原来的
    Tag orgTag = selectTag(tag.TAG_GUID);

    QString tagname = orgTag.TAG_NAME;
    QString taggroupuuid = orgTag.TAG_GROUP_GUID;
    QString tagdesp = orgTag.TAG_DESCRIPTION;
    int tagversion = orgTag.MF_VERSION;

    if(! tag.TAG_NAME.isEmpty()){
       tagname = tag.TAG_NAME;
    }
    // 移动到顶级标签 是清空操作
    taggroupuuid = tag.TAG_GROUP_GUID;

    if(! tag.TAG_DESCRIPTION.isEmpty()){
       tagdesp = tag.TAG_DESCRIPTION;
    }

    if(tag.MF_VERSION != 0){
       tagversion = tag.MF_VERSION;
    }
    SqlLoader* sqlLoader = SqlLoader::instance();
    QString sql = sqlLoader->getSql("mf_update_tag.sql");
    sql = sql.arg(tagname, taggroupuuid, tagdesp, QString::number(tagversion), tag.TAG_GUID);
    return Database::execSql(sql);
}
