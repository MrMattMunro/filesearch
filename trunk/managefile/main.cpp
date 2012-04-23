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

#include <QtGui>

#include "mainwindow.h"
#include "preferences.h"
#include "utils.h"
#include "db/database.h"
#include "fileutils.h"
#include "noteeditor.h"
#include <QDebug>
NoteEditor    *noteEditor;	// used in Constr. of LinkableMapObj


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
    QDir d("../ts/", "*.qm");
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
// 主函数
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //崩溃处理
#ifndef  WIN32
    initCrashHandler();
#endif
    ArgsParser cli(argc, argv);
    if (!cli.parseArgs()){
      return 0;
    }

    // 加载数据库驱动
    QApplication::addLibraryPath("./lib");
    qDebug() << "my library path : " << app.libraryPaths();
    QLibrary sqlib("sqlite3.dll");
    sqlib.load();
    qDebug() << "my library loaded" << sqlib.isLoaded();

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

   // 设置窗口图标
    app.setWindowIcon(Utils::getIcon("file_manager.png"));
    QTranslator translator;
    translator.load(Utils::getTranslator(cli.localeCode()));
    app.installTranslator(&translator);

    //QString QCoreApplication::applicationDirPath () [static]

    // Initialize window of NoteEditor
    noteEditor = new NoteEditor();
    //noteEditor->setWindowIcon (QPixmap (iconPath+ "vym-editor.png"));

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
    Database::execSql(Database::getSql("mf_document_related.sql"));
    Database::execSql(Database::getSql("mf_dir.sql"));
    Database::execSql(Database::getSql("mf_document_note.sql"));
    Database::execSql(Database::getSql("mf_document.sql"));
    Database::execSql(Database::getSql("mf_document_related.sql"));
    Database::execSql(Database::getSql("mf_document_tag.sql"));
    Database::execSql(Database::getSql("mf_tag.sql"));

    MainWindow w;
    w.setLocale(cli.localeCode());

    w.showMaximized();
    return app.exec();
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


