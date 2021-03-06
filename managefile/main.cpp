/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the Graphics Dojo project on Qt Labs.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 or 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.  Please review the following information to ensure GNU
** General Public Licensing requirements will be met:
** http://www.fsf.org/licensing/licenses/info/GPLv2.html and
** http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include <QtWidgets>

#include "mainwindow.h"
#include "preferences.h"
#include "utils.h"
#include "db/database.h"
#include "xmlrpc/client.h"
#include "logindialog.h"
#include "fileutils.h"
#include "sqlloader.h"
#include "jvm.h"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include "single_application.h"
#include <QTime>

#define _TIME_ qPrintable (QTime::currentTime ().toString ("hh:mm:ss:zzz"))

#define ARG_VERSION "--version"
#define ARG_HELP "--help"
#define ARG_LANG "--lang"
#define ARG_AVAILLANG "--langs"
#define ARG_VERSION_SHORT "-v"
#define ARG_HELP_SHORT "-h"
#define ARG_LANG_SHORT "-l"
#define ARG_AVAILLANG_SHORT "-la"
#define FILEMANAGE_VERSION "1.0"
#define endl QString("\n")
#define DATABASE "MF"

#ifndef WIN32
void initCrashHandler();
static void defaultCrashHandler(int sig);
#endif


/*! \brief Parse the CLI user input.
Based on the Scribus code (a bit).
\author Petr Vanek <petr@scribus.info>
*/
class ArgsParser
{
    public:
        ArgsParser(int c, char ** v);
        ~ArgsParser(){};
        bool parseArgs();
        QString localeCode();
        //! \brief No file is opened when the returned value is null
        const QString & fileToOpen();
    private:
        int argc;
        char ** argv;
        QString m_locale;
        QMap<int,QString> m_localeList;
        void langsAvailable();
        QString m_file;
};

/*! \brief Pre-fil available translations into QMap to cooperate
with PreferencesDialog.
*/
ArgsParser::ArgsParser(int c, char ** v)
    : argc(c), argv(v), m_locale(""), m_file(QString())
{
    QDir d("ts", "*.qm");
    int i = 1; // 0 is for system default
    foreach (QString f, d.entryList())
    {
        m_localeList[i] = f.remove("managefile_").remove(".qm");
        ++i;
    }
}

//! \brief Print available translations
void ArgsParser::langsAvailable()
{
    // HACK: QTextStream simulates std::cout here. It can handle
    // QStrings without any issues. E.g. std::cout << QString::toStdString()
    // does compile problems in some Qt4 configurations.
    QTextStream cout(stdout, QIODevice::WriteOnly);
    cout << QString("Available translation:") << endl;
    foreach (QString l, m_localeList.values())
        cout << QString("  --lang ") << l << endl;
}

/*! \brief Get the right translations.
Property: 1) specified from CLI - it overrides Prefs or System
2) from preferences
3) system pre-configured
*/
QString ArgsParser::localeCode()
{
    QString ret;
    Preferences * prefs = Preferences::instance();
    if (!m_locale.isEmpty())
        ret = QLocale(m_locale).name();
    else if (prefs->GUItranslator() != 0)
        ret = m_localeList[prefs->GUItranslator()];
    else
        ret = QLocale::system().name();
    return ret.left(2);
}

const QString & ArgsParser::fileToOpen()
{
    if (m_file.isNull())
    {
        Preferences* p = Preferences::instance();
        if (p->openLastDB() && QFileInfo(p->lastDB()).exists())
            m_file = p->lastDB();
    }
    return m_file;
}

bool ArgsParser::parseArgs()
{
    QString arg("");
    QTextStream cout(stdout, QIODevice::WriteOnly);

    for(int i = 1; i < argc; i++)
    {
        arg = argv[i];

        if ((arg == ARG_LANG || arg == ARG_LANG_SHORT) && (++i < argc))
        {
            m_locale = argv[i];
            return true;
        }
        else if (arg == ARG_VERSION || arg == ARG_VERSION_SHORT)
        {
            cout << QString("Sqliteman ") << FILEMANAGE_VERSION << endl;
            return false;
        }
        else if (arg == ARG_HELP || arg == ARG_HELP_SHORT)
        {
            cout << endl << QString("sqliteman [options] [databasefile]") << endl;
            cout << QString("options:") << endl;
            cout << QString("  --help    -h  displays small help") << endl;
            cout << QString("  --version -v  prints version") << endl;
            cout << QString("  --lang    -l  set a GUI language. E.g. --lang cs for Czech") << endl;
            cout << QString("  --langs   -la lists available languages") << endl;
            cout << QString("  + various Qt options") << endl << endl;
            return false;
        }
        else if (arg == ARG_AVAILLANG || arg == ARG_AVAILLANG_SHORT)
        {
            langsAvailable();
            return false;
        }
        else
        {
            m_file = QFile::decodeName(argv[i]);
            if (!QFileInfo(m_file).exists())
            {
                if (m_file.left(1) == "-" || m_file.left(2) == "--")
                    cout << QString("Invalid argument: ") << m_file << endl;
                else
                    cout << QString("File ") << m_file << QString(" does not exist, aborting.") << endl;
                return false;
            }
            return true;
        }
    }
    return true;
}

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

// 主函数
int main(int argc, char *argv[])
{
    SingleApplication app(argc, argv, "7yz2_2d");
    // 单个实例运行
    if (app.isRunning())
    {
        // app.sendMessage("There is an other Solo instance runing."));
        return 0;
    }

    //以后就可以像下面这样直接打日志到文件中，而且日志也会包含时间信息
//    qDebug("This is a debug message at thisisqt.com");
//    qWarning("This is a warning message  at thisisqt.com");
//    qCritical("This is a critical message  at thisisqt.com");
    // qFatal("This is a fatal message at thisisqt.com");

    //qInstallMsgHandler(customMessageHandler);

    //崩溃处理
#ifndef  WIN32
    initCrashHandler();
#endif
    ArgsParser cli(argc, argv);
    if (!cli.parseArgs()){
      return 0;
    }

    SingleApplication::addLibraryPath("./plugins");
    // 设置系统右下图标
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
            QMessageBox::critical(0, QObject::tr("Systray"),
                                  QObject::tr("I couldn't detect any system tray "
                                              "on this system."));
            return 1;
     }
    SingleApplication::setQuitOnLastWindowClosed(false);

     // 需要改动注册表文件,当退出时在MainWindow删除该文件
     QString regpath = QDir::currentPath().append(QDir::separator()).append("reg.exe");
     QFileInfo regFile(regpath);
     bool regSuccess = true;
     if(regFile.exists()){
        regSuccess = QProcess::startDetached(regpath, QStringList());
     }

    // 加载数据库驱动
//    QApplication::addLibraryPath("./lib");
//    qDebug() << "my library path : " << app.libraryPaths();
//    QLibrary sqlib("sqlite3.dll");
//    sqlib.load();
//    qDebug() << "my library loaded" << sqlib.isLoaded();

    // 设置数据库文件
    QString dbpath = Utils::getLocatePath().append(QDir::separator()).append("db");
    QDir *dir=new QDir(dbpath);
    if(!dir->exists()){
       dir->mkdir(dbpath);
    }
    QString dbfilepath = dbpath.append(QDir::separator()).append(DATABASE);
    QFile *dirfile=new QFile(dbfilepath);
    if(!dirfile->exists()){
      dirfile->open( QIODevice::WriteOnly );
      dirfile->close();
    }

    // 设置正在搜索标志位
    Preferences* pre = Preferences::instance();
    pre->setIsIndexing(false);

    // 设置服务器信息 TODO 需要改为从服务器端获取
    pre->setAddress("192.168.1.103");
    pre->setPort(8080);

    // 初始化JVM 提高第一次搜索数据
    Jvm::BeginJVM();

    // 设置窗口图标
    app.setWindowIcon(Utils::getIcon("file_manager.png"));
    QTranslator translator;
    QString localTranslator = Utils::getTranslator(cli.localeCode());
    translator.load(localTranslator);
    app.installTranslator(&translator);

    //QString QCoreApplication::applicationDirPath () [static]

    // 打开连接db
    Database::sessionName(DATABASE);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", DATABASE);
    db.setDatabaseName(dbfilepath);
    if(!db.open())
    {
        QMessageBox::critical(0, "", "Unable to open or create file. It is probably not a database");
        return -1;
    }

    // 初始化数据库
    SqlLoader* sqlLoader = SqlLoader::instance();
    Database::execSql(sqlLoader->getSql("mf_document_related.sql"));
    Database::execSql(sqlLoader->getSql("mf_dir.sql"));
    Database::execSql(sqlLoader->getSql("mf_document_note.sql"));
    Database::execSql(sqlLoader->getSql("mf_document.sql"));
    Database::execSql(sqlLoader->getSql("mf_document_related.sql"));
    Database::execSql(sqlLoader->getSql("mf_document_tag.sql"));
    Database::execSql(sqlLoader->getSql("mf_tag.sql"));
    Database::execSql(sqlLoader->getSql("mf_meta.sql"));
    Database::execSql(sqlLoader->getSql("mf_result.sql"));

    // 删除一段时间以上的T_result
    ResultDao::deleteResultByCreateDate(-15);

    // 显示登录界面
    Preferences* p = Preferences::instance();
    QString usremail = p->getUserEmail();
    QString usrename= p->getUserName();

    // 当当前用户为空时,才显示登录界面
    if(usremail.isEmpty() && usrename.isEmpty() ){
        LoginDialog dlg;
        dlg.exec();
        if(dlg.update){
          // 不做任何操作
            MainWindow w;
            w.setLocale(cli.localeCode());
            w.showMaximized();
            return app.exec();
        }else{
            return 0;
        }
    } else {
       // 不做任何操作
       MainWindow w;
       w.setLocale(cli.localeCode());
       w.showMaximized();

       // QObject::connect(&app, SIGNAL(messageAvailable(QString)), w, SLOT(receiveMessage(QString)));

       // 重新启动
       int ret = app.exec();
       if (ret == 773) {
            QProcess::startDetached(app.applicationFilePath(), QStringList());
            return 0;
       }
       return ret;
    }

}

#ifndef WIN32
void initCrashHandler()
{
    typedef void (*HandlerType)(int);
    HandlerType handler	= 0;
    handler = defaultCrashHandler;
    if (!handler)
        handler = SIG_DFL;
    sigset_t mask;
    sigemptyset(&mask);
#ifdef SIGSEGV
    signal (SIGSEGV, handler);
    sigaddset(&mask, SIGSEGV);
#endif
#ifdef SIGFPE
    signal (SIGFPE, handler);
    sigaddset(&mask, SIGFPE);
#endif
#ifdef SIGILL
    signal (SIGILL, handler);
    sigaddset(&mask, SIGILL);
#endif
#ifdef SIGABRT
    signal (SIGABRT, handler);
    sigaddset(&mask, SIGABRT);
#endif
    sigprocmask(SIG_UNBLOCK, &mask, 0);
}


void defaultCrashHandler(int sig)
{
    QTextStream cout(stdout, QIODevice::WriteOnly);
    static int crashRecursionCounter = 0;
    crashRecursionCounter++;
    signal(SIGALRM, SIG_DFL);
    if (crashRecursionCounter < 2)
    {
        crashRecursionCounter++;
        QString sigMsg(tr("\nfileManage crashes due to Signal #%1\n\n\All database opened will be rollbacked and closed.\n\n\Collect last steps that forced this\n\situlation and report it as a bug, please.").arg(sig));
        cout << sigMsg << endl;
        QMessageBox::critical(0, tr("filemanage"), sigMsg);
        alarm(300);
    }
    exit(255);
}
#endif


