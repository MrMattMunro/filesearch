#pragma once
#ifndef INDEXFILE_H
#define INDEXFILE_H
#endif // INDEXFILE_H
#include <jvm.h>
#include <utils.h>
#include <preferences.h>
#include <QDebug.h>
#include <QThread>

class IndexFilesObj:public QObject {
    Q_OBJECT
    public:
        IndexFilesObj(){}
    public slots:
       void indexfiles()
       {
           Jvm jvm;
           QString indexpath = Utils::getLocateIndexPath();
           QMap<QString, QString> map;
           map.insert("indexpath",indexpath);

           QString dbpath = Utils::getLocateDbPath();
           dbpath.append(QDir::separator()).append("MF");
           map.insert("dbpath",dbpath);

           bool ret = jvm.invokeMethod("com/searchlocal/lucene/IndexMaker", "makeindex", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z", map);
           if(ret){
               Preferences* p = Preferences::instance();
               p->setIsIndexing(false);
           }
       }
       void indexfile(Doc doc)
       {
           Jvm jvm;
           QString indexpath = Utils::getLocateIndexPath();
           QMap<QString, QString> map;
           map.insert("indexpath",indexpath);

           QString dbpath = Utils::getLocateDbPath();
           dbpath.append(QDir::separator()).append("MF");
           map.insert("dbpath",dbpath);

           map.insert("docuuid",doc.DOCUMENT_GUID);
           map.insert("filepath",doc.DOCUMENT_LOCATION);

           jvm.invokeMethod("com/searchlocal/lucene/IndexMaker", "makeindex", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z", map);
       }
};
class IndexFilesSign:public QObject {
    Q_OBJECT
    public:
        IndexFilesSign(QObject* parent=0):QObject(parent){
        }
   public slots:
        void emitsig()   {
           emit sig();
        }
   signals:
       void sig();
};

class DelIndexFilesObj:public QObject {
    Q_OBJECT
    public:
        DelIndexFilesObj(){}
  //      QList<Doc> deldocs;
    public slots:
       void delIndexfiles()
       {
           Jvm jvm;
           QString indexpath = Utils::getLocateIndexPath();
           QMap<QString, QString> map;
           map.insert("indexpath",indexpath);

           QString dbpath = Utils::getLocateDbPath();
           dbpath.append(QDir::separator()).append("MF");
           map.insert("dbpath",dbpath);

           qDebug()<<"slot thread:"<< QThread::currentThreadId();

           QList<Doc> deldocs = DocDao::selectDocsByDelFlg("1");
           for(int i = 0; i < deldocs.size(); i++ ){
                Doc doc = deldocs.at(i);
                map.insert("docuuid",doc.DOCUMENT_GUID);
                map.insert("filepath",doc.DOCUMENT_LOCATION);
                jvm.invokeMethod("com/searchlocal/lucene/IndexMaker", "deleteIndex", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z", map);
           }
       }
       void delIndexfile(QString filepath, QString docUuid)
       {
           Jvm jvm;
           QString indexpath = Utils::getLocateIndexPath();
           QMap<QString, QString> map;
           map.insert("indexpath",indexpath);

           QString dbpath = Utils::getLocateDbPath();
           dbpath.append(QDir::separator()).append("MF");
           map.insert("dbpath",dbpath);
           map.insert("docuuid", docUuid);
           map.insert("filepath", filepath);
           jvm.invokeMethod("com/searchlocal/lucene/IndexMaker", "deleteIndex", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z", map);
       }
};
class DelIndexFilesSign:public QObject {
    Q_OBJECT
    public:
        DelIndexFilesSign(QObject* parent=0):QObject(parent){
        }
   public slots:
        void emitDelIndexFile()   {
           emit sigDelIndexFile();
        }
   signals:
       void sigDelIndexFile();

};

class QueryIndexFilesObj:public QObject {
    Q_OBJECT
    public:
        QueryIndexFilesObj(){}
        QString searchType;
        QString keyWord;
    public slots:
       void queryfiles()
       {
          qDebug()<<"from thread slot:" << QThread::currentThreadId();
          Jvm jvm;

          QString indexpath = Utils::getLocateIndexPath();
          QString dbpath = Utils::getLocateDbPath();
          dbpath.append(QDir::separator()).append("MF");

          QMap<QString, QString> map;
          map.insert("searchtype",searchType);
          map.insert("keyword",keyWord);
          map.insert("indexpath",indexpath);
          map.insert("dbpath",dbpath);
          bool rtn = jvm.invokeMethod("com/searchlocal/lucene/ContentSearcher", "queryAll", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z", map);
          if(rtn){
              emit finished();
          }
       }
    signals:
        void finished();
};
class QueryIIndexFilesSign:public QObject {
    Q_OBJECT
    public:
        QueryIIndexFilesSign(QObject* parent=0):QObject(parent){
        }
   public slots:
        void emitsig()   {
           emit sig();
        }
   signals:
       void sig();
};
