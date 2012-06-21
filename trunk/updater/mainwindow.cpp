#include <QDebug>
#include <QProcess>
#include <QDir>

#include "mainwindow.h"
#include "preferences.h"
#include "updatedialog.h"


MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    // 获得服务器Version
    QString surl;
    surl.append("http://www.slfile.net/mf-getnewversion.php");

    requtil = new ReqUtil(this);
    connect(requtil,SIGNAL(reqfinished()),this,SLOT(doConfirmReply()));

    QUrl url= QUrl::fromEncoded(surl.toUtf8());
    requtil->startRequest(url);
}

// 确定后处理返回串
void MainWindow::doConfirmReply(){

     QVariantMap varMap = requtil->getReply();
     QVariant new_version = varMap["new_version"];

     QString newversion = qvariant_cast<QString>(new_version);
     qDebug() << "new_version::" << newversion;

     Preferences* p = Preferences::instance();
     QString version = p->getVersion();
     qDebug() << "version::" << version;
     if(newversion != version || version.isEmpty()){
//         ShowUpdateDialog dlg;
//         dlg.exec();
          UpdateDialog dlg;
          dlg.exec();
     }else{
         QCoreApplication::exit(773);
     }
}


MainWindow::~MainWindow()
{

}
