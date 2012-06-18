/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/
#include <QFileDialog>
#include <QMessageBox>

#include <QtDebug>
#include <QDir>
#include <QStandardItemModel>
#include <QDesktopServices>
#include <QUrl>
#include <QUuid>
#include "accountdialog.h"
#include "utils.h"
#include "fileutils.h"
#include "preferences.h"
#include "changepwddialog.h"
#include "scoretovipdialog.h"
#include "db/tagdao.h"

AccountDialog::AccountDialog(QWidget * parent)
        : QDialog(parent),
          update(false)
{
	setupUi(this);

        // Set UI
        this->setWindowTitle(tr("Account Information"));

        connect(changepwdBtn,SIGNAL(clicked()),this,SLOT(changePassword()));
        connect(score4vipBtn,SIGNAL(clicked()),this,SLOT(score4vip()));
        connect(updatevipBtn,SIGNAL(clicked()),this,SLOT(updatevip()));

        connect(buttonBox,SIGNAL(rejected()),this,SLOT(closeBtn_clicked()));

        // 设定值
        // 传递选择的docUuid
        Preferences* p = Preferences::instance();

        // 处理Setting 设置用户信息
        QString email = p->getUserEmail();
        QString username = p->getUserName();
        if( ! email.isEmpty()){
            name->setText(email);
        }else{
            name->setText(username);
        }
        QString score = p->getScore();
        QString stype = p->getType();
        if(stype == "b6e70zfef3"){
            QString dtExpired = p->getDtExpired();
            stype = "VIP ";
            stype.append(" ");
            stype.append(dtExpired);
        }else{
            stype = "free";
        }
        type->setText(stype);
        scoreLabel->setText(score);
        pwd->setText("*************");

        QString storeLimit = p->getStoreLimit();
        QString storeUsed = p->getStoreUsed();
        storeBar->setRange(0, storeLimit.toInt());
        storeBar->setValue(storeUsed.toInt());

        QString trafficLimit = p->getTrafficLimit();
        QString trafficUsed = p->getTrafficUsed();
        trafficBar->setRange(0, trafficLimit.toInt());
        trafficBar->setValue(trafficUsed.toInt());

        QString sstoreInfo;
        sstoreInfo.append(QString ::number(storeUsed.toInt()/1024/1024));
        sstoreInfo.append("/");
        sstoreInfo.append(QString ::number(storeLimit.toInt()/1024/1024));
        sstoreInfo.append(" MB(");
        sstoreInfo.append(storeBar->text());
        sstoreInfo.append(")");
        storeInfo->setText(sstoreInfo);

        QString strafficInfo;
        strafficInfo.append(QString ::number(trafficUsed.toInt()/1024/1024));
        strafficInfo.append("/");
        strafficInfo.append(QString ::number(trafficLimit.toInt()/1024/1024));
        strafficInfo.append(" MB(");
        strafficInfo.append(trafficBar->text());
        strafficInfo.append(" Current Month)");
        trafficInfo->setText(strafficInfo);

        // 设置Disabel项
        name->setDisabled(true);
        pwd->setDisabled(true);
        type->setDisabled(true);
}

// 改变密码
void AccountDialog::changePassword(){
    ChangePwdDialog dlg;
    dlg.exec();
    if(dlg.update){

    }
}

// 积分换VIP
void AccountDialog::score4vip(){
    ScoreToVipDialog dlg;
    dlg.exec();
    if(dlg.update){
    }
}

// 升级到VIP
void AccountDialog::updatevip(){
    // 打开ie
    emit updateVip();
}

// 取消按钮
void AccountDialog::closeBtn_clicked(){
     update = false;
     this->close();
}



