#include "UeSave.h"
#include <QMessageBox>
#include <QWebView>
#include <QWebFrame>
#include <QDebug>
#include <QApplication>
#include <preferences.h>
#include <utils.h>
#include <db/notedao.h>
#include <db/docdao.h>
#include <QUuid>
#include <QApplication>
#include <QTextDocument>
#include <QTextCodec>
#include "indexfile.h"

extern QWebView* view;
class QWebFrame;

UeSave::UeSave(QWidget *parent) :
    QLabel(parent)
{
    qDebug()<< "UeSave::UeSave () "<<  endl;
}

UeSave::~UeSave()
{
        qDebug()<<"UeSave::~UeSave ()"<<endl;
}

// 从页面js调用
void UeSave::save(QString content, QString plainText)
{
     // 清除空格
     plainText = plainText.trimmed();
     content = content.trimmed();

     Preferences* p = Preferences::instance();
     QString selNoteUuid = p->getSelNoteUid();

     // 保证note不为空
     QString notename = plainText.left(plainText.length() > 20 ? 20: plainText.length());
     notename = notename.replace(" ","");

     if(notename.trimmed().isEmpty()){
         QString m_docUuid = p->getSelDocUid();
         Doc doc = DocDao::selectDoc(m_docUuid);
         notename = doc.DOCUMENT_NAME + tr("_note");
     }

     // 判断是否修改笔记还是追加笔记
     if(selNoteUuid.isEmpty()){
         selNoteUuid = QUuid::createUuid().toString();
         // 插入note表
         Note note;
         note.NOTE_GUID = selNoteUuid;
         //加入docUuid 主要判断NotesDialog删除某一标注后后,再编辑保存该标注，
         //解决方法：直接关闭该窗体
         p->setSelNoteUid(selNoteUuid);

         QString m_docUuid = p->getSelDocUid();
         note.NOTE_NAME = notename;
         note.DOCUMENT_GUID = m_docUuid;
         note.NOTE_CONTENT = plainText;
         note.PAGE = 0;
         note.ROW = 0;
         note.COLUMN = 0;
         note.MF_VERSION = 0;
         NoteDao::insertNote(note);
     }else{
         Note note = NoteDao::selectNote(selNoteUuid);
         QString notesPath = Utils::getLocateNotesPath();
         QString delfilename = notesPath.append(QDir::separator());
         delfilename.append(note.NOTE_NAME);
         delfilename.append(".html");

         QFileInfo file(delfilename);
         if(file.exists()){
             QFile::remove(delfilename);
         }

         note.NOTE_NAME = notename;
         note.NOTE_CONTENT = plainText;
         note.MF_VERSION = note.MF_VERSION + 1;
         NoteDao::updateNote(note);

         // 删除index
         DelIndexFilesObj delindexFilesObj;
         delindexFilesObj.delIndexfile(delfilename, note.NOTE_GUID);
     }

     QString notesPath = Utils::getLocateNotesPath();
     QString filename = notesPath.append(QDir::separator());
     filename.append(notename);
     filename.append(".html");

     QFile f( filename );
     if (!f.exists())
     {
         f.open(QIODevice::WriteOnly);
     }else{
         QFileInfo file(filename);
         if(file.exists()){
             QFile::remove(filename);
         }
         f.open(QIODevice::WriteOnly);
     }

     QTextCodec *code= QTextCodec::codecForName("utf8");
     QTextStream t( &f );
     t.setCodec(code); // 输出流的设置编码

     t << content;
     f.close();

     // 加入index
     IndexFilesObj indexFilesObj;
     Doc doc;
     doc.DOCUMENT_GUID = p->getSelNoteUid();
     doc.DOCUMENT_LOCATION = filename;
     indexFilesObj.indexfile(doc);

     // 页面消息
     QString success = tr("save success");
     QString strVal = QString("savesuccess(\"%1\");").arg(success);
     view->page()->mainFrame()->evaluateJavaScript(strVal);
}
