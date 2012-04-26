
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

// 异常情况
void NoteDao::exception(const QString & message)
{
        QMessageBox::critical(0, tr("SQL Error"), message);
}
// 插入备注
bool NoteDao::insertNote(Note Note)
{
    QString sql = Database::getSql("mf_insert_Note.sql");
//    sql = sql.arg(Note.NOTE_GUID,Note.Note_GROUP_GUID,Note.Note_NAME,Note.Note_DESCRIPTION, QString::number(Note.MF_VERSION));
    return Database::execSql(sql);
}
// 删除备注
bool NoteDao::deleteNote(QString noteUuId)
{
    QString sql = Database::getSql("mf_delete_note.sql");
    sql = sql.arg(noteUuId);
    return Database::execSql(sql);
}
// 删除所有备注
bool NoteDao::deleteNoteByDoc(QString docUuId)
{
    QString sql = Database::getSql("mf_delete_note_docuuid.sql");
    sql = sql.arg(docUuId);
    return Database::execSql(sql);
}

// 根据Docuuid取得备注
QList<Note> NoteDao::selectNotesbyDocUuId(const QString & docUuid)
{
    QString sql = Database::getSql("mf_select_note_doc.sql");
    sql = sql.arg(docUuid);
    QSqlQuery query = Database::execSelect(sql);

    QList<Note> returnList;
    while (query.next()){
            Note field;
            field.NOTE_GUID = query.value(0).toString();
            field.NOTE_CONTENT = query.value(1).toString();
            field.NOTE_OWNER = query.value(2).toString();
            field.PAGE = query.value(3).toInt();
            field.SHEETPAGE = query.value(4).toString();
            field.ROW = query.value(5).toInt();
            field.COLUMN = query.value(6).toInt();
            field.DT_MODIFIED = query.value(7).toChar();
            returnList.append(field);
    }
    return returnList;
}

// 根据备注uuId获取备注
Note NoteDao::selectNote(const QString & uuid)
{
    QString sql = Database::getSql("mf_select_Note_uuid.sql");
    sql = sql.arg(uuid);
    QSqlQuery query = Database::execSelect(sql);

    while (query.next()){
            Note field;
            field.NOTE_GUID = query.value(0).toString();
            field.NOTE_CONTENT = query.value(1).toString();
            field.NOTE_OWNER = query.value(2).toString();
            field.PAGE = query.value(3).toInt();
            field.SHEETPAGE = query.value(4).toString();
            field.ROW = query.value(5).toInt();
            field.COLUMN = query.value(6).toInt();
            field.DT_MODIFIED = query.value(7).toChar();
            return field;
    }
}

// 更新子备注
bool NoteDao::updateNote(Note note){

    // 取得数据库原来的
    Note orgNote = selectNote(note.NOTE_GUID);

//    QString Notename = orgNote.Note_NAME;
//    QString Notegroupuuid = orgNote.Note_GROUP_GUID;
//    QString Notedesp = orgNote.Note_DESCRIPTION;
//    int Noteversion = orgNote.MF_VERSION;

//    if(! Note.Note_NAME.isEmpty()){
//       Notename = Note.Note_NAME;
//    }
//    // 移动到顶级备注
//    Notegroupuuid = Note.Note_GROUP_GUID;
//    if(! Note.Note_DESCRIPTION.isEmpty()){
//       Notedesp = Note.Note_DESCRIPTION;
//    }

//    if(Note.MF_VERSION != 0){
//       Noteversion = Note.MF_VERSION;
//    }
//    QString sql = Database::getSql("mf_update_Note.sql");
//    sql = sql.arg(Notename, Notegroupuuid, Notedesp, QString::number(Noteversion), Note.Note_GUID);
//    return Database::execSql(sql);

      return true;
}
