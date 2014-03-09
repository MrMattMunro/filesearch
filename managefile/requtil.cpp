#include <QFileDialog>
#include <QMessageBox>

#include <QtDebug>
#include <QDir>
#include <QUuid>
#include <QStandardItemModel>
#include <QDateTime>
#include <QTextCodec>
#include <QSslError>
#include <QEventLoop>
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
    loop = new QEventLoop;
}

//链接请求
void ReqUtil::startRequest(QUrl url)
{

    reply = manager->get(QNetworkRequest(url));
    connect(reply,SIGNAL(finished()),this,SLOT(httpFinished()));  //下载完成后
    connect(reply,SIGNAL(readyRead()),this,SLOT(httpReadyRead())); //有可用数据时
    // 判断异常
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),this, SLOT(slotError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(slotSslErrors(QList<QSslError>)));

    connect(reply,SIGNAL(finished()),loop,SLOT(quit()));  // 退出循环
    loop->exec();
}

// 出错
void ReqUtil::slotError(QNetworkReply::NetworkError error)
{
     hasError = true;
}
// 出错
void ReqUtil::slotSslErrors(QList<QSslError> temp)
{
     hasError = true;
}
//有可用数据
bool ReqUtil::getError()
{
     return hasError;
}

//有可用数据
void ReqUtil::httpReadyRead()
{
//    file = new QFile("temp.json");
//    if(file->open(QIODevice::WriteOnly)){
//        if (file){
            rtnStr = reply->readAll();
//            file->write(bytes);
            QString rtnString = QString(rtnStr);
            // 判断是否404异常
             qDebug() << "rtnString::" << rtnString;

            // http://go.microsoft.com/fwlink/?linkid=8180">Microsoft ???</a>&ldquo;HTTP&rdquo;&ldquo;404
            if(rtnString.indexOf("404") != -1 && rtnString.indexOf("HTML") != -1 ){
                QMessageBox::warning(this, tr("Warning"), tr("The Server has Errors, Please Contact the Administrator!"), QMessageBox::Yes);
                QCoreApplication::exit(773);
            }
//        }
//    }
}
// 完成下载
void ReqUtil::httpFinished()
 {
//        if(file){
//            file->flush();
//            file->close();
//        }

     reply->deleteLater();
     reply = 0;
     emit reqfinished();
}

QVariantMap ReqUtil::getReply()
{

  //QJson::Parser parser;
  bool ok;
  //QVariantMap result = parser.parse(rtnStr,&ok).toMap();
  QString rtnString = QString(rtnStr);
  // 判断是否404异常
  qDebug() << "rtnString::" << rtnString;
//  -delete file;
//  -file = 0;


 // return result;

}
