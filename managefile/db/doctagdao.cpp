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
#include "db/doctagdao.h"
#include "db/sqlite3.h"
#include "sqlloader.h"

// 异常情况
void DocTagDao::exception(const QString & message)
{
        QMessageBox::critical(0, tr("SQL Error"), message);
}

// 插入文档标签
bool DocTagDao::insertDocTag(DocTag docTag)
{
    SqlLoader* sqlLoader = SqlLoader::instance();
    QString sql = sqlLoader->getSql("mf_insert_doctag.sql");
    sql = sql.arg(docTag.DOCUMENT_GUID, docTag.TAG_GUID);
    return Database::execSql(sql);
}
// 删除文档标签
bool DocTagDao::deleteDocTag(DocTag docTag)
{
    SqlLoader* sqlLoader = SqlLoader::instance();
    QString sql = sqlLoader->getSql("mf_delete_doctag.sql");
    sql = sql.arg(docTag.DOCUMENT_GUID, docTag.TAG_GUID);
    return Database::execSql(sql);
}
// 用TagUuId 删除文档标签
bool DocTagDao::deleteDocTagByTag(QString taguid)
{
    SqlLoader* sqlLoader = SqlLoader::instance();
    QString sql = sqlLoader->getSql("mf_delete_doctag_tag.sql");
    sql = sql.arg(taguid);
    return Database::execSql(sql);
}

// 删除某个文档所有标签
bool DocTagDao::deleteDocTagByDoc(QString docUuId)
{
    SqlLoader* sqlLoader = SqlLoader::instance();
    QString sql = sqlLoader->getSql("mf_delete_doctag_doc.sql");
    sql = sql.arg(docUuId);
    return Database::execSql(sql);
}

// 根据Docuuid取得文档标签 连接tag表及doctag表
QList<Tag> DocTagDao::selectTagsbyDocUuId(const QString & docUuid)
{
    SqlLoader* sqlLoader = SqlLoader::instance();
    QString sql = sqlLoader->getSql("mf_select_doctag_doc.sql");
    sql = sql.arg(docUuid);
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
