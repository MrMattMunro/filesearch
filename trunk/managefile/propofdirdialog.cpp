#include "PropOfDirDialog.h"

#include <QDir>
#include <QMessageBox>
#include "db/docdao.h"
#include "db/dirdao.h"
#include "db/relatedocdao.h"
#include "utils.h"

PropOfDirDialog::PropOfDirDialog (QWidget *parent, const QString & curUuid)
    : QDialog(parent), m_curUuid(curUuid),update(false)
{
    setupUi (this);

    // 取得当前文档
    Dir dir = DirDao::selectDir(m_curUuid);

    setWindowTitle (dir.DIR_NAME +" - " +tr ("Property Editor","Window caption"));


    // 设置基本信息
    name->setText(dir.DIR_NAME);
    uuid->setText(dir.DIR_GUID);
    icon->setIcon(Utils::getIcon(dir.DIR_ICON));

    // 取得当前路径
    QList<Dir> dirList;
    DirDao::selectAllParentDirbyDir(dirList, m_curUuid);

    QString slocation;
    slocation.append(QDir::separator());
    for (int var = dirList.length() - 1; var >= 0 ; --var) {
        Dir dir = dirList.at(var);
        slocation.append(dir.DIR_NAME);
        slocation.append(QDir::separator());
    }
    location->setText(slocation);
    desp->setText(dir.DIR_DESCRIPTION);

    // 设置保护
    QList<Dir> selDirList;
    DirDao::selectAllSubDirbyDir(selDirList, m_curUuid, "0");
    DirDao::selectAllSubDirbyDir(selDirList, m_curUuid, "1");
    dirCount->setText(QString::number(selDirList.size()));

    Dir tempDir;
    int ifileCount = 0;
    int ifileSize = 0;
    foreach(tempDir, selDirList){
        QList<Doc> docs = DocDao::selectDocsbyDir(tempDir.DIR_GUID, "0");
        QList<Doc> deldocs = DocDao::selectDocsbyDir(tempDir.DIR_GUID, "1");
        ifileCount = docs.size() + deldocs.size() + 1;
        Doc doc;
        foreach(doc, docs){
            // 计算size K
            QFileInfo file(doc.DOCUMENT_LOCATION);
            ifileSize = ifileSize + file.size();
        }
        foreach(doc, deldocs){
            // 计算size K
            QFileInfo file(doc.DOCUMENT_LOCATION);
            ifileSize = ifileSize + file.size();
        }
    }
    fileCount->setText(QString::number(ifileCount));
    fileSize->setText(QString::number(ifileSize/1024).append(" K"));

    // 密码
    // MD5解密
    QString dirprotect = dir.DIR_PROTECT;
    if(dirprotect.isEmpty()){
        // 未设置保护
        isProtect->setChecked(false);
        orgpwd->setText("");
        pwd->setText("");
        repwd->setText("");

        orgpwd->setDisabled(true);
        pwd->setDisabled(true);
        repwd->setDisabled(true);
    }else{
        // 设置过保护
        isProtect->setChecked(true);
        orgpwd->setText("password");
        orgpwd->setDisabled(false);
        pwd->setDisabled(false);
        repwd->setDisabled(false);
    }

    // 设置同步
    localVer->setText(QString::number(dir.MF_VERSION));

    // 从服务器上取出，对比Version来比较版本 利用新的来同步
    // remoteVer->setText();
    connect(closeBtn,SIGNAL(clicked()),this, SLOT(closeBtn_clicked()));
    connect(applyBtn,SIGNAL(clicked()),this, SLOT(applyBtn_clicked()));
    connect(isProtect,SIGNAL(clicked()),this, SLOT(setProtect()));


    // 默认选中第一个tab
    tabWidget->setCurrentIndex(0);

}

// 保护文件夹
void PropOfDirDialog::setProtect()
{
    if(orgpwd->isEnabled()){
       orgpwd->setDisabled(true);
    }else{
       orgpwd->setDisabled(false);
    }

    if(pwd->isEnabled()){
       pwd->setDisabled(true);
    }else{
       pwd->setDisabled(false);
    }

    if(repwd->isEnabled()){
       repwd->setDisabled(true);
    }else{
       repwd->setDisabled(false);
    }

}

// 更新数据项
void PropOfDirDialog::applyBtn_clicked()
{
     // 参数检查
    // 取得当前文档
    Dir dir = DirDao::selectDir(m_curUuid);

     QString sorgpwd = orgpwd->text();
     if(!sorgpwd.isEmpty()){
        // 判断跟数据库一致
         QString dbprotect = dir.DIR_PROTECT;
         QString md5pwd = Utils::getMD5Str(sorgpwd);
         if(dbprotect != md5pwd){
             QMessageBox::warning(this, tr("Warning"), tr("The Org password is wrong, Please Confirm"), QMessageBox::Yes);
             return;
         }
     }


     QString srepwd = repwd->text();
     QString spwd = pwd->text();
     QString protectStr = "";

     if(!srepwd.isEmpty() && !spwd.isEmpty()){
         if(srepwd != spwd){
             QMessageBox::warning(this, tr("Warning"), tr("The password you entered must be the same as the  former"), QMessageBox::Yes);
             return;
         }else{
             protectStr =  Utils::getMD5Str(srepwd);
         }
     }


     dir.DIR_NAME = name->text();
     dir.DIR_DESCRIPTION = desp->toPlainText();
     dir.DIR_ICON = icon->icon().name();
     dir.DIR_PROTECT = protectStr;
     dir.MF_VERSION = dir.MF_VERSION + 1;

     DirDao::updateDir(dir);

     update = true;
     this->close();
}


void PropOfDirDialog::closeBtn_clicked()
{
    update = true;
    this->close();
}

