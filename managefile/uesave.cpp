#include "UeSave.h"
#include <QMessageBox>
#include <QWebView>
#include <QWebFrame>
#include <QDebug>
#include <QApplication>
#include <preferences.h>
#include <utils.h>
#include <db/notedao.h>
#include <QUuid>
#include <QApplication>
#include <QTextCodec>

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
     Preferences* p = Preferences::instance();
     QString selNoteUuid = p->getSelNoteUid();

     // 判断是否修改笔记还是追加笔记
     QString notesPath = Utils::getLocateNotesPath();
     QString filename = "";
     if(selNoteUuid.isEmpty()){
         filename = notesPath.append(QDir::separator());
         QString noteuuId = QUuid::createUuid().toString();
         filename.append(noteuuId);
         filename.append(".html");
         // 插入note表
         Note note;
         note.NOTE_GUID = noteuuId;
         //加入docUuid 主要判断NotesDialog删除某一标注后后,再编辑保存该标注，
         //解决方法：直接关闭该窗体
         p->setSelNoteUid(noteuuId);

         QString m_docUuid = p->getSelDocUid();
         note.DOCUMENT_GUID = m_docUuid;
         note.NOTE_CONTENT = plainText;
         NoteDao::insertNote(note);
     }else{
         // 更新note表
         filename = notesPath.append(QDir::separator());
         filename.append(selNoteUuid);
         filename.append(".html");

         Note note;
         note.NOTE_GUID = selNoteUuid;
         QString m_docUuid = p->getSelDocUid();
         note.DOCUMENT_GUID = m_docUuid;
         note.NOTE_CONTENT = plainText;
         NoteDao::updateNote(note);
     }

     QFile f( filename );
     if (!f.exists())
     {
         f.open(QIODevice::WriteOnly);
     }

     QTextCodec *code= QTextCodec::codecForName("utf8");
     QTextStream t( &f );
     t.setCodec(code); // 输出流的设置编码

     t << content;
     f.close();

     // 页面消息
     view->page()->mainFrame()->evaluateJavaScript("savesuccess();");
}

