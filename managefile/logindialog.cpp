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

        connect(loginBtn, SIGNAL(clicked()), this, SLOT(loginBtn_clicked()));
        connect(registerBtn, SIGNAL(clicked()), this, SLOT(registerBtn_clicked()));
        connect(resetBtn, SIGNAL(clicked()), this, SLOT(resetBtn_clicked()));

        this->setWindowIcon(Utils::getIcon("file_manager.png"));
        this->setWindowTitle(tr("Slfile"));
        tabWidget->setCurrentIndex(0);

        QDir pathDir = Utils::directoryOf("html");
        QString path = pathDir.absolutePath();
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

    requtil = new ReqUtil(this);
    connect(requtil,SIGNAL(reqfinished()),this,SLOT(doReply()));

    QUrl url= QUrl::fromEncoded(surl.toUtf8());
    requtil->startRequest(url);
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
    surl.append("&ip=");
    QString ipAddr = Utils::getIPAddress();
    surl.append(ipAddr);
    surl.append("&os=");
    QString os = Utils::getSysOs();
    surl.append(os);
    surl.append("&lang=");
    QString lang = Utils::getSysLang();
    surl.append(lang);

    requtil = new ReqUtil(this);
    connect(requtil,SIGNAL(reqfinished()),this,SLOT(doReply()));

    QUrl url= QUrl::fromEncoded(surl.toUtf8());
    requtil->startRequest(url);
}

// 重置
void LoginDialog::resetBtn_clicked(){
    m_action = "reset";
    QString surl;
    surl.append("http://www.slfile.net/mf-forgetpwd.php?email=");
    surl.append(usremail->text().trimmed());

    requtil = new ReqUtil(this);
    connect(requtil,SIGNAL(reqfinished()),this,SLOT(doReply()));

    QUrl url= QUrl::fromEncoded(surl.toUtf8());
    requtil->startRequest(url);
}

// 处理服务器返回信息
void LoginDialog::doReply()
{
  QVariantMap result = requtil->getReply();

  QVariant verror = result["error"];
  QString error = qvariant_cast<QString>(verror);
  QVariant susername = result["username"];
  QString name = qvariant_cast<QString>(susername);

  if(error == "Server Errors"){
      QMessageBox::warning(this, tr("Warning"), tr("Server Failed, Please Contact Administrator"), QMessageBox::Yes);
      return;
  }
  // 注册失败
  if(error == "Sign up Failed"){
      QMessageBox::warning(this, tr("Warning"), tr("Sign up Failed, Please Contact Administrator"), QMessageBox::Yes);
      return;
  }
  if(error == "Username/email Have Existed"){
      QMessageBox::warning(this, tr("Warning"), name + tr(" : Username/Email have existed, Please Choose an other one"), QMessageBox::Yes);
      return;
  }
  // 登录失败
  if(error == "User Is Not Existed"){
      QMessageBox::warning(this, tr("Warning"), name + tr(" : Username/Email is not existed, Please confirm"), QMessageBox::Yes);
      return;
  }
  if(error == "Pwd Is Incorrect"){
      QMessageBox::warning(this, tr("Warning"), name + tr(" : Password is incorrect, Please confirm"), QMessageBox::Yes);
      return;
  }
  // 重置密码失败
  if(error == "Change Password Success, But Send Mail Failed Please Contact Administrator to get the Password"){
      QVariant semail = result["email"];
      QString tempemail = qvariant_cast<QString>(semail);
      QMessageBox::warning(this, tr("Warning"), tempemail + tr(" : Change Password Success, <br>But Send Mail Failed Please Contact Administrator to get the Password"), QMessageBox::Yes);
      return;
  }

  // 注册成功时
  if(m_action == "register" && error.isEmpty()){
      QMessageBox::information(this, tr("Information"), tr("Sign up Successed, Please Login in"), QMessageBox::Yes);
      tabWidget->setCurrentIndex(0);
      return;
  }

  // 登录成功时
  if(m_action == "login" && error.isEmpty()){
      // 传递选择的docUuid
      Preferences* p = Preferences::instance();

      // 处理Setting 设置用户信息
      QVariant user_email = result["user_email"];
      QString  suser_email = qvariant_cast<QString>(user_email);
      p->setUserEmail(suser_email);

      QVariant username = result["username"];
      QString  susername = qvariant_cast<QString>(username);
      p->setUserName(susername);

      QVariant displayname = result["displayname"];
      QString  sdisplayname = qvariant_cast<QString>(displayname);
      p->setDisplayName(sdisplayname);

      QVariant score = result["score"];
      QString  sscore = qvariant_cast<QString>(score);
      p->setScore(sscore);

      QVariant dt_expired = result["dt_expired"];
      QString  sdt_expired = qvariant_cast<QString>(dt_expired);
      p->setDtExpired(sdt_expired);

      QVariant type = result["type"];
      QString  stype = qvariant_cast<QString>(type);
      p->setType(stype);

      QVariant store_limit = result["store_limit"];
      QString  sstore_limit = qvariant_cast<QString>(store_limit);
      p->setStoreLimit(sstore_limit);

      QVariant store_used = result["store_used"];
      QString  sstore_used = qvariant_cast<QString>(store_used);
      p->setStoreUsed(sstore_used);

      QVariant traffic_limit = result["traffic_limit"];
      QString  straffic_limit = qvariant_cast<QString>(traffic_limit);
      p->setTrafficLimit(straffic_limit);

      QVariant traffic_used = result["traffic_used"];
      QString  straffic_used = qvariant_cast<QString>(traffic_used);
      p->setTrafficUsed(straffic_used);

      QVariant last_sel_tags = result["last_sel_tags"];
      QString  slast_sel_tags = qvariant_cast<QString>(last_sel_tags);
      p->setLastSelTags(slast_sel_tags);

      QVariant last_sel_dirs = result["last_sel_dirs"];
      QString  slast_sel_dirs = qvariant_cast<QString>(last_sel_dirs);
      p->setLastSelDirs(slast_sel_dirs);

      QVariant last_open_docs = result["last_open_docs"];
      QString  slast_open_docs = qvariant_cast<QString>(last_open_docs);
      p->setLastOpenDocs(slast_open_docs);

      QVariant last_open_notes = result["last_open_notes"];
      QString  slast_open_notes = qvariant_cast<QString>(last_open_notes);
      p->setLastOpenNotes(slast_open_notes);

      QVariant last_open_urls = result["last_open_urls"];
      QString  slast_open_urls = qvariant_cast<QString>(last_open_urls);
      p->setLastOpenUrls(slast_open_urls);

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





