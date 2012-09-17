#include <QFileDialog>
#include <QMessageBox>

#include <QtDebug>
#include <QDir>
#include <QUuid>
#include <QStandardItemModel>
#include <QWebFrame>
#include <QDateTime>
#include <QTextCodec>
#include <qjson/parser.h>
#include <qjson/serializer.h>

#include "aboutdialog.h"
#include "preferences.h"
#include "utils.h"
#include "intelliplugin.h"
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


        // 插入插件
        about->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
        about->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
        about->settings()->setAttribute(QWebSettings::LocalStorageEnabled, true);

        about->page()->setPluginFactory(new IntelliPlugin);
        about->load(QUrl::fromUserInput(path));
        about->show();

        // 获得服务器Version
        QString surl;
        surl.append("http://www.slfile.net/mf-getnewversion.php");

        requtil = new ReqUtil(this);
        connect(requtil,SIGNAL(reqfinished()),this,SLOT(doConfirmReply()));

        QUrl url= QUrl::fromEncoded(surl.toUtf8());
        requtil->startRequest(url);

        connect(buttonBox,SIGNAL(rejected()),this,SLOT(closeBtn_clicked()));
}

// 确定后处理返回串
void AboutDialog::doConfirmReply(){

    QVariantMap varMap = requtil->getReply();
    QVariant new_version = varMap["new_version"];

    QString newversion = qvariant_cast<QString>(new_version);
    qDebug() << "new_version::" << newversion;

    Preferences* p = Preferences::instance();
    QString localversion = p->getVersion();
    qDebug() << "local_version::" << localversion;

    QString strVal = QString("setVersion(\"%1\", \"%2\");").arg(localversion).arg(newversion);
    about->page()->mainFrame()->evaluateJavaScript(strVal);
}


// 取消按钮
void AboutDialog::closeBtn_clicked(){
     update = false;
     this->close();
}








