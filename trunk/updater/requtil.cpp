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
#include <QSslError>
#include <QCoreApplication>

#include "requtil.h"
#include "preferences.h"
#include "utils.h"

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

    rtnStr = reply->readAll();
    QString rtnString = QString(rtnStr);
    // 判断是否404异常
    qDebug() << "rtnString::" << rtnString;

}
// 完成下载
void ReqUtil::httpFinished()
 {
     if(reply->error()){
        hasError = true;
     }
     reply->deleteLater();
     reply = 0;
     emit reqfinished();
}

QVariantMap ReqUtil::getReply()
{

    QJson::Parser parser;
    bool ok;
    QVariantMap result = parser.parse(rtnStr,&ok).toMap();
    QString rtnString = QString(rtnStr);
    // 判断是否404异常
    qDebug() << "rtnString::" << rtnString;
    return result;
}
