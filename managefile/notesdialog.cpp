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
#include "indexfile.h"

NotesDialog::NotesDialog(QWidget * parent): QDialog(parent),  update(false)
{
        setupUi(this);
        // 列表
        model = new QStandardItemModel();
        // 新建Model
        model->setColumnCount(6);
        model->setHeaderData(0,Qt::Horizontal,tr("Name"));
        model->setHeaderData(1,Qt::Horizontal,tr("Type"));
        model->setHeaderData(2,Qt::Horizontal,tr("Content"));
        model->setHeaderData(3,Qt::Horizontal,tr("Author"));
        model->setHeaderData(4,Qt::Horizontal,tr("Date"));
        model->setHeaderData(5,Qt::Horizontal,tr("NoteUid"));

        intNotes();

        // 传递选择的docUuid
        Preferences* p = Preferences::instance();
        m_docUuid = p->getSelDocUid();

        if(! m_docUuid.isEmpty()){
            Doc doc = DocDao::selectDoc(m_docUuid);
            m_docPath = doc.DOCUMENT_LOCATION;
            this->setWindowTitle(doc.DOCUMENT_NAME);
        }

        this->setWindowIcon(Utils::getIcon("notes.png"));

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
    QItemSelectionModel *selections = notesView->selectionModel();
    QModelIndexList selected = selections->selectedIndexes();

    if(selected.size() == 0){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select an note."), QMessageBox::Yes);
        return;
    }

    needCloseNoteWiget = false;
    int ret = QMessageBox::question(this, "", tr("Are you sure that delete the note ?"),
                                    QMessageBox::Yes, QMessageBox::No);
    if(ret == QMessageBox::Yes){

        QMap<int, int> rowMap;
        // 删除文件
        QString notespath = Utils::getLocateNotesPath();

        Preferences* p = Preferences::instance();

        foreach (QModelIndex index, selected)
        {
            rowMap.insert(index.row(), 0);

            QStandardItem* item = model->item(index.row(), 5);
            QString noteuuid = qvariant_cast<QString>(item->data(Qt::DisplayRole));

            if(noteuuid == p->getSelNoteUid()){
               needCloseNoteWiget = true;
            }

            //删除Note文件
            Note note = NoteDao::selectNote(noteuuid);
            QString notename = note.NOTE_NAME;
            notename.append(".html");
            notename.prepend(QDir::separator());
            QFileInfo file(notename.prepend(notespath));
            if(file.exists()){
                FileUtils::deleteDirectory(file);
            }
            // 删除note记录
            NoteDao::deleteNote(noteuuid);
            // 删除index
            DelIndexFilesObj indexFilesObj;
            indexFilesObj.delIndexfile(notename, note.NOTE_GUID);
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

    // 去关闭Note< 删除的Uuid正好是打开的Uuid>
    emit closeNoteWidget();

    if(ret == QMessageBox::No){
       return;
    }
}

// 编辑备注 《直接显示在判断是否存在》
void NotesDialog::editNote()
{
    QItemSelectionModel *selections = notesView->selectionModel();
    QModelIndexList selected = selections->selectedIndexes();

    if(selected.size() == 0){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select an note."), QMessageBox::Yes);
        return;
    }

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
    int ret = QMessageBox::question(this, "", tr("Are you sure that delete All the notes ?"),
                                    QMessageBox::Yes, QMessageBox::No);
    if(ret == QMessageBox::Yes){
            if(!m_docUuid.isEmpty()){
                //删除Note文件
                QList<Note> notes = NoteDao::selectNotesbyDocUuId(m_docUuid);
                // 列出子目录文件
                QString notespath = Utils::getLocateNotesPath();
                DelIndexFilesObj indexFilesObj;
                for (int var = 0; var < notes.length(); ++var) {
                         Note note = notes.at(var);
                         QString name = note.NOTE_NAME;
                         name.append(".html");
                         name.prepend(QDir::separator());
                         QFileInfo file(name.prepend(notespath));
                         if(file.exists()){
                             FileUtils::deleteDirectory(file);
                         }
                         // 删除index
                         indexFilesObj.delIndexfile(name, note.NOTE_GUID);
                }
                // 删除Notes
                NoteDao::deleteNoteByDoc(m_docUuid);
                model->clear();
            }
     }
     if(ret == QMessageBox::No){
           return;
      }
     // 去关闭Note
     needCloseNoteWiget = true;
     emit closeNoteWidget();
}

// 确定按钮
void NotesDialog::intNotes(){

    Preferences* p = Preferences::instance();
    m_docUuid = p->getSelDocUid();

    QList<Note> notes = NoteDao::selectNotesbyDocUuId(m_docUuid);

    // 列出子目录文件
    for (int var = 0; var < notes.length(); ++var) {
             Note note = notes.at(var);
             // 形成位置信息 TODO
//             QString position;
//             if(note.PAGE != 0){
//                 position.append(QString::number(note.PAGE));
//                 position.append(tr(" page"));
//             }
//             if(!note.SHEETPAGE.isEmpty()){
//                 position.append(tr("sheet "));
//                 position.append(note.SHEETPAGE);

//             }
//             if(note.ROW != 0){
//                 position.append(QString::number(note.ROW));
//                 position.append(tr(" row"));
//             }

//             if(note.COLUMN != 0){
//                 position.append(QString::number(note.COLUMN));
//                 position.append(tr(" column"));
//             }

             QList<QStandardItem*> items;
             QStandardItem* name = new QStandardItem(note.NOTE_NAME);
             QStandardItem* type = new QStandardItem(tr("text"));
             QString tmp = note.NOTE_CONTENT;
             tmp = (tmp.length() > 50 ? tmp.left(50).append("...") : tmp);
             QStandardItem* content = new QStandardItem(tmp);
             QStandardItem* owner = new QStandardItem(note.NOTE_OWNER);
             QStandardItem* dtmodify = new QStandardItem(note.DT_MODIFIED);
             QStandardItem* noteguid = new QStandardItem(note.NOTE_GUID);

             items << name ;
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
    // TODO 位置信息
    // notesView->hideColumn(0);
    notesView->resizeColumnsToContents();
}
