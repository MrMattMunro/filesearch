#include "jvm.h"
#include <QDebug>
#include <string>
#include <iostream>
#include <QDir>
#include <utils.h>
#include <db/docdao.h>
#include <db/resultdao.h>
#include <QTextCodec>
#include <QThread>
#include <QMessageBox>

JNIEnv* Jvm::env = NULL;
JavaVM* Jvm::jvm = NULL;

Jvm::~Jvm()
{
}

bool Jvm::BeginJVM()
{

     if(jvm == NULL){
        //定义一个函数指针，下面用来指向JVM中的JNI_CreateJavaVM函数
        typedef jint (WINAPI *PFunCreateJavaVM)(JavaVM **, void **, void *);
        int ret;
        JavaVMInitArgs vm_args;
        JavaVMOption options[3];

         qDebug() << "ininsize JVM";

        /*设置初始化参数*/
        //disable JIT，这是JNI文档中的解释，具体意义不是很清楚 ，能取哪些值也不清楚。
        //从JNI文档里给的示例代码中搬过来的
        options[0].optionString = "-Djava.compiler=NONE";

        //设置classpath，如果程序用到了第三方的JAR包，也可以在这里面包含进来
            // char *optionString;
        QString option = "-Djava.class.path=.;";
        option.append(".\\jre\\jar\\bcmail-jdk14-132.jar;");
        option.append(".\\jre\\jar\\bcprov-jdk14-132.jar;");
        option.append(".\\jre\\jar\\commons-collections-3.2.1.jar;");
        option.append(".\\jre\\jar\\commons-logging-1.1.jar;");
        option.append(".\\jre\\jar\\geronimo-stax-api_1.0_spec-1.0.jar;");
        option.append(".\\jre\\jar\\htmllexer.jar;");
        option.append(".\\jre\\jar\\htmlparser.jar;");
        option.append(".\\jre\\jar\\indexFile.jar;");
        option.append(".\\jre\\jar\\log4j-1.2.13.jar;");
        option.append(".\\jre\\jar\\lucene-core-3.3.0.jar;");
        option.append(".\\jre\\jar\\lucene-gosen-1.2-dev-ipadic.jar;");
        option.append(".\\jre\\jar\\lucene-highlighter-3.3.0.jar;");
        option.append(".\\jre\\jar\\lucene-memory-3.3.0.jar;");
        option.append(".\\jre\\jar\\nekohtml.jar;");
        option.append(".\\jre\\jar\\paoding-analysis.jar;");
        option.append(".\\jre\\jar\\poi-3.8-beta3-20110606.jar;");
        option.append(".\\jre\\jar\\poi-excelant-3.8-beta3-20110606.jar;");
        option.append(".\\jre\\jar\\poi-ooxml-3.8-beta3-20110606.jar;");
        option.append(".\\jre\\jar\\poi-ooxml-schemas-3.8-beta3-20110606.jar;");
        option.append(".\\jre\\jar\\poi-scratchpad-3.8-beta3-20110606.jar;");
        option.append(".\\jre\\jar\\stax-api-1.0.1.jar;");
        option.append(".\\jre\\jar\\xercesImpl.jar;");
        option.append(".\\jre\\jar\\xmlbeans-2.3.0.jar;");
        option.append(".\\jre\\jar\\dom4j-1.6.1.jar;");
        option.append(".\\jre\\jar\\sendmail.jar;");
        option.append(".\\jre\\jar\\mail-1.4.1.jar;");


        options[1].optionString = "-Djava.class.path=.;.\\jre\\jar\\bcmail-jdk14-132.jar;.\\jre\\jar\\bcprov-jdk14-132.jar;.\\jre\\jar\\commons-collections-3.2.1.jar;.\\jre\\jar\\commons-logging-1.1.jar;.\\jre\\jar\\geronimo-stax-api_1.0_spec-1.0.jar;.\\jre\\jar\\htmllexer.jar;.\\jre\\jar\\htmlparser.jar;.\\jre\\jar\\indexFile.jar;.\\jre\\jar\\log4j-1.2.13.jar;.\\jre\\jar\\lucene-core-3.3.0.jar;.\\jre\\jar\\lucene-gosen-1.2-dev-ipadic.jar;.\\jre\\jar\\lucene-highlighter-3.3.0.jar;.\\jre\\jar\\lucene-memory-3.3.0.jar;.\\jre\\jar\\nekohtml.jar;.\\jre\\jar\\paoding-analysis.jar;.\\jre\\jar\\poi-3.8-beta3-20110606.jar;.\\jre\\jar\\poi-excelant-3.8-beta3-20110606.jar;.\\jre\\jar\\poi-ooxml-3.8-beta3-20110606.jar;.\\jre\\jar\\poi-ooxml-schemas-3.8-beta3-20110606.jar;.\\jre\\jar\\poi-scratchpad-3.8-beta3-20110606.jar;.\\jre\\jar\\stax-api-1.0.1.jar;.\\jre\\jar\\xercesImpl.jar;.\\jre\\jar\\xmlbeans-2.3.0.jar;.\\jre\\jar\\dom4j-1.6.1.jar;.\\jre\\jar\\sendmail.jar;.\\jre\\jar\\mail-1.4.1.jar";
        // options[1].optionString = option.toLatin1().data();

        //设置显示消息的类型，取值有gc、class和jni，如果一次取多个的话值之间用逗号格开，如-verbose:gc,class
        //该参数可以用来观察C++调用JAVA的过程，设置该参数后，程序会在标准输出设备上打印调用的相关信息
        options[2].optionString = "-verbose:NONE";

        //设置版本号，版本号有JNI_VERSION_1_1，JNI_VERSION_1_2和JNI_VERSION_1_4
        //选择一个根你安装的JRE版本最近的版本号即可，不过你的JRE版本一定要等于或者高于指定的版本号
        vm_args.version = JNI_VERSION_1_6;
        vm_args.nOptions = 3;
        vm_args.options = options;
        //该参数指定是否忽略非标准的参数，如果填JNI_FLASE，当遇到非标准参数时，JNI_CreateJavaVM会返回JNI_ERR
        vm_args.ignoreUnrecognized = JNI_TRUE;
        QString path = QDir::currentPath();
        path.append("\\jre\\bin\\client\\jvm.dll");

        HINSTANCE hInstance = ::LoadLibraryA(path.toLocal8Bit().constData());
        // HINSTANCE hInstance = ::LoadLibraryW(path.toStdWString().c_str());
        if (hInstance == NULL)
        {
            qDebug() << "LoadLibraryW hInstance == NULL";
            hInstance = LoadLibraryEx(path.toStdWString().c_str(), NULL, LOAD_LIBRARY_AS_DATAFILE);
        }
        if (hInstance == NULL)
        {
            qDebug() << "LoadLibraryEx hInstance == NULL";
            return false;
        }
        //取得里面的JNI_CreateJavaVM函数指针
        PFunCreateJavaVM funCreateJavaVM = (PFunCreateJavaVM)::GetProcAddress(hInstance, "JNI_CreateJavaVM");
        //调用JNI_CreateJavaVM创建虚拟机
        ret = (*funCreateJavaVM)(&jvm, (void**)&env, &vm_args);
        if(ret < 0){
            qDebug() << "CreateJVM Created Failed !";
        }else{
            qDebug() << "CreateJVM Created!, jvm Not NULL";
            jvm->AttachCurrentThread((void **) &env, NULL);
        }
     }else {
         qDebug() << "CreateJVM jvm Not NULL";
         jvm->AttachCurrentThread((void **) &env, NULL);
     }
}

// 测试方法
bool Jvm::invokeMethod(QString clz, QString method, QString methodSign, QMap<QString, QString> parms){
    BeginJVM();
    //查找test.Demo类，返回JAVA类的CLASS对象
    jclass cls = env->FindClass(clz.toLatin1().data());
    //根据类的CLASS对象获取该类的实例
    jobject obj = env->AllocObject(cls);

    //获取类中的方法，最后一个参数是方法的签名，通过javap -s -p 文件名可以获得
    //javap -s -p -classpath C:\QtWorksapce\managefile-build-de
//    sktop-Qt_4_7_4_for_Desktop_-_MSVC2008__Qt_SDK____\jre\jar\sendmail\ com.util.mai
//    l.SendMail
    jmethodID mid = env->GetMethodID(cls, method.toLatin1().data(), methodSign.toLatin1().data());


    if(method == "makeindex"){
        DocDao dao;
        QString idexpath = parms.value("indexpath");
        QString dbpath = parms.value("dbpath");

        QString filepath = parms.value("filepath");
        // 全部执行
        if(filepath.isEmpty()){
            QList<Doc> docList = dao.selectDocsByIndexFlag("0");
            QByteArray tempindexpath = idexpath.toLocal8Bit();
            char* cindexpath = tempindexpath.data();

            QByteArray tempdbpath = dbpath.toLocal8Bit();
            char* cdbpath = tempdbpath.data();

            jstring arg1 = NewJString(env, cindexpath);
            jstring arg4 = NewJString(env, cdbpath);
            Doc file;
            foreach(file, docList){
                qDebug() << "index file ---" << file.DOCUMENT_LOCATION;

                QByteArray tempfilepath = file.DOCUMENT_LOCATION.toLocal8Bit();
                char* filepath = tempfilepath.data();

                jstring arg2 = NewJString(env, filepath);
                jstring arg3 = NewJString(env, file.DOCUMENT_GUID.toLatin1().data());
                env->CallObjectMethod(obj, mid, arg1, arg2, arg3, arg4);

                file.DOCUMENT_INDEXFLG = "1";
                DocDao::updateDoc(file);
            }
        }else{
            QString docuuid = parms.value("docuuid");

            QByteArray tempindexpath = idexpath.toLocal8Bit();
            char* cindexpath = tempindexpath.data();

            QByteArray tempdbpath = dbpath.toLocal8Bit();
            char* cdbpath = tempdbpath.data();

            jstring arg1 = NewJString(env, cindexpath);
            jstring arg4 = NewJString(env, cdbpath);

            qDebug() << "index file ---" << filepath;

            QByteArray tempfilepath = filepath.toLocal8Bit();
            char* filepath = tempfilepath.data();

            jstring arg2 = NewJString(env, filepath);
            jstring arg3 = NewJString(env, docuuid.toLatin1().data());
            env->CallObjectMethod(obj, mid, arg1, arg2, arg3, arg4);

            Doc doc;
            doc.DOCUMENT_GUID = docuuid;
            doc.DOCUMENT_INDEXFLG = "1";
            DocDao::updateDoc(doc);
        }
    }

    if(method == "deleteIndex"){
        QString idexpath = parms.value("indexpath");
        QString dbpath = parms.value("dbpath");
        QString docuuid = parms.value("docuuid");
        QString filepath = parms.value("filepath");


        QByteArray tempindexpath = idexpath.toLocal8Bit();
        char* cindexpath = tempindexpath.data();

        QByteArray tempdbpath = dbpath.toLocal8Bit();
        char* cdbpath = tempdbpath.data();

        jstring arg1 = NewJString(env, cindexpath);
        jstring arg4 = NewJString(env, cdbpath);

        qDebug() << "delete index file ---" << filepath;

        QByteArray tempfilepath = filepath.toLocal8Bit();
        char* cfilepath = tempfilepath.data();

        jstring arg2 = NewJString(env, cfilepath);
        jstring arg3 = NewJString(env, docuuid.toLatin1().data());
        env->CallObjectMethod(obj, mid, arg1, arg2, arg3, arg4);

        ResultDao dao;
        dao.deleteResultByDocUid(docuuid);
    }

    if(method == "queryAll"){

        QString keyword = parms.value("keyword");
        QString searchType = parms.value("searchtype");
        QString indexpath = parms.value("indexpath");
        QString dbpath = parms.value("dbpath");

        QByteArray tempkeyword = keyword.toLocal8Bit();
        char* ckeyword = tempkeyword.data();

        QByteArray tempindexpath = indexpath.toLocal8Bit();
        char* cindexpath = tempindexpath.data();

        QByteArray tempdbpath = dbpath.toLocal8Bit();
        char* cdbpath = tempdbpath.data();


        jstring arg1 = NewJString(env, searchType.toLatin1().data());
        jstring arg2 = NewJString(env, ckeyword);
        jstring arg3 = NewJString(env, cindexpath);
        jstring arg4 = NewJString(env, cdbpath);


        qDebug() << "searchType>> " << searchType;
        qDebug() << "keyword--> " << ckeyword;
        qDebug() << "indexpath>> " << cindexpath;
        qDebug() << "dbpath>> " << cdbpath;
        env->CallObjectMethod(obj, mid, arg1, arg2, arg3, arg4);

    }

    if(method == "sendMail"){

        // (String host, String username, String pwd, String fromaddr, String toaddr, String title, String content)

        QString host = "mx1.ourhost.cn";
        QString username = "support@slfile.net";
        QString pwd = "changsong2008";
        QString fromaddr = "support@slfile.net";

        QString toaddr = parms.value("toaddr");
        QString title = parms.value("title");
        QString content = parms.value("content");

        QByteArray temptitle = title.toLocal8Bit();
        char* ctitle = temptitle.data();

        QByteArray tempcontent = content.toLocal8Bit();
        char* ccontent = tempcontent.data();

        jstring arg1 = NewJString(env, host.toLatin1().data());
        jstring arg2 = NewJString(env, username.toLatin1().data());
        jstring arg3 = NewJString(env, pwd.toLatin1().data());
        jstring arg4 = NewJString(env, fromaddr.toLatin1().data());
        jstring arg5 = NewJString(env, toaddr.toLatin1().data());
        jstring arg6 = NewJString(env, ctitle);
        jstring arg7 = NewJString(env, ccontent);

        env->CallObjectMethod(obj, mid, arg1, arg2, arg3, arg4, arg5, arg6, arg7);

    }
    //EndJVM();
    return true;
}
// 结束JVM
bool Jvm::EndJVM()
{
    //关闭JVM
    jvm->DestroyJavaVM();
    return true;
}
string Jvm::JStringToCString (JNIEnv *env, jstring str)// (jstring str, LPTSTR desc, int desc_len)
{
    if(str == NULL)
    {
        return "";
    }
    //在VC中wchar_t是用来存储宽字节字符(UNICODE)的数据类型
    int len = env->GetStringLength(str);
    wchar_t *w_buffer = new wchar_t[len+1];
    char *c_buffer = new char[2*len+1];
    ZeroMemory(w_buffer,(len+1)*sizeof(wchar_t));
    //使用GetStringChars而不是GetStringUTFChars
    const jchar * jcharString = env->GetStringChars(str, 0);
    wcscpy(w_buffer,jcharString);
    env->ReleaseStringChars(str,jcharString);
    ZeroMemory(c_buffer,(2*len+1)*sizeof(char));
    //调用字符编码转换函数(Win32 API)将UNICODE转为ASCII编码格式字符串
    len = WideCharToMultiByte(CP_ACP,0,w_buffer,len,c_buffer,2*len,NULL,NULL);
    string cstr = c_buffer;
    delete[] w_buffer;
    delete[] c_buffer;

    return cstr;
}

jstring Jvm::NewJString(JNIEnv *env, char *str)
{
    if(!env || !str)
    {
        return 0;
    }
    int slen = strlen(str);
    jchar* buffer = new jchar[slen];
    int len = MultiByteToWideChar(CP_ACP, 0, str, strlen(str),buffer,slen);
    if(len>0 && len < slen)
    {
        buffer[len] = 0;
    }
    jstring js = env->NewString(buffer,slen);
    delete [] buffer;
    return js;
}


