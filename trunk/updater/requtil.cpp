#include <QFileDialog>
#include <QMessageBox>

#include <QtDebug>
#include <QDir>
#include <QUuid>
#include <QStandardItemModel>
#include <QDateTime>
#include <QTextCodec>
#include <qjson/parser.h>
#include <qjson/serializer.h>

#include "requtil.h"
#include "preferences.h"
#include "utils.h"

// 登录界面
ReqUtil::ReqUtil(QWidget * parent)
{
    manager=new QNetworkAccessManager(this);
}

//链接请求
void ReqUtil::startRequest(QUrl url)
{
    reply = manager->get(QNetworkRequest(url));
    connect(reply,SIGNAL(finished()),this,SLOT(httpFinished()));  //下载完成后
    connect(reply,SIGNAL(readyRead()),this,SLOT(httpReadyRead())); //有可用数据时
}

//有可用数据
void ReqUtil::httpReadyRead()
{
    file = new QFile("temp.json");
    if(file->open(QIODevice::WriteOnly)){
        if (file){
            file->write((reply->readAll()));
        }
    }
}
// 完成下载
void ReqUtil::httpFinished()
 {
     file->flush();
     file->close();
     reply->deleteLater();
     reply = 0;
     emit reqfinished();
}

QVariantMap ReqUtil::getReply()
{

  QJson::Parser parser;
  bool ok;
  QVariantMap result = parser.parse(file,&ok).toMap();
  delete file;
  file = 0;
  return result;

}





