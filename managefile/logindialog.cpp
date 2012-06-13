#include <QFileDialog>
#include <QMessageBox>

#include <QtDebug>
#include <QDir>
#include <QUuid>
#include <QStandardItemModel>
#include <QDateTime>

#include "logindialog.h"
#include "preferences.h"
#include "utils.h"
#include "db/docdao.h"
#include "db/dirdao.h"

// 登录界面
LoginDialog::LoginDialog(QWidget * parent)
        : QDialog(parent),
          update(false)
{
	setupUi(this);

        manager=new QNetworkAccessManager(this);

        connect(loginBtn, SIGNAL(clicked()), this, SLOT(loginBtn_clicked()));
        connect(registerBtn, SIGNAL(clicked()), this, SLOT(registerBtn_clicked()));
        connect(resetBtn, SIGNAL(clicked()), this, SLOT(resetBtn_clicked()));

        this->setWindowIcon(Utils::getIcon("file_manager.png"));
        this->setWindowTitle(tr("Slfile"));
        tabWidget->setCurrentIndex(0);

        QDir pathDir = Utils::directoryOf("html");
        QString path = pathDir.absolutePath();
        path.append(QDir::separator());
        path.append("welcome");
        path.append(QDir::separator());
        path.append("html");
        path.append(QDir::separator());
        path.append("welcome.html");

        welcome->load(QUrl::fromUserInput(path));
}

// 登录
void LoginDialog::loginBtn_clicked()
{
    QString surl;
    surl.append("http://www.slfile.net/mf-login.php?username=");
    surl.append(nameemail->text().trimmed());
    surl.append("&password=");
    QString pwd = Utils::getMD5Str(nameemail->text().trimmed());
    surl.append(pwd);
    url= QUrl::fromEncoded(surl.toUtf8());

    QFileInfo info(url.path());

    fileName=info.fileName(); //获取文件名
    if (fileName.isEmpty()) {
      fileName = "db.json";  //如果文件名为空，则使用db.json
    }else{
       fileName = "dbfm.json";
    }
    file = new QFile(fileName);
    if(file->open(QIODevice::WriteOnly))
    {
        startRequest(url);  //进行链接请求
    } else{
          //如果打开文件失败，则删除file，并使file指针为0，然后返回
          qDebug() << "file open error";
          delete file;
          file = 0;
          return;
    }

    update = true;
    this->close();
}

// 注册
void LoginDialog::registerBtn_clicked()
{

//    $usrname = $_GET['username'];
//	$email = $_GET['email'];
//	$pwd = $_GET['pwd'];
//	$guid = $_GET['guid'];


    QString surl;
    surl.append("http://www.slfile.net/mf-signup.php?username=");
    surl.append(username->text().trimmed());
    surl.append("&pwd=");
    QString spwd = Utils::getMD5Str(pwd->text().trimmed());
    surl.append(spwd);
    surl.append("&email=");
    QString semail = email->text().trimmed();
    surl.append(semail);
    surl.append("&guid=");
    QString guid = QUuid::createUuid().toString();
    surl.append(guid);

    url= QUrl::fromEncoded(surl.toUtf8());

    QFileInfo info(url.path());

    fileName=info.fileName(); //获取文件名
    if (fileName.isEmpty()) {
      fileName = "db.json";  //如果文件名为空，则使用db.json
    }else{
       fileName = "dbfm.json";
    }
    file = new QFile(fileName);
    if(file->open(QIODevice::WriteOnly))
    {
        startRequest(url);  //进行链接请求
    } else{
          //如果打开文件失败，则删除file，并使file指针为0，然后返回
          qDebug() << "file open error";
          delete file;
          file = 0;
          return;
    }
}

// 重置
void LoginDialog::resetBtn_clicked(){


}

//链接请求
void LoginDialog::startRequest(QUrl url)
{
    reply = manager->get(QNetworkRequest(url));
    connect(reply,SIGNAL(finished()),this,SLOT(httpFinished()));  //下载完成后
    connect(reply,SIGNAL(readyRead()),this,SLOT(httpReadyRead())); //有可用数据时
}

//有可用数据
void LoginDialog::httpReadyRead()
{
  if (file){
      file->write((reply->readAll()));
  }
}
// 完成下载
void LoginDialog::httpFinished()
 {
     file->flush();
     file->close();
     reply->deleteLater();
     reply = 0;
     // TODO 存在Setting里，开始读取file里的返回值 是否验证通过

     //delete file;
     file = 0;
}




