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

#include "updatedialog.h"
#include "showupdatedialog.h"
#include "preferences.h"
#include "utils.h"

// 登录界面
UpdateDialog::UpdateDialog(QWidget * parent)
        : QDialog(parent),
          update(false)
{
	setupUi(this);
        this->setWindowIcon(Utils::getIcon("file_manager.png"));
        this->setWindowTitle(tr("Slfile"));

        QString url;
        url.append("http://www.slfile.net/bootstrap/changelog_");
        url.append(Utils::getSysLang());
        url.append(".html");
        changelog->load(QUrl::fromUserInput(url));

        connect(ignoreBtn,SIGNAL(clicked()),this,SLOT(ingoreBtn_clicked()));
        connect(nexttimeBtn,SIGNAL(clicked()),this,SLOT(nexttimeBtn_clicked()));
        connect(updateBtn,SIGNAL(clicked()),this,SLOT(updateBtn_clicked()));
}

// 下次按钮
void UpdateDialog::nexttimeBtn_clicked(){
     update = false;
     this->close();
     QCoreApplication::exit(773);
}

// 忽视按钮 -<不能忽视>
void UpdateDialog::ingoreBtn_clicked(){
     update = false;
     this->close();
     QCoreApplication::exit(773);
}

// 升级按钮
void UpdateDialog::updateBtn_clicked(){
    ShowUpdateDialog dlg(this);
    dlg.exec();
    this->close();
}





