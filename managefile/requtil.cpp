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
#include "db/docdao.h"
#include "db/dirdao.h"

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
            QByteArray bytes = reply->readAll();
            file->write(bytes);
            QString string;
            string = QString(bytes);
            // 判断是否404异常
            // http://go.microsoft.com/fwlink/?linkid=8180">Microsoft ???</a>&ldquo;HTTP&rdquo;&ldquo;404
            if(string.indexOf("404") != -1 && string.indexOf("HTML") != -1 ){
                QMessageBox::warning(this, tr("Warning"), tr("The Server has Errors, Please Contact the Administrator!"), QMessageBox::Yes);
                QCoreApplication::exit(773);
            }
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
