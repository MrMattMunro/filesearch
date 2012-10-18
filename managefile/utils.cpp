/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/

#include <QIcon>
#include <QPixmapCache>
#include <QDir>
#include <QDesktopServices>
#include <QApplication>
#include <QListWidgetItem>
#include <QObject>
#include <QCryptographicHash>
#include <QSysInfo>
#include <QNetworkInterface>
#ifdef Q_WS_WIN
#include <windows.h>
#include <shlobj.h>
#endif

#include "utils.h"
#include "publicfun.h"

#define ICON_DIR ":/icons"
#define TRANSLATION_DIR ":/ts"

// 取得操作系统
QString Utils::getSysOs()
{
    if (QSysInfo::WindowsVersion == QSysInfo::WV_32s){
        return "WV_32s";
    }
    if (QSysInfo::WindowsVersion == QSysInfo::WV_95){
        return "WV_95";
    }
    if (QSysInfo::WindowsVersion == QSysInfo::WV_98){
        return "WV_98";
    }
    if (QSysInfo::WindowsVersion == QSysInfo::WV_Me){
        return "WV_Me";
    }
    if (QSysInfo::WindowsVersion == QSysInfo::WV_NT){
        return "WV_NT";
    }
    if (QSysInfo::WindowsVersion == QSysInfo::WV_2000){
        return "WV_2000";
    }
    if (QSysInfo::WindowsVersion == QSysInfo::WV_XP){
        return "WV_XP";
    }
    if (QSysInfo::WindowsVersion == QSysInfo::WV_2003){
        return "WV_2003";
    }
    if (QSysInfo::WindowsVersion == QSysInfo::WV_VISTA){
        return "WV_VISTA";
    }

    return "";
}
// 取得IP
QString Utils::getIPAddress(){
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list)
    {
       if(address.protocol() == QAbstractSocket::IPv4Protocol){
           //IPv4地址
           if (address.toString().contains("127.0.")){
               continue;
           }
           return address.toString();
        }
   }
}

QIcon Utils::getIcon(const QString & fileName)
{
	QPixmap pm;

	if (! QPixmapCache::find(fileName, &pm))
	{
                QPixmap npm(QString(ICON_DIR) + QDir::separator() + fileName);
		QPixmapCache::insert(fileName, npm);
		return npm;
	}

	return pm;
}

QPixmap Utils::getPixmap(const QString & fileName)
{
        return QPixmap(QString(ICON_DIR)  + QDir::separator() + fileName);
}

QString Utils::getTranslator(const QString & localeName)
{
    QString local(localeName);
    if( localeName == "zh"){
        local = "zh_cn";
    }

    return QString("%1/managefile_%2.qm").arg(TRANSLATION_DIR).arg(local);
}



bool Utils::updateObjectTree(const QString & sql)
{
	if (sql.isNull())
		return false;
	QString tmp(sql.trimmed().toUpper());
	if (tmp.left(4) == "DROP" || tmp.left(6) == "CREATE" || tmp.left(5) == "ALTER")
		return true;
	return false;
}

QString Utils::getLocatePath()
{
    QString locpath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
    locpath.append(QDir::separator()).append("slfile");
    QDir *dir=new QDir(locpath);
    if(!dir->exists()){
       dir->mkdir(locpath);
    }
    return locpath;
}

QString Utils::getLocateDownloadPath(QString basepath)
{
    QString locpath;
    if(basepath.length() == 0){
        locpath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
        locpath.append(QDir::separator()).append("slfile");
        locpath.append(QDir::separator()).append("download");
    }else{
        locpath = basepath.append(QDir::separator()).append("download");
    }

    QDir *dir=new QDir(locpath);
    if(!dir->exists()){
       dir->mkdir(locpath);
    }
    return locpath;
}

QString Utils::getLocateNotesPath(QString basepath)
{
    QString locpath;
    if(basepath.length() == 0){
        locpath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
        locpath.append(QDir::separator()).append("slfile");
        locpath.append(QDir::separator()).append("note");
    }else{
        locpath = basepath.append(QDir::separator()).append("note");
    }

    QDir *dir=new QDir(locpath);
    if(!dir->exists()){
       dir->mkdir(locpath);
    }
    return locpath;
}

QString Utils::getLocateIndexPath(QString basepath)
{   
    QString locpath;
    if(basepath.length() == 0){
        locpath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
        locpath.append(QDir::separator()).append("slfile");
        locpath.append(QDir::separator()).append("index");
    }else{
        locpath = basepath.append(QDir::separator()).append("index");
    }

    QDir *dir=new QDir(locpath);
    if(!dir->exists()){
       dir->mkdir(locpath);
    }
    return locpath;
}

QString Utils::getLocateDbPath(QString basepath)
{
    QString locpath;
    if(basepath.length() == 0){
        locpath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
        locpath.append(QDir::separator()).append("slfile");
        locpath.append(QDir::separator()).append("db");
    }else{
        locpath = basepath.append(QDir::separator()).append("db");
    }

    QDir *dir=new QDir(locpath);
    if(!dir->exists()){
       dir->mkdir(locpath);
    }
    return locpath;
}

QString Utils::getSavePagePath(QString basepath)
{
    QString locpath;
    if(basepath.length() == 0){
        locpath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
        locpath.append(QDir::separator()).append("slfile");
        locpath.append(QDir::separator()).append("page");
    }else{
        locpath = basepath.append(QDir::separator()).append("page");
    }

    QDir *dir=new QDir(locpath);
    if(!dir->exists()){
       dir->mkdir(locpath);
    }
    return locpath;
}

QString Utils::getSaveDocPath(QString basepath)
{
    QString locpath;
    if(basepath.length() == 0){
        locpath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
        locpath.append(QDir::separator()).append("slfile");
        locpath.append(QDir::separator()).append("doc");
    }else{
        locpath = basepath.append(QDir::separator()).append("doc");
    }

    QDir *dir=new QDir(locpath);
    if(!dir->exists()){
       dir->mkdir(locpath);
    }
    return locpath;
}

QString Utils::getSaveLogPath(QString basepath)
{
    QString locpath;
    if(basepath.length() == 0){
        locpath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
        locpath.append(QDir::separator()).append("slfile");
        locpath.append(QDir::separator()).append("log");
    }else{
        locpath = basepath.append(QDir::separator()).append("log");
    }

    QDir *dir=new QDir(locpath);
    if(!dir->exists()){
       dir->mkdir(locpath);
    }
    return locpath;
}

QString Utils::getBackUpPath(QString basepath)
{
    QString locpath;
    if(basepath.length() == 0){
        locpath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
        locpath.append(QDir::separator()).append("slfile");
        locpath.append(QDir::separator()).append("backup");
    }else{
        locpath = basepath.append(QDir::separator()).append("backup");
    }

    QDir *dir=new QDir(locpath);
    if(!dir->exists()){
       dir->mkdir(locpath);
    }
    return locpath;
}

// 根据目录path取得最底层目录名
QString Utils::getDirNameByPath(const QString & path)
{
    QString temp = path;
    temp = temp.right(temp.length() - temp.lastIndexOf(QDir::separator()) - 1);
    return temp;
}


QDir Utils::directoryOf(const QString & subdir)
{

    QDir dir(QApplication::applicationDirPath());
    #if defined(Q_OS_WIN)
        if (dir.dirName().toLower() == "debug"
                || dir.dirName().toLower() == "release"
                || dir.dirName().toLower() == "bin"){
            dir.cdUp();
        }

    #elif defined(Q_OS_MAC)
        if (dir.dirName() == "MacOS") {
            dir.cdUp();
            dir.cdUp();
            dir.cdUp();
        }
    #endif
    dir.cd(subdir);
    return dir;
}

QString Utils::getMD5Str(const QString & str)
{

    QString md5;
    QByteArray bb;
    bb = QCryptographicHash::hash (str.toAscii(), QCryptographicHash::Md5 );
    return md5.append(bb.toHex());
}

QString Utils::getSysLang()
{
    return QLocale::system().name().left(2);
}

// 获取程序启动快捷方式
QString Utils::getStartUpPath()
{
    QString strPath;
 #ifdef Q_WS_WIN
    LPITEMIDLIST    pidl;
    LPMALLOC        pShellMalloc;
    wchar_t         szDir[1024];
    if (SUCCEEDED(SHGetMalloc(&pShellMalloc)))
   {
       if (SUCCEEDED(SHGetSpecialFolderLocation(NULL, CSIDL_STARTUP, &pidl)))
       {
          if (SHGetPathFromIDList(pidl, szDir))
         {
               strPath = QString::fromWCharArray(szDir) + "\\Solo.lnk";
           }
            pShellMalloc->Free(pidl);
       }
       pShellMalloc->Release();
   }
#endif
    return strPath;
}

// 设置是否自动运行
void Utils::setAutoRunStatus(bool bAutoRun)//{{{
{
   QString strExe = QApplication::applicationFilePath();
   QString strLink = getStartUpPath();
   if (bAutoRun)
   {
#ifdef Q_WS_WIN
        HRESULT hr = CoInitialize(NULL);
       if (SUCCEEDED(hr))
       {
            IShellLink *pisl;
            hr = CoCreateInstance(CLSID_ShellLink, NULL,
                    CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&pisl);
            if (SUCCEEDED(hr))
           {
               IPersistFile* pIPF;

               //这里是我们要创建快捷方式的原始文件地址
                pisl->SetPath(strExe.toStdWString().c_str());
               hr = pisl->QueryInterface(IID_IPersistFile, (void**)&pIPF);
               if (SUCCEEDED(hr))
                {
                   //这里是我们要创建快捷方式的目标地址
                   pIPF->Save(strLink.toStdWString().c_str(), FALSE);
                   pIPF->Release();
                }
               pisl->Release();
            }
            CoUninitialize();
       }
#endif
    }
    else
    {
        QFile::remove(strLink);
    }
}//}}}

// 获取自动运行状态
bool Utils::getAutoRunStatus()//{{{
{
   QString strLink = getStartUpPath();
   bool bAutoRun = QFile::exists(strLink);
   return bAutoRun;
}//}}}

Document Utils::convertDoc(Doc doc){
    Document document;
    document.setDocuuid(doc.DOCUMENT_GUID);
    document.setDocTitle(doc.DOCUMENT_TITLE);
    document.setDirUuid(doc.DIR_GUID);
    document.setDocLoc(doc.DOCUMENT_LOCATION);
    document.setDocName(doc.DOCUMENT_NAME);
    document.setDocSeo(doc.DOCUMENT_SEO);
    document.setDocUrl(doc.DOCUMENT_URL);
    document.setDocAuthor(doc.DOCUMENT_AUTHOR);
    document.setDocKeyWord(doc.DOCUMENT_KEYWORDS);
    document.setDocType(doc.DOCUMENT_TYPE);
    document.setDocOwner(doc.DOCUMENT_OWNER);
    document.setDtCreated(doc.DT_CREATED);
    document.setDtModified(doc.DT_MODIFIED);
    document.setDtAccessed(doc.DT_ACCESSED);
    document.setDocIconIndex(doc.DOCUMENT_ICON_INDEX);
    document.setDocSync(doc.DOCUMENT_SYNC);
    document.setDocProtect(doc.DOCUMENT_PROTECT);
    document.setDocEncode(doc.DOCUMENT_ENCODE);
    document.setReadCount(doc.DOCUMENT_READ_COUNT);
    document.setRelateCount(doc.DOCUMENT_RELATE_COUNT);
    document.setIndexFlg(doc.DOCUMENT_INDEXFLG);
    document.setOpenFlg(doc.DOCUMENT_OPERFLG);
    document.setDelFlg(doc.DELETE_FLAG);
    document.setVersion(doc.MF_VERSION);

    return document;
}

TableResult Utils::convertResult(Result result){
    TableResult tableResult;
    tableResult.setDocuuid(result.DOC_UUID);
    tableResult.setKeyword(result.KEY_WORD);
    tableResult.setFiletype(result.FILE_TYPE);
    tableResult.setFilepath(result.FILE_PATH);
    tableResult.setFilename(result.FILE_NAME);
    tableResult.setDesp(result.DESP);
    tableResult.setContent(result.CONTENT);
    tableResult.setSheetname(result.SHEET_NAME);
    tableResult.setRownb(result.ROW_NB);
    tableResult.setPage(result.PAGE);
    tableResult.setDtcreatede(result.DT_CREATED);

    return tableResult;
}

//hmacSha1算法实现
QString Utils::hmacSha1(QByteArray key, QByteArray baseString)
{
    int blockSize = 64; // HMAC-SHA-1 block size, defined in SHA-1 standard
    if (key.length() > blockSize) { // if key is longer than block size (64), reduce key length with SHA-1 compression
        key = QCryptographicHash::hash(key, QCryptographicHash::Sha1);
    }

    QByteArray innerPadding(blockSize, char(0x36)); // initialize inner padding with char "6"
    QByteArray outerPadding(blockSize, char(0x5c)); // initialize outer padding with char "\"
    // ascii characters 0x36 ("6") and 0x5c ("\") are selected because they have large
    // Hamming distance (http://en.wikipedia.org/wiki/Hamming_distance)

    for (int i = 0; i < key.length(); i++) {
        innerPadding[i] = innerPadding[i] ^ key.at(i); // XOR operation between every byte in key and innerpadding, of key length
        outerPadding[i] = outerPadding[i] ^ key.at(i); // XOR operation between every byte in key and outerpadding, of key length
    }
    QByteArray total = outerPadding;
    QByteArray part = innerPadding;
    part.append(baseString);
    total.append(QCryptographicHash::hash(part, QCryptographicHash::Sha1));
    QByteArray hashed = QCryptographicHash::hash(total, QCryptographicHash::Sha1);
    //return  hashed.toBase64();//原版的不返回url编码的

    QString signatureStr=hashed.toBase64(); //这里返回url编码
    return QUrl::toPercentEncoding(signatureStr);
}


//返回随机数 oauth_nonce
QString Utils::getRandNonce()
{
    QTime time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    return QString().number(qrand());
}

//返回当前时间
QString Utils::getTimeStamp()
{
    time_t curTime=time(0);
    return QString().number(curTime);
}

//去除url编码
QString Utils::removeUrlEncode(const QString &urlStr)
{
    QUrl url;
    url.setEncodedUrl(urlStr.toAscii());
    return url.toString();
}


QString Utils::stringToUnicode(QString str)
{
    // 这里传来的字符串一定要加tr，main函数里可以加 QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    //  例如：str=tr("你好");
    const QChar *q;
    QChar qtmp;
    QString str0, strout;
    int num;
    q=str.unicode();
    int len=str.count();
    for(int i=0;i<len;i++)
    {   qtmp =(QChar)*q++;
        num= qtmp.unicode();
        if(num<255)
            strout+="00"; //英文或数字前加"00"

        str0=str0.setNum(num,16);//变成十六进制数

        strout+=str0;
    }
    return strout;
}

QString Utils::unicodeToString(QString str)
{
    //例如 str="4F60597D";
    int temp[400];
    QChar qchar[100];
    QString strOut;
    bool ok;
    int count=str.count();
    int len=count/4;
    for(int i=0;i<count;i+=4)
    {
     temp[i] = str.mid(i,4).toInt(&ok,16);//每四位转化为16进制整型
     qchar[i/4] = temp[i];
     QString str0(qchar, len);
     strOut=str0;
    }
    return strOut;
}

QString Utils::getKpanRoot()
{
    QStringList<QString> roots;
    roots.append("C:\\");
    roots.append("D:\\");
    roots.append("E:\\");
    roots.append("F:\\");
    roots.append("G:\\");
    roots.append("H:\\");
    roots.append("I:\\");
    roots.append("J:\\");
    roots.append("K:\\");
    roots.append("L:\\");

    for (int var = 0; var < roots.size(); ++var) {
         QString root = roots.at(var);
         root.append("快盘");
         QFile file(root);
         if(file.exists()){
             return root;
         }
    }
}

//QString Utils::s2q(const QString &s)
//{
////    return QString(QString::fromLocal8Bit(s.c_str()));
//    return "";
//}

//QString Utils::q2s(const QString &s)
//{
//    return QString((const char *)s.toLocal8Bit());
//}








