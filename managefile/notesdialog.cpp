#include <QFileDialog>
#include <QMessageBox>

#include <QtDebug>
#include <QDir>
#include <QMenu>
#include <QStandardItemModel>

#include "notesdialog.h"
#include "preferences.h"
#include "utils.h"
#include "db/notedao.h"

NotesDialog::NotesDialog(QWidget * parent, const QString & m_docUuid)
        : QDialog(parent),  m_docUuid(m_docUuid),  update(false)
{
	setupUi(this);
        // 列表
        model = new QStandardItemModel();
        // 新建Model
        model->setColumnCount(4);
        model->setHeaderData(0,Qt::Horizontal,tr("Positon"));
        model->setHeaderData(1,Qt::Horizontal,tr("Type"));
        model->setHeaderData(2,Qt::Horizontal,tr("Author"));
        model->setHeaderData(3,Qt::Horizontal,tr("Date"));
        model->setHeaderData(4,Qt::Horizontal,tr("NoteUid"));

        intNotes();

        // 传递选择的docUuid
        Preferences* p = Preferences::instance();
        p->setNoteDocUid(m_docUuid);

        this->setWindowIcon(Utils::getIcon("document-import.png"));
        this->setWindowTitle(tr("Document Notes"));

        setContextMenuPolicy(Qt::CustomContextMenu);
        connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequested(QPoint)));

        notesView->setSelectionBehavior(QAbstractItemView::SelectRows);
}
// 打开菜单
void NotesDialog::contextMenuRequested(const QPoint &pos)
{
    QMenu menu;
    selIndex = notesView->indexAt(pos);

    menu.addAction(tr("Add note"), this, SLOT(addNote()));
    menu.addAction(tr("Delect this note"), this, SLOT(deleteNote(selIndex)));
    menu.addAction(tr("Delect All notes"), this, SLOT(deleteAllNote()));


    menu.exec(QCursor::pos());
}

// 在主界面中打开添加备注
void NotesDialog::addNote()
{  
    QStandardItem* item = model->item(selIndex.row(), 4);
    QString noteuuid = qvariant_cast<QString>(item->data(Qt::DisplayRole));

    // 传递选择的docUuid
    Preferences* p = Preferences::instance();
    p->setSelNoteUid(noteuuid);

    emit showAddNoteWidget();
}

// 删除备注
void NotesDialog::deleteNote(QModelIndex index)
{
    QStandardItem* item = model->item(index.row(), 4);
    QString noteuuid = qvariant_cast<QString>(item->data(Qt::DisplayRole));
    NoteDao::deleteNote(noteuuid);
    model->removeRow(index.row());
}

// 删除所有备注
void NotesDialog::deleteAllNote()
{
    NoteDao::deleteNote(m_docUuid);
    model->clear();
}

// 确定按钮
void NotesDialog::intNotes(){

    QList<Note> notes = NoteDao::selectNotesbyDocUuId(m_docUuid);

    // 列出子目录文件
    for (int var = 0; var < notes.length(); ++var) {
             Note note = notes.at(var);
             // 形成位置信息
             QString position;
             if(note.PAGE != 0){
                 position.append(note.PAGE);
                 position.append(tr(" page"));
             }
             if(note.SHEETPAGE != ""){
                 position.append(tr("sheet "));
                 position.append(note.SHEETPAGE);

             }
             if(note.ROW != 0){
                 position.append(note.ROW);
                 position.append(tr(" row"));
             }
             if(note.COLUMN != 0){
                 position.append(note.COLUMN);
                 position.append(tr(" column"));
             }
             model->setData(model->index(var,0), position);
             model->setData(model->index(var,1),tr("text"));
             model->setData(model->index(var,2),note.NOTE_OWNER);
             model->setData(model->index(var,3),note.DT_MODIFIED);
             model->setData(model->index(var,4),note.NOTE_GUID);
    }

    notesView->setModel(model);
    notesView->resizeColumnsToContents();
    notesView->hideColumn(4);
}
