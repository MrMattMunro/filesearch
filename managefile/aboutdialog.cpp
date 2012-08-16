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

#include "aboutdialog.h"
#include "preferences.h"
#include "utils.h"
#include "db/docdao.h"
#include "db/dirdao.h"

// 登录界面
AboutDialog::AboutDialog(QWidget * parent)
        : QDialog(parent),
          update(false)
{
        setupUi(this);
        this->setWindowIcon(Utils::getIcon("file_manager.png"));
        this->setWindowTitle(tr("Solo"));

        QString lange = Utils::getSysLang();
        QDir pathDir = Utils::directoryOf("html");
        QString path = pathDir.absolutePath();
        path.append(QDir::separator());
        path.append("about_");
        path.append(lange);
        path.append(".html");

        about->load(QUrl::fromUserInput(path));
        connect(buttonBox,SIGNAL(rejected()),this,SLOT(closeBtn_clicked()));
}

// 取消按钮
void AboutDialog::closeBtn_clicked(){
     update = false;
     this->close();
}








