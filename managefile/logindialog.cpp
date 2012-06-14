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
        m_action = "";
}

// 登录
void LoginDialog::loginBtn_clicked()
{
    m_action = "login";
    QString surl;
    surl.append("http://www.slfile.net/mf-login.php?username=");
    surl.append(nameemail->text().trimmed());
    surl.append("&password=");
    QString pwd = Utils::getMD5Str(password->text().trimmed());
    surl.append(pwd);
    url= QUrl::fromEncoded(surl.toUtf8());

    file = new QFile("temp.json");
    if(file->open(QIODevice::WriteOnly))
    {
        startRequest(url);  //进行链接请求
    } else {
          //如果打开文件失败，则删除file，并使file指针为0，然后返回
          qDebug() << "file open error";
          delete file;
          file = 0;
          return;
    }

}

// 注册
void LoginDialog::registerBtn_clicked()
{
    m_action = "register";
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

    file = new QFile("temp.json");
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
    m_action = "reset";
    QString surl;
    surl.append("http://www.slfile.net/mf-forgetpwd.php?email=");
    surl.append(usremail->text().trimmed());
    url= QUrl::fromEncoded(surl.toUtf8());

    file = new QFile("temp.json");
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
     // 处理返回信息
     doReply();
     delete file;
     file = 0;
}

void LoginDialog::doReply()
{
  QString line;
  // 采用的是UTF8格式显示的
  QTextCodec *code=QTextCodec::codecForName("utf8");
   if(file->open(QIODevice::ReadOnly ))
    {
        QTextStream myStream(file);
        myStream.setCodec(code);//设置输出流
        do
        {
         line = myStream.readLine(); // 不包括“\n”的一行文本
         }
        while(!myStream.atEnd());
         file->close();
    }
  QJson::Parser parser;
  bool ok;
  QVariantMap result = parser.parse(file,&ok).toMap();
  QVariant verror = result["error"];
  QString error = qvariant_cast<QString>(verror);
  QVariant susername = result["username"];
  QString name = qvariant_cast<QString>(susername);

  if(error == "Server Errors"){
      QMessageBox::warning(this, tr("Warning"), tr("Server Failed, Please Contact Administrator"), QMessageBox::Yes);
  }
  // 注册失败
  if(error == "Sign up Failed"){
      QMessageBox::warning(this, tr("Warning"), tr("Sign up Failed, Please Contact Administrator"), QMessageBox::Yes);
  }
  if(error == "Username/email Have Existed"){
      QMessageBox::warning(this, tr("Warning"), name + tr(" : Username/Email have existed, Please Choose an other one"), QMessageBox::Yes);
  }
  // 登录失败
  if(error == "User Is Not Existed"){
      QMessageBox::warning(this, tr("Warning"), name + tr(" : Username/Email is not existed, Please confirm"), QMessageBox::Yes);
  }
  if(error == "Pwd Is Incorrect"){
      QMessageBox::warning(this, tr("Warning"), name + tr(" : Password is incorrect, Please confirm"), QMessageBox::Yes);
  }
  // 重置密码失败
  if(error == "Change Password Success, But Send Mail Failed Please Contact Administrator to get the Password"){
      QVariant semail = result["email"];
      QString tempemail = qvariant_cast<QString>(semail);
      QMessageBox::warning(this, tr("Warning"), tempemail + tr(" : Change Password Success, <br>But Send Mail Failed Please Contact Administrator to get the Password"), QMessageBox::Yes);
  }

  // 注册成功时
  if(m_action == "register" && error.isEmpty()){
      QMessageBox::information(this, tr("Information"), tr("Sign up Successed, Please Login in"), QMessageBox::Yes);
      tabWidget->setCurrentIndex(0);
  }

  // 登录成功时
  if(m_action == "login" && error.isEmpty()){
      // 处理Setting
      QVariant user_email = result["user_email"];
      QString  suser_email = qvariant_cast<QString>(user_email);

      QVariant username = result["username"];
      QString  susername = qvariant_cast<QString>(username);

      QVariant displayname = result["displayname"];
      QString  sdisplayname = qvariant_cast<QString>(displayname);

      QVariant score = result["score"];
      QString  sscore = qvariant_cast<QString>(score);

      QVariant dt_expired = result["dt_expired"];
      QString  sdt_expired = qvariant_cast<QString>(dt_expired);

      QVariant type = result["type"];
      QString  stype = qvariant_cast<QString>(type);

      QVariant store_limit = result["store_limit"];
      QString  sstore_limit = qvariant_cast<QString>(store_limit);

      QVariant store_used = result["store_used"];
      QString  sstore_used = qvariant_cast<QString>(store_used);

      QVariant traffic_limit = result["traffic_limit"];
      QString  straffic_limit = qvariant_cast<QString>(traffic_limit);

      QVariant traffic_used = result["traffic_used"];
      QString  straffic_used = qvariant_cast<QString>(traffic_used);

      QVariant last_sel_tags = result["last_sel_tags"];
      QString  slast_sel_tags = qvariant_cast<QString>(last_sel_tags);

      QVariant last_sel_dirs = result["last_sel_dirs"];
      QString  slast_sel_dirs = qvariant_cast<QString>(last_sel_dirs);

      QVariant last_open_docs = result["last_open_docs"];
      QString  slast_open_docs = qvariant_cast<QString>(last_open_docs);

      QVariant last_open_notes = result["last_open_notes"];
      QString  slast_open_notes = qvariant_cast<QString>(last_open_notes);

      QVariant last_open_urls = result["last_open_urls"];
      QString  slast_open_urls = qvariant_cast<QString>(last_open_urls);

      update = true;
      this->close();
  }

  // 重设置密码成功时
  if(m_action == "reset" && error.isEmpty()){
      // 处理Setting 通知服务器发送邮件
      QMessageBox::information(this, tr("Information"), tr("ReSet Password Successed, Please Check the email to get the new password"), QMessageBox::Yes);
      tabWidget->setCurrentIndex(0);
  }
}





