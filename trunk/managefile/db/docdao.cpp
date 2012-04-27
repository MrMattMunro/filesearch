
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
#include "db/docdao.h"
#include "db/sqlite3.h"

// 异常情况
void DocDao::exception(const QString & message)
{
        QMessageBox::critical(0, tr("SQL Error"), message);
}
// 插入文档
bool DocDao::insertDoc(Doc doc)
{

    QString sql_1 = Database::getSql("mf_insert_doc_1.sql");
    QString sql_2 = Database::getSql("mf_insert_doc_2.sql");
    QString sql_3 = Database::getSql("mf_insert_doc_3.sql");

//    sql = sql.arg(doc.DOCUMENT_GUID, doc.DOCUMENT_TITLE, doc.DIR_GUID, doc.DOCUMENT_LOCATION, doc.DOCUMENT_NAME, doc.DOCUMENT_SEO,
//                  doc.DOCUMENT_URL, doc.DOCUMENT_AUTHOR, doc.DOCUMENT_KEYWORDS, doc.DOCUMENT_TYPE, doc.DOCUMENT_OWNER, doc.DT_CREATED,
//                  doc.DT_MODIFIED, doc.DT_ACCESSED, doc.DOCUMENT_ICON_INDEX, QString::number(doc.DOCUMENT_SYNC), doc.DOCUMENT_PROTECT,
//                  doc.DOCUMENT_ENCODE, QString::number(doc.DOCUMENT_READ_COUNT), QString::number(doc.DOCUMENT_RELATE_COUNT),
//                  doc.DOCUMENT_INDEXFLG, doc.DOCUMENT_OPERFLG, doc.DELETE_FLAG, QString::number(doc.MF_VERSION));

    sql_1 = sql_1.arg(doc.DOCUMENT_GUID, doc.DOCUMENT_TITLE, doc.DIR_GUID, doc.DOCUMENT_LOCATION, doc.DOCUMENT_NAME, doc.DOCUMENT_SEO,
                  doc.DOCUMENT_URL, doc.DOCUMENT_AUTHOR, doc.DOCUMENT_KEYWORDS);
    sql_2 = sql_2.arg(doc.DOCUMENT_TYPE, doc.DOCUMENT_OWNER, doc.DT_CREATED,
                  doc.DT_MODIFIED, doc.DT_ACCESSED, QString::number(doc.DOCUMENT_ICON_INDEX), QString::number(doc.DOCUMENT_SYNC),
                  doc.DOCUMENT_PROTECT, doc.DOCUMENT_ENCODE);
    sql_3 = sql_3.arg(QString::number(doc.DOCUMENT_READ_COUNT), QString::number(doc.DOCUMENT_RELATE_COUNT),
                  doc.DOCUMENT_INDEXFLG, doc.DOCUMENT_OPERFLG, doc.DELETE_FLAG, QString::number(doc.MF_VERSION));

    QString sql;
    sql.append(sql_1);
    sql.append(sql_2);
    sql.append(sql_3);

    return Database::execSql(sql);
}
// 删除文档
bool DocDao::deleteDoc(QString DocUuId)
{
    QString sql = Database::getSql("mf_delete_doc.sql");
    sql = sql.arg(DocUuId);
    return Database::execSql(sql);
}

// 根据文件夹下所有文档
QList<Doc> DocDao::selectDocsbyDir(const QString & dirUuid)
{
    QString sql = Database::getSql("mf_select_docs_dir.sql");
    sql = sql.arg(dirUuid);
    QSqlQuery query = Database::execSelect(sql);

//    DOCUMENT_GUID,
//          DOCUMENT_TITLE,
//          DIR_GUID,
//          DOCUMENT_LOCATION,
//          DOCUMENT_NAME,
//          DOCUMENT_SEO,
//          DOCUMENT_URL,
//          DOCUMENT_AUTHOR,
//          DOCUMENT_KEYWORDS,
//          DOCUMENT_TYPE,
//          DOCUMENT_OWNER,
//          DT_CREATED,
//          DT_MODIFIED,
//          DT_ACCESSED,
//          DOCUMENT_ICON_INDEX,
//          DOCUMENT_SYNC,
//          DOCUMENT_PROTECT,
//          DOCUMENT_ENCODE,
//          DOCUMENT_READ_COUNT,
//          DOCUMENT_RELATE_COUNT,
//          DOCUMENT_INDEXFLG,
//          DOCUMENT_OPERFLG,
//          DELETE_FLAG,
//          MF_VERSION

    QList<Doc> returnList;
    while (query.next()){
            Doc field;
            field.DOCUMENT_GUID = query.value(0).toString();
            field.DOCUMENT_TITLE = query.value(1).toString();
            field.DIR_GUID = query.value(2).toString();
            field.DOCUMENT_LOCATION = query.value(3).toString();
            field.DOCUMENT_NAME = query.value(4).toString();
            field.DOCUMENT_SEO = query.value(5).toString();
            field.DOCUMENT_URL = query.value(6).toString();
            field.DOCUMENT_AUTHOR = query.value(7).toString();
            field.DOCUMENT_KEYWORDS = query.value(8).toString();
            field.DOCUMENT_TYPE = query.value(9).toString();
            field.DOCUMENT_OWNER = query.value(10).toString();
            field.DT_CREATED = query.value(11).toChar();
            field.DT_MODIFIED = query.value(12).toChar();
            field.DT_ACCESSED = query.value(13).toChar();
            field.DOCUMENT_ICON_INDEX = query.value(14).toInt();
            field.DOCUMENT_SYNC = query.value(15).toInt();
            field.DOCUMENT_PROTECT = query.value(16).toString();
            field.DOCUMENT_ENCODE = query.value(17).toChar();
            field.DOCUMENT_READ_COUNT = query.value(18).toInt();
            field.DOCUMENT_RELATE_COUNT = query.value(19).toInt();
            field.DOCUMENT_INDEXFLG = query.value(20).toChar();
            field.DOCUMENT_OPERFLG = query.value(21).toChar();
            field.DELETE_FLAG = query.value(22).toChar();
            field.MF_VERSION = query.value(23).toInt();
            returnList.append(field);
    }
    return returnList;
}

// 根据文档uuId获取文档
Doc DocDao::selectDoc(const QString & uuid)
{
    QString sql = Database::getSql("mf_select_doc_uuid.sql");
    sql = sql.arg(uuid);
    QSqlQuery query = Database::execSelect(sql);

    while (query.next()){
            Doc field;
            field.DOCUMENT_GUID = query.value(0).toString();
            field.DOCUMENT_TITLE = query.value(1).toString();
            field.DIR_GUID = query.value(2).toString();
            field.DOCUMENT_LOCATION = query.value(3).toString();
            field.DOCUMENT_NAME = query.value(4).toString();
            field.DOCUMENT_SEO = query.value(5).toString();
            field.DOCUMENT_URL = query.value(6).toString();
            field.DOCUMENT_AUTHOR = query.value(7).toString();
            field.DOCUMENT_KEYWORDS = query.value(8).toString();
            field.DOCUMENT_TYPE = query.value(9).toString();
            field.DOCUMENT_OWNER = query.value(10).toString();
            field.DT_CREATED = query.value(11).toChar();
            field.DT_MODIFIED = query.value(12).toChar();
            field.DT_ACCESSED = query.value(13).toChar();
            field.DOCUMENT_ICON_INDEX = query.value(14).toInt();
            field.DOCUMENT_SYNC = query.value(15).toInt();
            field.DOCUMENT_PROTECT = query.value(16).toString();
            field.DOCUMENT_ENCODE = query.value(17).toChar();
            field.DOCUMENT_READ_COUNT = query.value(18).toInt();
            field.DOCUMENT_RELATE_COUNT = query.value(19).toInt();
            field.DOCUMENT_INDEXFLG = query.value(20).toChar();
            field.DOCUMENT_OPERFLG = query.value(21).toChar();
            field.DELETE_FLAG = query.value(22).toChar();
            field.MF_VERSION = query.value(23).toInt();
            return field;
    }
}

// 更新文档
bool DocDao::updateDoc(Doc doc){

    // 取得数据库原来的
    Doc orgDoc = selectDoc(doc.DOCUMENT_GUID);

    //    QString DOCUMENT_TITLE;
    //    QString DIR_GUID;
    //    QString DOCUMENT_LOCATION;
    //    QString DOCUMENT_NAME;
    //    QString DOCUMENT_SEO;
    //    QString DOCUMENT_URL;
    //    QString DOCUMENT_AUTHOR;
    //    QString DOCUMENT_KEYWORDS;
    //    QString DOCUMENT_TYPE;
    //    QString DOCUMENT_OWNER;
    //    QChar DT_CREATED;
    //    QChar DT_MODIFIED;
    //    QChar DT_ACCESSED;
    //    QString DOCUMENT_ICON_INDEX;
    //    int DOCUMENT_SYNC;
    //    QString DOCUMENT_PROTECT;
    //    QChar DOCUMENT_ENCODE;
    //    int DOCUMENT_READ_COUNT;
    //    int DOCUMENT_RELATE_COUNT;
    //    QChar DOCUMENT_INDEXFLG;
    //    QChar DOCUMENT_OPERFLG;
    //    QChar DELETE_FLAG;
    //    int MF_VERSION;

    QString docTitle = orgDoc.DOCUMENT_TITLE;
    QString dirUuId = orgDoc.DIR_GUID;
    QString docLocation = orgDoc.DOCUMENT_LOCATION;
    QString docName = orgDoc.DOCUMENT_NAME;
    QString docSeo = orgDoc.DOCUMENT_SEO;
    QString docUrl = orgDoc.DOCUMENT_URL;
    QString docAuthor = orgDoc.DOCUMENT_AUTHOR;
    QString docKeyWord = orgDoc.DOCUMENT_KEYWORDS;
    QString docType = orgDoc.DOCUMENT_TYPE;
    QString docOwer = orgDoc.DOCUMENT_OWNER;
    QChar created = orgDoc.DT_CREATED;
    QChar modified = orgDoc.DT_MODIFIED;
    QChar accessed = orgDoc.DT_ACCESSED;
    QString iconIdx = orgDoc.DOCUMENT_ICON_INDEX;
    int docSync = orgDoc.DOCUMENT_SYNC;
    QString docProtect = orgDoc.DOCUMENT_PROTECT;
    QChar docEncode = orgDoc.DOCUMENT_ENCODE;
    int readCount = orgDoc.DOCUMENT_READ_COUNT;
    int relateCount = orgDoc.DOCUMENT_RELATE_COUNT;
    QChar idexFlg = orgDoc.DOCUMENT_INDEXFLG;
    QChar operFlg = orgDoc.DOCUMENT_OPERFLG;
    QChar delFlg = orgDoc.DELETE_FLAG;
    int version = orgDoc.MF_VERSION;

    if(! doc.DOCUMENT_TITLE.isEmpty()){
       docTitle = doc.DOCUMENT_TITLE;
    }
    if(! doc.DIR_GUID.isEmpty()){
       dirUuId = doc.DOCUMENT_TITLE;
    }
    if(! doc.DOCUMENT_LOCATION.isEmpty()){
       docLocation = doc.DOCUMENT_LOCATION;
    }
    if(! doc.DOCUMENT_NAME.isEmpty()){
       docName = doc.DOCUMENT_NAME;
    }
    if(! doc.DOCUMENT_SEO.isEmpty()){
       docSeo = doc.DOCUMENT_SEO;
    }
    if(! doc.DOCUMENT_URL.isEmpty()){
       docUrl = doc.DOCUMENT_URL;
    }
    if(! doc.DOCUMENT_AUTHOR.isEmpty()){
       docAuthor = doc.DOCUMENT_AUTHOR;
    }
    if(! doc.DOCUMENT_KEYWORDS.isEmpty()){
       docKeyWord = doc.DOCUMENT_KEYWORDS;
    }
    if(! doc.DOCUMENT_TYPE.isEmpty()){
       docType = doc.DOCUMENT_TYPE;
    }
    if(! doc.DOCUMENT_OWNER.isEmpty()){
       docOwer = doc.DOCUMENT_OWNER;
    }
    if(! doc.DT_CREATED.isNull()){
       created = doc.DT_CREATED;
    }
    if(! doc.DT_MODIFIED.isNull()){
       modified = doc.DT_MODIFIED;
    }
    if(! doc.DT_ACCESSED.isNull()){
       accessed = doc.DT_ACCESSED;
    }
    if(doc.DOCUMENT_ICON_INDEX != 0){
       iconIdx = doc.DOCUMENT_ICON_INDEX;
    }
    if(doc.DOCUMENT_SYNC != 0 ){
       docSync = doc.DOCUMENT_SYNC;
    }
    if(! doc.DOCUMENT_PROTECT.isEmpty()){
       docProtect = doc.DOCUMENT_PROTECT;
    }
    if(! doc.DOCUMENT_ENCODE.isNull()){
       docEncode = doc.DOCUMENT_ENCODE;
    }
    if(doc.DOCUMENT_READ_COUNT != 0 ){
       readCount = doc.DOCUMENT_READ_COUNT;
    }
    if(doc.DOCUMENT_RELATE_COUNT != 0 ){
       relateCount = doc.DOCUMENT_RELATE_COUNT;
    }
    if(! doc.DOCUMENT_INDEXFLG.isNull()){
       idexFlg = doc.DOCUMENT_INDEXFLG;
    }
    if(! doc.DOCUMENT_OPERFLG.isNull()){
       operFlg = doc.DOCUMENT_OPERFLG;
    }
    if(! doc.DELETE_FLAG.isNull()){
       delFlg = doc.DELETE_FLAG;
    }
    if(doc.MF_VERSION != 0 ){
       version = doc.MF_VERSION;
    }

    QString sql_1 = Database::getSql("mf_update_doc_1.sql");
    QString sql_2 = Database::getSql("mf_update_doc_2.sql");
    QString sql_3 = Database::getSql("mf_update_doc_3.sql");
    sql_1 = sql_1.arg(docTitle, dirUuId, docLocation, docName, docSeo, docUrl, docAuthor,
                  docKeyWord, docType);

    sql_2 = sql_2.arg(docOwer, created, modified, accessed, iconIdx, QString::number(docSync),
                  docProtect, docEncode, QString::number(readCount));

    sql_3 = sql_3.arg(QString::number(relateCount), idexFlg, operFlg,
                  delFlg, QString::number(version), doc.DOCUMENT_GUID);


    QString sql;
    sql.append(sql_1);
    sql.append(sql_2);
    sql.append(sql_3);

    return Database::execSql(sql);
}
