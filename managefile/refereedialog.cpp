#include "refereedialog.h"

#include <QDir>
#include <QMessageBox>
#include <QThread>
#include "db/docdao.h"
#include "db/dirdao.h"
#include "db/relatedocdao.h"
#include "utils.h"
#include "preferences.h"

RefereeDialog::RefereeDialog (QWidget *parent, const QString & curUuid)
    : QDialog(parent),update(false)
{
    setupUi (this);

    // 名称
    Preferences* p = Preferences::instance();
    QString displayName = p->getDisplayName();

    if(displayName.isEmpty()){
        realname->setText(tr("Please Input your real name"));
    }
    QString userEmail = p->getUserEmail();

    emailtitle->setText(tr("Your Friend %1 recommend this Software to Manage your document").arg(displayName));
    content->setHtml(tr("<html><body><div>hi! , your friend %1 is using slfile to manage her documents, <br>do you want to try? Use this Address(<url>http://www.slfile.net/singup.php?referee=%2<url>) to Sign up you will help you friend get 300 point score. </div></body></html>").arg(displayName).arg(userEmail));

    connect(realname, SIGNAL(textChanged(QString)), this, SLOT(changeEmail(QString)));

    connect(closeBtn,SIGNAL(clicked()),this, SLOT(closeBtn_clicked()));
    connect(applyBtn,SIGNAL(clicked()),this, SLOT(applyBtn_clicked()));
}

// 改变邮件内容
void RefereeDialog::changeEmail(QString userName)
{
    // 名称
    Preferences* p = Preferences::instance();
    QString userEmail = p->getUserEmail();

    emailtitle->setText(tr("Your Friend %1 recommend slfile to Manage document").arg(userName));
    content->setHtml(tr("hi! , your friend %1 is using slfile to manage document, <br>do you want to try? Use this Address(<url>http://www.slfile.net/singup.php?referee=%2<url>) to Sign up you will help you friend get 300 point score.").arg(userName).arg(userEmail));
}

// 发送邮件
void RefereeDialog::applyBtn_clicked()
{
    sendMailObj.m_successList.clear();
    sendMailObj.m_failList.clear();
    QString addrs = emailaddr->toPlainText();
    if(addrs.trimmed().isEmpty()){
        QMessageBox::warning(this, tr("Warning"), tr("The address is empty, Please Input"), QMessageBox::Yes);
        return;
    }

    QString scontent = content->toHtml();
    if(scontent.trimmed().isEmpty()){
        QMessageBox::warning(this,  tr("Warning") ,tr("The email content is empty, Please Input"), QMessageBox::Yes);
        return;
    }

    QString title = emailtitle->text();
    if(title.trimmed().isEmpty()){
        QMessageBox::warning(this, tr("Warning"), tr("The title is empty, Please Input"), QMessageBox::Yes);
        return;
    }

    QStringList emailaddrs = addrs.split(",");

    sendMailObj.toaddrs = emailaddrs;
    sendMailObj.title = title;
    sendMailObj.content = scontent;

//    QThread thread;
//    sendMailObj.moveToThread(&thread);

    SendMailSign dummy;
    QObject::connect(&dummy, SIGNAL(sig()), &sendMailObj, SLOT(sendMail()));
    QObject::connect(&sendMailObj, SIGNAL(finished()), this, SLOT(checkSuccess()));

//    thread.start();
    dummy.emitsig();

//    update = true;
//    this->close();
}

// 成功
void RefereeDialog::checkSuccess()
{

    // 显示发送成功的邮件
    if(sendMailObj.m_successList.size() > 0){
        QString email;
        QString msg;
        msg.append(tr("Send Mail Success !"));
        msg.append("\n");
        foreach(email, sendMailObj.m_successList){
            msg.append(email);
            msg.append("\n");
        }
         QMessageBox::warning(this, tr("Information"), msg, QMessageBox::Yes);
    }

     // 未发送成功的邮件
    if(sendMailObj.m_failList.size() > 0){
        QString email;
        QString msg;
        msg.append(tr("Send Mail Failed, Please check the email Address !"));
        msg.append("\n");
        foreach(email, sendMailObj.m_successList){
            msg.append(email);
            msg.append("\n");
        }
         QMessageBox::warning(this, tr("Warning"), msg, QMessageBox::Yes);
    }

}

// 取消
void RefereeDialog::closeBtn_clicked()
{
    update = true;
    this->close();
}

