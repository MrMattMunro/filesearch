#include <QtGui/QApplication>
#include <QProcess>
#include <QDir>
#include <QTranslator>
#include "mainwindow.h"
#include "utils.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.hide();

    QApplication::addLibraryPath("./plugins");
    // 设置窗口图标
    app.setWindowIcon(Utils::getIcon("updater.ico"));
    // 多语言设置
    QString lang = QLocale::system().name();
    QTranslator translator;
    QString localTranslator = Utils::getTranslator(lang.left(2));
    translator.load(localTranslator);
    app.installTranslator(&translator);

    // 重新启动
    int ret = app.exec();
    // 启动主程序
    if (ret == 773) {
        qDebug() << "start main programme";
        QProcess::startDetached(QDir::currentPath().append("managefile.exe"), QStringList());
        return 0;
    }
    return ret;
}
