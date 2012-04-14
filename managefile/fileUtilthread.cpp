#include "filethread.h"
#include <iostream>
FileThread::FileThread(QString fileName)
{
    this->fileName = fileName;
}
FileThread::FileThread()
{

}
void FileThread::setFileName(QString fileName)
{
    this->fileName = fileName;
}

void FileThread::run()
{

    QTextCodec *code;
    code = QTextCodec::codecForName("gb18030");
    code->fromUnicode(fileName).data();
    qDebug() << "FileThread::run before open" ;
    QDesktopServices::openUrl ( QUrl::fromLocalFile(fileName) );
// QDesktopServices::openUrl(QUrl(fileName, QUrl::StrictMode));
    qDebug() << "FileThread::run after open" ;
    //emit finished();
    emit terminate();
}

//void FileThread::finished()
//{
//     qDebug() << "finish cccc" ;
//}

FileThread::~FileThread()
{
     qDebug() << "aaaa" ;

}
