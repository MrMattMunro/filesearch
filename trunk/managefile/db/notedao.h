#ifndef NoteDAO_H
#define NoteDAO_H

#include <QCoreApplication>
#include <QList>

typedef struct
{
        QString NOTE_GUID;
        QString DOCUMENT_GUID;
        QString NOTE_CONTENT;
        QString NOTE_OWNER;
        int PAGE;
        QString SHEETPAGE;
        int ROW;
        int COLUMN;
        QString  DT_MODIFIED;
}Note;

class NoteDao
{
            Q_DECLARE_TR_FUNCTIONS(NoteDao)
        public:
                // ≤Â»Î±Í«©
                static bool insertNote(Note note);
                static bool updateNote(Note note);
                static bool deleteNote(QString noteUuId);
                static bool deleteNoteByDoc(QString docUuId);
                static Note selectNote(const QString & uuid);
                static QList<Note> selectNotesbyDocUuId(const QString & docUuid);

        private:
                static void exception(const QString & message);
};

#endif
