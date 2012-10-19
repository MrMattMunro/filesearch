#include <QtGui/QApplication>
#include <QProcess>
#include <QDir>
#include <QTranslator>
#include <QMessageBox>
#include "mainwindow.h"
#include "utils.h"
#include "fileutils.h"
#include "single_application.h"

#define _TIME_ qPrintable (QTime::currentTime ().toString ("hh:mm:ss:zzz"))

void customMessageHandler(QtMsgType type, const char *msg)
 {
        QString txt;
        switch (type) {
         //调试信息提示
         case QtDebugMsg:
                 txt = QString("%1: Debug: %2").arg(_TIME_).arg(msg);
                 break;

        //一般的warning提示
         case QtWarningMsg:
                 txt = QString("%1: Warning: %2").arg(_TIME_).arg(msg);
         break;
         //严重错误提示
         case QtCriticalMsg:
                txt = QString("%1: Critical: %2").arg(_TIME_).arg(msg);
         break;
         //致命错误提示
         case QtFatalMsg:
                txt = QString("%1: Fatal: %2").arg(_TIME_).arg(msg);
                abort();
         }

         QString logfile = Utils::getSaveLogPath().append(QDir::separator()).append("mflog.log");
         QFileInfo file(logfile);
         if(file.exists()){
             if(file.size() > 1048576){
                 FileUtils::deleteDirectory(file);
             }
         }

         QFile outFile(logfile);
         outFile.open(QIODevice::WriteOnly | QIODevice::Append);
         QTextStream ts(&outFile);
         ts << txt << endl;
}

int main(int argc, char *argv[])
{
    SingleApplication app(argc, argv, "7yd2_2d");
    // 单个实例运行
    if (app.isRunning())
    {
        // app.sendMessage("There is an other Solo instance runing."));
        return 0;
    }

    qInstallMsgHandler(customMessageHandler);

    MainWindow w;
    w.hide();

    // 设定开机自检启动
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
        QProcess::startDetached(QDir::currentPath().append(QDir::separator()).append("Solo.exe"), QStringList());
        return 0;
    }
    return ret;
}
