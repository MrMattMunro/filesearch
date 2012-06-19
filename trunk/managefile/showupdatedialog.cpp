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

#include "showupdatedialog.h"
#include "preferences.h"
#include "utils.h"
#include "fileutils.h"
#include "db/docdao.h"
#include "db/dirdao.h"

// 显示升级过程窗体
ShowUpdateDialog::ShowUpdateDialog(QWidget * parent)
        : QDialog(parent),
          update(false)
{
	setupUi(this);
        this->setWindowIcon(Utils::getIcon("file_manager.png"));
        this->setWindowTitle(tr("Slfile"));
        updatefiles();

        connect(buttonBox, SIGNAL(accepted()), this, SLOT(confirmBtn_clicked()));
        connect(buttonBox,SIGNAL(rejected()),this,SLOT(closeBtn_clicked()));
}

// Copy all
void ShowUpdateDialog::updatefiles(){

    // 传递选择的docUuid
    Preferences* p = Preferences::instance();

    // 处理Setting 设置用户信息
    QString email = p->getUserEmail();
    QString version = p->getVersion();

    QString surl;
    surl.append("http://www.slfile.net/mf-update.php?email=");
    surl.append(email.trimmed());
    surl.append("&version=");
    surl.append(version);

    requtil = new ReqUtil(this);
    connect(requtil,SIGNAL(reqfinished()),this,SLOT(doConfirmReply()));

    QUrl url= QUrl::fromEncoded(surl.toUtf8());
    requtil->startRequest(url);
}

// 确定后处理返回串
void ShowUpdateDialog::doConfirmReply(){

     QVariantMap varMap = requtil->getReply();
     QVariant verror = varMap["error"];
     QString error = qvariant_cast<QString>(verror);
     if(error == "Old PassWord Is Incorrect"){
         QMessageBox::warning(this, tr("Information"), tr("Old PassWord Is Incorrect."), QMessageBox::Yes);
         return;
     }
     if(error == "Email Is Not Existed"){
         QMessageBox::warning(this, tr("Information"), tr("User Is Not Existed."), QMessageBox::Yes);
         return;
     }

     if(error.isEmpty()){
        QVariantList dellist = varMap["dellist"].toList();
        QVariantList updatelist = varMap["updatelist"].toList();

        int sumoffile = dellist.size() + updatelist.size();
        progressBar->setWindowModality(Qt::WindowModal);
        progressBar->setRange(0, sumoffile);

        // 开始操作
        int pos = 0;
        foreach(QVariant delfile, dellist)
        {

           QString sdelfile = qvariant_cast<QString>(delfile);
           FileUtils::removeDirectory(sdelfile);
           pos = pos + 1;
           progressBar->setValue(pos);
        }

        // TODO 从ftp上下载文件覆盖本地
        foreach(QVariant delfile, updatelist)
        {

           QString sdelfile = qvariant_cast<QString>(delfile);
           // FileUtils::copyFileToDir(sdelfile, )
           pos = pos + 1;
           progressBar->setValue(pos);
        }
     }
}

// 确定按钮
void ShowUpdateDialog::confirmBtn_clicked(){
     update = false;
     this->close();
}

// 关闭按钮
void ShowUpdateDialog::closeBtn_clicked(){
     update = false;
     this->close();
}





