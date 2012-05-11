#include <QFileDialog>
#include <QMessageBox>

#include <QtDebug>
#include <QDir>
#include <QMenu>
#include <QStandardItemModel>

#include "notesdialog.h"
#include "preferences.h"
#include "utils.h"
#include "fileutils.h"
#include "db/notedao.h"
#include "db/docdao.h"

NotesDialog::NotesDialog(QWidget * parent): QDialog(parent),  update(false)
{
	setupUi(this);
        // 列表
        model = new QStandardItemModel();
        // 新建Model
        model->setColumnCount(6);
        model->setHeaderData(0,Qt::Horizontal,tr("Positon"));
        model->setHeaderData(1,Qt::Horizontal,tr("Type"));
        model->setHeaderData(2,Qt::Horizontal,tr("Content"));
        model->setHeaderData(3,Qt::Horizontal,tr("Author"));
        model->setHeaderData(4,Qt::Horizontal,tr("Date"));
        model->setHeaderData(5,Qt::Horizontal,tr("NoteUid"));

        intNotes();

        // 传递选择的docUuid
        Preferences* p = Preferences::instance();
        m_docUuid = p->getNoteDocUid();

        if(! m_docUuid.isEmpty()){
            Doc doc = DocDao::selectDoc(m_docUuid);
            m_docPath = doc.DOCUMENT_LOCATION;
            this->setWindowTitle(doc.DOCUMENT_NAME);
        }

        this->setWindowIcon(Utils::getIcon("document-import.png"));

        setContextMenuPolicy(Qt::CustomContextMenu);
        connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequested(QPoint)));

}

// 打开菜单
void NotesDialog::contextMenuRequested(const QPoint &pos)
{
    QMenu menu;
    selIndex = notesView->indexAt(pos);

    menu.addAction(tr("Add note"), this, SLOT(addNote()));
    menu.addAction(tr("Delete this note"), this, SLOT(deleteNote()));
    menu.addAction(tr("Edit this note"), this, SLOT(editNote()));
    menu.addAction(tr("Delete All notes"), this, SLOT(deleteAllNote()));

    menu.exec(QCursor::pos());
}

// 在主界面中打开添加备注
void NotesDialog::addNote()
{  
    // 清空SelNoteUid
    Preferences* p = Preferences::instance();
    p->setSelNoteUid("");

    emit showAddNoteWidget();
    this->close();
}

// 删除备注
void NotesDialog::deleteNote()
{
    int ret = QMessageBox::question(this, "", tr("Are you sure that delete the note ?"),
                                    QMessageBox::Yes, QMessageBox::No);

    if(ret == QMessageBox::Yes){

        QItemSelectionModel *selections = notesView->selectionModel();
        QModelIndexList selected = selections->selectedIndexes();
        QMap<int, int> rowMap;
        // 删除文件
        QString notespath = Utils::getLocateNotesPath();

        foreach (QModelIndex index, selected)
        {
            rowMap.insert(index.row(), 0);

            QStandardItem* item = model->item(index.row(), 5);
            QString noteuuid = qvariant_cast<QString>(item->data(Qt::DisplayRole));
            NoteDao::deleteNote(noteuuid);

            noteuuid.append(".html");
            noteuuid.prepend(QDir::separator());
            QFileInfo file(noteuuid.prepend(notespath));
            if(file.exists()){
                FileUtils::deleteDirectory(file);
            }
        }

        int rowToDel;
        QMapIterator<int, int> rowMapIterator(rowMap);
        rowMapIterator.toBack();
        while (rowMapIterator.hasPrevious())
        {
            rowMapIterator.previous();
            rowToDel = rowMapIterator.key();
            model->removeRow(rowToDel);
        }
    }

    // 清空SelNoteUid
    Preferences* p = Preferences::instance();
    p->setSelNoteUid("");

    if(ret == QMessageBox::No){
       return;
    }
}

// 编辑备注 《直接显示在判断是否存在》
void NotesDialog::editNote()
{
    QItemSelectionModel *selections = notesView->selectionModel();
    QModelIndexList selected = selections->selectedIndexes();

    // 选择第一个
    QModelIndex index = selected.at(0);
    QStandardItem* item = model->item(index.row(), 5);
    QString noteuuid = qvariant_cast<QString>(item->data(Qt::DisplayRole));

    Preferences* p = Preferences::instance();
    p->setSelNoteUid(noteuuid);

    emit showAddNoteWidget();
    this->close();
}


// 删除所有备注
void NotesDialog::deleteAllNote()
{
    if(!m_docUuid.isEmpty()){
        //删除Note文件
        QList<Note> notes = NoteDao::selectNotesbyDocUuId(m_docUuid);
        // 列出子目录文件
        QString notespath = Utils::getLocateNotesPath();
        for (int var = 0; var < notes.length(); ++var) {
                 Note note = notes.at(var);
                 QString uuid = note.NOTE_GUID;
                 uuid.append(".html");
                 uuid.prepend(QDir::separator());
                 QFileInfo file(uuid.prepend(notespath));
                 if(file.exists()){
                     FileUtils::deleteDirectory(file);
                 }
        }
        // 删除Notes
        NoteDao::deleteNoteByDoc(m_docUuid);
        model->clear();
    }
}

// 确定按钮
void NotesDialog::intNotes(){

    Preferences* p = Preferences::instance();
    m_docUuid = p->getNoteDocUid();

    QList<Note> notes = NoteDao::selectNotesbyDocUuId(m_docUuid);

    // 列出子目录文件
    for (int var = 0; var < notes.length(); ++var) {
             Note note = notes.at(var);
             // 形成位置信息
             QString position;
             if(note.PAGE != 0){
                 position.append(QString::number(note.PAGE));
                 position.append(tr(" page"));
             }
             if(!note.SHEETPAGE.isEmpty()){
                 position.append(tr("sheet "));
                 position.append(note.SHEETPAGE);

             }
             if(note.ROW != 0){
                 position.append(QString::number(note.ROW));
                 position.append(tr(" row"));
             }

             if(note.COLUMN != 0){
                 position.append(QString::number(note.COLUMN));
                 position.append(tr(" column"));
             }

             QList<QStandardItem*> items;
             QStandardItem* iposition = new QStandardItem(position);
             QStandardItem* type = new QStandardItem(tr("text"));
             QString tmp = note.NOTE_CONTENT;
             tmp = (tmp.length() > 50 ? tmp.left(50).append("...") : tmp);
             QStandardItem* content = new QStandardItem(tmp);
             QStandardItem* owner = new QStandardItem(note.NOTE_OWNER);
             QStandardItem* dtmodify = new QStandardItem(note.DT_MODIFIED);
             QStandardItem* noteguid = new QStandardItem(note.NOTE_GUID);

             items << iposition ;
             items << type;
             items << content;
             items << owner;
             items << dtmodify;
             items << noteguid;
             model->appendRow(items);
    }

    notesView->setModel(model);
    notesView->setSelectionBehavior(QAbstractItemView::SelectRows);
    notesView->hideColumn(5);
    notesView->resizeColumnsToContents();
}
