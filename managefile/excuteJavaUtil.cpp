#include "windows.h"
#include "jni.h"
#include <string>
#include <iostream>
#include <QDir>
#include <excuteJavaUtil.h>
#include <utils.h>
#include <QDebug>

using namespace std;

//jstring NewJString(JNIEnv *env, char *str);
//string  JStringToCString (JNIEnv *env, jstring str);

bool ExcuteJavaUtil::indexFiles(QList<Doc> files)
{

    // 先调用JNI_GetCreatedJavaVMs()，如果返回0就调用JNI_CreateJavaVM，否则不调用

    //定义一个函数指针，下面用来指向JVM中的JNI_CreateJavaVM函数
    typedef jint (WINAPI *PFunCreateJavaVM)(JavaVM **, void **, void *);
    typedef jint (WINAPI *PFunGetCreatedJavaVMs)(JavaVM **, void **, void *);
    int res;
    JavaVMInitArgs vm_args;
    JavaVMOption options[3];
    JavaVM *jvm;
    JNIEnv *env;
    qDebug() << "indexFiles 3";

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

    options[1].optionString = "-Djava.class.path=.;.\\jre\\jar\\bcmail-jdk14-132.jar;.\\jre\\jar\\bcprov-jdk14-132.jar;.\\jre\\jar\\commons-collections-3.2.1.jar;.\\jre\\jar\\commons-logging-1.1.jar;.\\jre\\jar\\geronimo-stax-api_1.0_spec-1.0.jar;.\\jre\\jar\\htmllexer.jar;.\\jre\\jar\\htmlparser.jar;.\\jre\\jar\\indexFile.jar;.\\jre\\jar\\log4j-1.2.13.jar;.\\jre\\jar\\lucene-core-3.3.0.jar;.\\jre\\jar\\lucene-gosen-1.2-dev-ipadic.jar;.\\jre\\jar\\lucene-highlighter-3.3.0.jar;.\\jre\\jar\\lucene-memory-3.3.0.jar;.\\jre\\jar\\nekohtml.jar;.\\jre\\jar\\paoding-analysis.jar;.\\jre\\jar\\poi-3.8-beta3-20110606.jar;.\\jre\\jar\\poi-excelant-3.8-beta3-20110606.jar;.\\jre\\jar\\poi-ooxml-3.8-beta3-20110606.jar;.\\jre\\jar\\poi-ooxml-schemas-3.8-beta3-20110606.jar;.\\jre\\jar\\poi-scratchpad-3.8-beta3-20110606.jar;.\\jre\\jar\\stax-api-1.0.1.jar;.\\jre\\jar\\xercesImpl.jar;.\\jre\\jar\\xmlbeans-2.3.0.jar";
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
    //加载JVM.DLL动态库
    // HINSTANCE hInstance = ::LoadLibraryA("C:\\QtWorksapce\\managefile\\jre\\bin\\client\\jvm.dll");
    HINSTANCE hInstance = ::LoadLibraryA(path.toLocal8Bit().constData());
    if (hInstance == NULL)
    {
        qDebug() << "indexFiles hInstance == NULL";
        return false;
    }
    //取得里面的JNI_CreateJavaVM函数指针
    PFunGetCreatedJavaVMs funGetCreatedJavaVMs = (PFunGetCreatedJavaVMs)::GetProcAddress(hInstance, "JNI_GetCreatedJavaVMs");
    // 先调用JNI_GetCreatedJavaVMs()，如果返回0就调用JNI_CreateJavaVM，否则不调用

    //调用JNI_CreateJavaVM创建虚拟机
    res = (*funGetCreatedJavaVMs)(&jvm, (void**)&env, &vm_args);
    if( res == 0){
        //取得里面的JNI_CreateJavaVM函数指针
        PFunCreateJavaVM funCreateJavaVM = (PFunCreateJavaVM)::GetProcAddress(hInstance, "JNI_CreateJavaVM");
        //调用JNI_CreateJavaVM创建虚拟机
        res = (*funCreateJavaVM)(&jvm, (void**)&env, &vm_args);
    }
    if (res < 0)
    {
       return false;
    }
    //查找test.Demo类，返回JAVA类的CLASS对象
    jclass cls = env->FindClass("com/searchlocal/lucene/IndexMaker");
    //根据类的CLASS对象获取该类的实例
    jobject obj = env->AllocObject(cls);

    //获取类中的方法，最后一个参数是方法的签名，通过javap -s -p 文件名可以获得
    jmethodID mid = env->GetMethodID(cls, "makeindex", "(Ljava/lang/String;Ljava/lang/String;)Z");


//        javap -s -p -classpath C:\QtWorksapce\managefile-build-de
//        sktop-Qt_4_7_4_for_Desktop_-_MSVC2008__Qt_SDK____\jre\jar\indexFile\ com.searchl
//        ocal.lucene.IndexMaker

    //构造参数并调用对象的方法  中文乱码
    // char *indexpath = "C:\\Documents and Settings\\Administrator\\Local Settings\\Application Data\\slfile\\index";
    QString indexpath = "C:\\Documents and Settings\\Administrator\\Local Settings\\Application Data\\slfile\\index";
    jstring arg1 = NewJString(env, indexpath.toLatin1().data());

//    char *filepath = "E:\\MyDocuments\\Qt\\Document+For+QT.doc";
//    QString filepath = "F:\\Document\\测试\\Bug及改进列表.xls";
//    jstring arg2 = NewJString(env, filepath.toLatin1().data());

//   // jstring msg = (jstring) env->CallObjectMethod(obj, mid, arg1, arg2);
//    env->CallObjectMethod(obj, mid, arg1, arg2);

    Doc file;
    foreach(file, files){
        // jstring msg = (jstring) env->CallObjectMethod(obj, mid, arg1, arg2);
        qDebug() << "index file ---" << file.DOCUMENT_LOCATION;
        jstring arg2 = NewJString(env, file.DOCUMENT_LOCATION.toLatin1().data());
        env->CallObjectMethod(obj, mid, arg1, arg2);
    }

    // string temp = JStringToCString(env, msg);

    // QDebug << JStringToCString(env, msg);

    //QString qstr = QString::fromStdString(temp);

//    str = qstr.toStdString();
//    qstr = QString::fromStdString(str);

    //销毁虚拟机并释放动态库
    jvm->DestroyJavaVM();
    ::FreeLibrary(hInstance);
    return true;
}


bool ExcuteJavaUtil::queryIndex(const QString &searchType, const QString &keyword)
{

    //定义一个函数指针，下面用来指向JVM中的JNI_CreateJavaVM函数
    typedef jint (WINAPI *PFunCreateJavaVM)(JavaVM **, void **, void *);

    int res;
    JavaVMInitArgs vm_args;
    JavaVMOption options[3];
    JavaVM *jvm;
    JNIEnv *env;

    /*设置初始化参数*/
    //disable JIT，这是JNI文档中的解释，具体意义不是很清楚 ，能取哪些值也不清楚。
    //从JNI文档里给的示例代码中搬过来的
    options[0].optionString = "-Djava.compiler=NONE";

    //设置classpath，如果程序用到了第三方的JAR包，也可以在这里面包含进来
        // char *optionString;
    QString option = "-Djava.class.path=.;";
    option.append(".\\jre\\jar\\commons-collections-3.2.1.jar;");
    option.append(".\\jre\\jar\\commons-logging-1.1.jar;");
    option.append(".\\jre\\jar\\geronimo-stax-api_1.0_spec-1.0.jar;");
    option.append(".\\jre\\jar\\indexFile.jar;");
    option.append(".\\jre\\jar\\log4j-1.2.13.jar;");
    option.append(".\\jre\\jar\\lucene-core-3.3.0.jar;");
    option.append(".\\jre\\jar\\lucene-gosen-1.2-dev-ipadic.jar;");
    option.append(".\\jre\\jar\\lucene-highlighter-3.3.0.jar;");
    option.append(".\\jre\\jar\\lucene-memory-3.3.0.jar;");
    option.append(".\\jre\\jar\\nekohtml.jar;");
    option.append(".\\jre\\jar\\paoding-analysis.jar;");
    option.append(".\\jre\\jar\\stax-api-1.0.1.jar;");
    option.append(".\\jre\\jar\\xercesImpl.jar;");
    option.append(".\\jre\\jar\\xmlbeans-2.3.0.jar;");


    // options[1].optionString = "-Djava.class.path=.;.\\jre\\jar\\bcmail-jdk14-132.jar;.\\jre\\jar\\bcprov-jdk14-132.jar;.\\jre\\jar\\commons-collections-3.2.1.jar;.\\jre\\jar\\commons-logging-1.1.jar;.\\jre\\jar\\geronimo-stax-api_1.0_spec-1.0.jar;.\\jre\\jar\\htmllexer.jar;.\\jre\\jar\\htmlparser.jar;.\\jre\\jar\\indexFile.jar;.\\jre\\jar\\log4j-1.2.13.jar;.\\jre\\jar\\lucene-core-3.3.0.jar;.\\jre\\jar\\lucene-gosen-1.2-dev-ipadic.jar;.\\jre\\jar\\lucene-highlighter-3.3.0.jar;.\\jre\\jar\\lucene-memory-3.3.0.jar;.\\jre\\jar\\nekohtml.jar;.\\jre\\jar\\paoding-analysis.jar;.\\jre\\jar\\poi-3.8-beta3-20110606.jar;.\\jre\\jar\\poi-excelant-3.8-beta3-20110606.jar;.\\jre\\jar\\poi-ooxml-3.8-beta3-20110606.jar;.\\jre\\jar\\poi-ooxml-schemas-3.8-beta3-20110606.jar;.\\jre\\jar\\poi-scratchpad-3.8-beta3-20110606.jar;.\\jre\\jar\\stax-api-1.0.1.jar;.\\jre\\jar\\xercesImpl.jar;.\\jre\\jar\\xmlbeans-2.3.0.jar;.\\jre\\jar\\json-lib-2.3-jdk13.jar;.\\jre\\jar\\commons-lang.jar;.\\jre\\jar\\ezmorph-1.0.4.jar;.\\jre\\jar\\commons-collections.jar;.\\jre\\jar\\commons-beanutils-1.8.0.jar";
     options[1].optionString = "-Djava.class.path=.;.\\jre\\jar\\commons-collections-3.2.1.jar;.\\jre\\jar\\commons-logging-1.1.jar;.\\jre\\jar\\geronimo-stax-api_1.0_spec-1.0.jar;.\\jre\\jar\\indexFile.jar;.\\jre\\jar\\log4j-1.2.13.jar;.\\jre\\jar\\lucene-core-3.3.0.jar;.\\jre\\jar\\lucene-gosen-1.2-dev-ipadic.jar;.\\jre\\jar\\lucene-highlighter-3.3.0.jar;.\\jre\\jar\\lucene-memory-3.3.0.jar;.\\jre\\jar\\nekohtml.jar;.\\jre\\jar\\paoding-analysis.jar;.\\jre\\jar\\stax-api-1.0.1.jar;.\\jre\\jar\\xercesImpl.jar;.\\jre\\jar\\xmlbeans-2.3.0.jar";

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
    //加载JVM.DLL动态库
    // HINSTANCE hInstance = ::LoadLibraryA("C:\\QtWorksapce\\managefile\\jre\\bin\\client\\jvm.dll");
    HINSTANCE hInstance = ::LoadLibraryA(path.toLocal8Bit().constData());
    if (hInstance == NULL)
    {
        return false;
    }
    //取得里面的JNI_CreateJavaVM函数指针
    PFunCreateJavaVM funCreateJavaVM = (PFunCreateJavaVM)::GetProcAddress(hInstance, "JNI_CreateJavaVM");
    //调用JNI_CreateJavaVM创建虚拟机
    res = (*funCreateJavaVM)(&jvm, (void**)&env, &vm_args);
    if (res < 0)
    {
        return false;
    }
    // 查找test.Demo类，返回JAVA类的CLASS对象
    jclass cls = env->FindClass("com/searchlocal/lucene/ContentSearcher");
    // 根据类的CLASS对象获取该类的实例
    jobject obj = env->AllocObject(cls);

    //获取类中的方法，最后一个参数是方法的签名，通过javap -s -p 文件名可以获得
    jmethodID mid = env->GetMethodID(cls, "queryAll", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z");


//        javap -s -p -classpath C:\QtWorksapce\managefile-build-de
//        sktop-Qt_4_7_4_for_Desktop_-_MSVC2008__Qt_SDK____\jre\jar\indexFile\ com.searchl
//        ocal.lucene.ContentSearcher

    //构造参数并调用对象的方法  中文乱码
    // char *indexpath = "C:\\Documents and Settings\\Administrator\\Local Settings\\Application Data\\slfile\\index";

    jstring arg1 = NewJString(env, searchType.toLatin1().data());
    jstring arg2 = NewJString(env, keyword.toLatin1().data());

    QString indexpath = Utils::getLocateIndexPath();
    jstring arg3 = NewJString(env, indexpath.toLatin1().data());

    QString dbpath = Utils::getLocateDbPath();
    dbpath.append(QDir::separator()).append("MF");
    jstring arg4 = NewJString(env, dbpath.toLatin1().data());

    qDebug() << "searchType>> " << searchType;
    qDebug() << "keyword>> " << keyword;
    qDebug() << "indexpath>> " << indexpath;
    qDebug() << "dbpath>> " << dbpath;
    env->CallObjectMethod(obj, mid, arg1, arg2, arg3, arg4);
//    qDebug() << "temp>> " << msg;
//    string temp = JStringToCString(env, msg);

//    QString jsonresult = QString::fromStdString(temp);
//    qDebug() << "jsonresult>> " << jsonresult;

    //销毁虚拟机并释放动态库
//    jvm->DestroyJavaVM();
//    ::FreeLibrary(hInstance);
    return true;
}

string ExcuteJavaUtil::JStringToCString (JNIEnv *env, jstring str)// (jstring str, LPTSTR desc, int desc_len)
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

jstring ExcuteJavaUtil::NewJString(JNIEnv *env, char *str)
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
    jstring js = env->NewString(buffer,len);
    delete [] buffer;
    return js;
}

