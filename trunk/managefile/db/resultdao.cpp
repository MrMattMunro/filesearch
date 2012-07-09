
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
#include "db/resultdao.h"
#include "db/sqlite3.h"

// 异常情况
void ResultDao::exception(const QString & message)
{
        QMessageBox::critical(0, tr("SQL Error"), message);
}

// 前缀
QList<Result> ResultDao::selectByPrefix(const QString & keyword){
    QString sql = "SELECT * FROM MF_RESULT WHERE KEY_WORD LIKE '%1\%'";
    sql = sql.arg(keyword);
    QSqlQuery query = Database::execSelect(sql);

    QList<Result> returnList;
    while (query.next()){
            Result field;
            field.DOC_UUID = query.value(0).toString();
            field.KEY_WORD = query.value(1).toString();
            field.FILE_TYPE = query.value(2).toString();
            field.FILE_PATH = query.value(3).toString();
            field.FILE_NAME = query.value(4).toString();
            field.DESP = query.value(5).toString();
            field.CONTENT = query.value(6).toString();
            field.SHEET_NAME = query.value(7).toString();
            field.ROW_NB = query.value(8).toInt();
            field.PAGE = query.value(9).toInt();
            field.DT_CREATED= query.value(10).toString();
            returnList.append(field);
    }
    return returnList;
}


// 后缀
QList<Result> ResultDao::selectBySuffix(const QString & keyword){
    QString sql = "SELECT * FROM MF_RESULT WHERE KEY_WORD LIKE '\%%1'";
    sql = sql.arg(keyword);
    QSqlQuery query = Database::execSelect(sql);

    QList<Result> returnList;
    while (query.next()){
            Result field;
            field.DOC_UUID = query.value(0).toString();
            field.KEY_WORD = query.value(1).toString();
            field.FILE_TYPE = query.value(2).toString();
            field.FILE_PATH = query.value(3).toString();
            field.FILE_NAME = query.value(4).toString();
            field.DESP = query.value(5).toString();
            field.CONTENT = query.value(6).toString();
            field.SHEET_NAME = query.value(7).toString();
            field.ROW_NB = query.value(8).toInt();
            field.PAGE = query.value(9).toInt();
            field.DT_CREATED= query.value(10).toString();
            returnList.append(field);
    }
    return returnList;
}

// 中间
QList<Result> ResultDao::selectByMiddle(const QString & keyword){
    QString sql = "SELECT * FROM MF_RESULT WHERE KEY_WORD LIKE '\%%1\%'";
    sql = sql.arg(keyword);
    QSqlQuery query = Database::execSelect(sql);

    QList<Result> returnList;
    while (query.next()){
            Result field;
            field.DOC_UUID = query.value(0).toString();
            field.KEY_WORD = query.value(1).toString();
            field.FILE_TYPE = query.value(2).toString();
            field.FILE_PATH = query.value(3).toString();
            field.FILE_NAME = query.value(4).toString();
            field.DESP = query.value(5).toString();
            field.CONTENT = query.value(6).toString();
            field.SHEET_NAME = query.value(7).toString();
            field.ROW_NB = query.value(8).toInt();
            field.PAGE = query.value(9).toInt();
            field.DT_CREATED= query.value(10).toString();
            returnList.append(field);
    }
    return returnList;
}

// 完全相等
QList<Result> ResultDao::selectByFullEqual(const QString & keyword){
    QString sql = "SELECT DOCUMENT_GUID,KEY_WORD,FILE_TYPE,FILE_PATH,FILE_NAME,DESP,CONTENT,SHEET_NAME,ROW_NB,PAGE,DT_CREATED FROM MF_RESULT WHERE KEY_WORD = '%1'";
    sql = sql.arg(keyword);
    QSqlQuery query = Database::execSelect(sql);

    QList<Result> returnList;
    while (query.next()){
            Result field;
            field.DOC_UUID = query.value(0).toString();
            field.KEY_WORD = query.value(1).toString();
            field.FILE_TYPE = query.value(2).toString();
            field.FILE_PATH = query.value(3).toString();
            field.FILE_NAME = query.value(4).toString();
            field.DESP = query.value(5).toString();
            field.CONTENT = query.value(6).toString();
            field.SHEET_NAME = query.value(7).toString();
            field.ROW_NB = query.value(8).toInt();
            field.PAGE = query.value(9).toInt();
            field.DT_CREATED= query.value(10).toString();
            returnList.append(field);
    }
    return returnList;
}

