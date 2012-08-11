
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
#include "db/notedao.h"
#include "db/sqlite3.h"
#include "sqlloader.h"

// 异常情况
void NoteDao::exception(const QString & message)
{
        QMessageBox::critical(0, tr("SQL Error"), message);
}
// 插入备注
bool NoteDao::insertNote(Note note)
{
    SqlLoader* sqlLoader = SqlLoader::instance();
    QString sql = sqlLoader->getSql("mf_insert_note.sql");
    sql = sql.arg(note.NOTE_GUID, note.DOCUMENT_GUID, note.NOTE_NAME, note.NOTE_CONTENT, note.NOTE_OWNER
                  , QString::number(note.PAGE), note.SHEETPAGE,  QString::number(note.ROW),  QString::number(note.COLUMN));
    return Database::execSql(sql);
}
// 删除备注
bool NoteDao::deleteNote(QString noteUuId)
{
    SqlLoader* sqlLoader = SqlLoader::instance();
    QString sql = sqlLoader->getSql("mf_delete_note.sql");
    sql = sql.arg(noteUuId);
    return Database::execSql(sql);
}
// 删除所有备注
bool NoteDao::deleteNoteByDoc(QString docUuId)
{
    SqlLoader* sqlLoader = SqlLoader::instance();
    QString sql = sqlLoader->getSql("mf_delete_note_docuuid.sql");
    sql = sql.arg(docUuId);
    return Database::execSql(sql);
}

// 根据Docuuid取得备注
QList<Note> NoteDao::selectNotesbyDocUuId(const QString & docUuid)
{
    SqlLoader* sqlLoader = SqlLoader::instance();
    QString sql = sqlLoader->getSql("mf_select_note_doc.sql");
    sql = sql.arg(docUuid);
    QSqlQuery query = Database::execSelect(sql);

    QList<Note> returnList;
    while (query.next()){
            Note field;
            field.NOTE_GUID = query.value(0).toString();
            field.DOCUMENT_GUID = query.value(1).toString();
            field.NOTE_NAME = query.value(2).toString();
            field.NOTE_CONTENT = query.value(3).toString();
            field.NOTE_OWNER = query.value(4).toString();
            field.PAGE = query.value(5).toInt();
            field.SHEETPAGE = query.value(6).toString();
            field.ROW = query.value(7).toInt();
            field.COLUMN = query.value(8).toInt();
            field.MF_VERSION = query.value(9).toInt();
            field.DT_MODIFIED = query.value(10).toString();
            returnList.append(field);
    }
    return returnList;
}

// 根据备注uuId获取备注
Note NoteDao::selectNote(const QString & uuid)
{
    SqlLoader* sqlLoader = SqlLoader::instance();
    QString sql = sqlLoader->getSql("mf_select_note_uuid.sql");
    sql = sql.arg(uuid);
    QSqlQuery query = Database::execSelect(sql);

    Note field;
    while (query.next()){
            field.NOTE_GUID = query.value(0).toString();
            field.DOCUMENT_GUID = query.value(1).toString();
            field.NOTE_NAME = query.value(2).toString();
            field.NOTE_CONTENT = query.value(3).toString();
            field.NOTE_OWNER = query.value(4).toString();
            field.PAGE = query.value(5).toInt();
            field.SHEETPAGE = query.value(6).toString();
            field.ROW = query.value(7).toInt();
            field.COLUMN = query.value(8).toInt();
            field.MF_VERSION = query.value(9).toInt();
            field.DT_MODIFIED = query.value(10).toString();
    }
    return field;
}

// 更新备注
bool NoteDao::updateNote(Note note){

    // 取得数据库原来的
    Note orgNote = selectNote(note.NOTE_GUID);

    QString docUuId = orgNote.DOCUMENT_GUID;
    QString noteName = orgNote.NOTE_NAME;
    QString noteContent = orgNote.NOTE_CONTENT;
    QString noteOwner = orgNote.NOTE_OWNER;
    int page = orgNote.PAGE;
    QString sheetpage = orgNote.SHEETPAGE;
    int row = orgNote.ROW;
    int column = orgNote.COLUMN;
    int version = orgNote.MF_VERSION;

    if(! note.DOCUMENT_GUID.isEmpty()){
       docUuId = note.DOCUMENT_GUID;
    }

    if(! note.NOTE_NAME.isEmpty()){
       noteName = note.NOTE_NAME;
    }

    if(! note.NOTE_CONTENT.isEmpty()){
       noteContent = note.NOTE_CONTENT;
    }

    if(! note.NOTE_OWNER.isEmpty()){
       noteOwner = note.NOTE_OWNER;
    }

    if(note.PAGE != 0){
       page = note.PAGE;
    }

    if(! note.SHEETPAGE.isEmpty()){
       sheetpage = note.SHEETPAGE;
    }

    if(note.ROW != 0){
       row = note.ROW;
    }

    if(note.COLUMN != 0){
       column = note.COLUMN;
    }

    if(note.MF_VERSION != 0){
       version = note.MF_VERSION;
    }

    SqlLoader* sqlLoader = SqlLoader::instance();
    QString sql = sqlLoader->getSql("mf_update_note.sql");
    sql = sql.arg(docUuId, noteName, noteContent, noteOwner, QString::number(page),
                  sheetpage, QString::number(row), QString::number(version), note.NOTE_GUID);
    return Database::execSql(sql);

      return true;
}
