#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Preferences* p = Preferences::instance();
    QString version = p->getVersion();
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
}


MainWindow::~MainWindow()
{
    delete ui;
}
