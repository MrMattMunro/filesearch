#include <QtGui/QApplication>
#include <QProcess>
#include "mainwindow.h"
#include "QDir.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.hide();

    // 重新启动
    int ret = a.exec();
    // 启动主程序
    if (ret == 773) {
        qDebug() << "start main programme";
        QProcess::startDetached(QDir::currentPath().append("managefile.exe"), QStringList());
        return 0;
    }
    return ret;
}
