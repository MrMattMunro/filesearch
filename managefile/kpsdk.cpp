#include <QDebug>

#include "kpsdk.h"
#include "utils.h"

KpSDK::KpSDK(QObject *parent) :
    QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    eLoop = new QEventLoop(this);
    mRet=-1;
    mIsAppPath=true;
    mIsToRecyle=true;
    mIsOverWrite=true;
    connect(this,SIGNAL(helloworld()),this,SLOT(reqTknReplyFinished()));
}
KpSDK::~KpSDK()
{
    delete manager;
}

//签名常用参数偷懒添加···做成一个函数 囧~
void KpSDK::addTknNonceTimes(QString &paraStr, const QString &consKeyStr)
{
    paraStr.append(OACONSUMER_KEY); //cosumer_key
    paraStr.append(consKeyStr);
    paraStr.append("&");
    paraStr.append(OANONCE);        //oauth_nonce
    paraStr.append(Utils::getRandNonce());
    paraStr.append("&");
    paraStr.append(OATIMESTAMP);    //oauth_timestamp
    paraStr.append(Utils::getTimeStamp());
    //qDebug()<<Utils::getTimeStamp();
}

//打开文件
int KpSDK::openFile(QByteArray &buf, const QString &filePath)
{
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly))
    {
        buf=file.readAll();
    }
    file.close();
    return buf.size();
}

//---------------------------------------请求临时token
//发送请求
void KpSDK::reqReqTmpToken()
{
    QString reqTokenUrl=buildReqTknUrl(mConsumerKey, mConsumerSecret);
    inputUrl.setUrl(reqTokenUrl.toLatin1());
    request.setUrl(inputUrl);
    mReqTknReply = manager->get(request);

    qDebug() << "inputUrl" << inputUrl;
    connect(mReqTknReply, SIGNAL(finished()), eLoop, SLOT(quit()));
    eLoop->exec();
    reqTknReplyFinished();
}

//构造url
QString KpSDK::buildReqTknUrl(const QString &consKeyStr, const QString &consKeySecretStr)
{
    QString para;
    QString _reqTokenUrl = KP_REQUEST_TOKEN_SRC_URL;
    _reqTokenUrl.append("?");
    _reqTokenUrl.append(OASIGNATURE);
    _reqTokenUrl.append(getReqTknSignature(para,consKeyStr,consKeySecretStr));//添加签名
    _reqTokenUrl.append("&");
    _reqTokenUrl.append(Utils::removeUrlEncode(para));//添加去掉编码的参数
    return _reqTokenUrl;
}

//构造reqToken 获取签名
//  oauth_consumer_key
//  oauth_nonce
//  oauth_timestamp
QString KpSDK::getReqTknSignature(QString &paraStr, const QString &consKeyStr, const QString &consKeySecretStr)
{
    QString ReqTokenBaseUrl;
    ReqTokenBaseUrl.clear(); //将请求的URI路径进行URL编码
    ReqTokenBaseUrl.append("GET&");
    ReqTokenBaseUrl.append(QUrl::toPercentEncoding(KP_REQUEST_TOKEN_SRC_URL));
    ReqTokenBaseUrl.append("&");

    //对参数进行升序排列 然后合并
    addTknNonceTimes(paraStr,consKeyStr);
    ReqTokenBaseUrl.append(QUrl::toPercentEncoding(paraStr));// 对参数进行编码 然后合并成源串
    return  Utils::hmacSha1((consKeySecretStr+"&").toLatin1(),ReqTokenBaseUrl.toLatin1()); //返回签名
}

//收到临时oauth_token和secret反馈完成
void KpSDK::reqTknReplyFinished()
{
    mRet= mReqTknReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray getBuf=mReqTknReply->readAll();

    qDebug() << "mRet:" << mRet;
    if(KP_CORRECT_RESULT==mRet)//返回正确
    {
        QList<QByteArray> list=getBuf.simplified().split('"');
        mTmpTokenSecret=list.at(TMP_TOKEN_SECRET_INDEX);
        mTmpToken=list.at(TMP_TOKEN_INDEX);
        //setAuthorise(mTmpToken);//进行鉴权

    } else
    {
        mTmpToken="NULL";
        mTmpTokenSecret="NULL";
    }
    mReqTknReply->deleteLater();
    eLoop->exit();
}

//---------------------------------------------请求正式token
//请求正式token
void KpSDK::reqAcessToken()
{
    QString acesTknUrl=buildAcesTknUrl(mConsumerKey,mConsumerSecret,\
                                       mTmpToken,mTmpTokenSecret);
    inputUrl.setUrl(acesTknUrl.toLatin1());
    request.setUrl(inputUrl);
    mAcesTknReply=manager->get(request);
    connect(mAcesTknReply, SIGNAL(finished()), eLoop, SLOT(quit()));
    eLoop->exec();
    acesTknReplyFinished();
}

//构造请求accessToken url
QString KpSDK::buildAcesTknUrl(const QString &consKeyStr, const QString &consKeySecretStr, \
                               const QString &tmpTknStr, const QString &tmpTknSercetStr)
{
    QString para;
    QString _acesTknUrl=KP_ACCESS_TOKEN_SRC_URL;
    _acesTknUrl.append("?");
    _acesTknUrl.append(OASIGNATURE);
    _acesTknUrl.append(getAcesTknSignature(para,consKeyStr,consKeySecretStr,\
                                           tmpTknStr,tmpTknSercetStr));
    //添加签名
    _acesTknUrl.append("&");
    _acesTknUrl.append(Utils::removeUrlEncode(para));//添加去掉编码的参数
    return _acesTknUrl;
}

//构造请求accessToken 签名
//oauth_consumer_key
//oauth_nonce
//oauth_timestamp
//oauth_token
QString KpSDK::getAcesTknSignature(QString &paraStr, const QString &consKeyStr, const QString &consKeySecretStr, \
                                   const QString &tmpTknStr, const QString &tmpTknSercetStr)
{
    QString acesTknBaseUrl;
    acesTknBaseUrl.clear(); //将请求的URI路径进行URL编码
    acesTknBaseUrl.append("GET&");
    acesTknBaseUrl.append(QUrl::toPercentEncoding(KP_ACCESS_TOKEN_SRC_URL));
    acesTknBaseUrl.append("&");

    //对参数进行升序排列 然后合并
    addTknNonceTimes(paraStr,consKeyStr);
    paraStr.append("&");
    paraStr.append(OATOKEN);
    paraStr.append(tmpTknStr);

    acesTknBaseUrl.append(QUrl::toPercentEncoding(paraStr));// 对参数进行编码 然后合并成源串

    QString secret=consKeySecretStr+"&";
    secret=secret.append(tmpTknSercetStr);
    return  Utils::hmacSha1(secret.toLatin1(),acesTknBaseUrl.toLatin1()); //返回签名
}

//反馈完成 收到accessToken
void KpSDK::acesTknReplyFinished()
{
    mRet=mAcesTknReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray getBuf=mAcesTknReply->readAll();
    qDebug() << "mRet:" << mRet;
    if(KP_CORRECT_RESULT==mRet)//返回正确
    {
        QList<QByteArray> list=getBuf.simplified().split('"');
        mAuTokenInfo.auTokenSecret=list.at(AUTHOR_TOKEN_SECRET_INDEX);
        mAuTokenInfo.auToken=list.at(AUTHOR_TOKEM_INDEX);
        mAuTokenInfo.chargedDir=list.at(AUTHOR_USR_DIR);
        QString tmpUsrId=list.at(AUTHOR_USR_ID).trimmed();
        mAuTokenInfo.usrID=tmpUsrId.mid(2,tmpUsrId.length()-3);
    }
    else
    {
        mAuTokenInfo.auTokenSecret="NULL";
        mAuTokenInfo.auToken="NULL";
        mAuTokenInfo.chargedDir="NULL";
        mAuTokenInfo.usrID="NULL";
    }
    mAcesTknReply->deleteLater();
    eLoop->exit();
}

//-----------------------------------------请求用户信息
//请求用户信息
void KpSDK::reqUsrInfo()
{
    QString usrInfoUrl=buildUsrInfoUrl(mConsumerKey,mConsumerSecret,\
                                       mAuTokenInfo.auToken,mAuTokenInfo.auTokenSecret);
    inputUrl.setUrl(usrInfoUrl.toLatin1());
    request.setUrl(inputUrl);
    mUsrInfoReply=manager->get(request);
    connect(mUsrInfoReply, SIGNAL(finished()), eLoop, SLOT(quit()));
    eLoop->exec();
    usrInfoReplyFinished();
}

//构造获取用户信息 url
QString KpSDK::buildUsrInfoUrl(const QString &consKeyStr, const QString &consKeySecretStr, \
                               const QString &oauTknStr, const QString &oauTknSercetStr)
{
    QString para;
    QString _usrInfoUrl=KP_GET_USR_INFO_URL;
    _usrInfoUrl.append("?");
    _usrInfoUrl.append(OASIGNATURE);
    _usrInfoUrl.append(getUsrInfoSignature(para,consKeyStr,consKeySecretStr,\
                                           oauTknStr,oauTknSercetStr));
    //添加签名
    _usrInfoUrl.append("&");
    _usrInfoUrl.append(Utils::removeUrlEncode(para));//添加去掉编码的参数
    return _usrInfoUrl;
}

//构造获取用户信息 的签名
//oauth_consumer_key
//oauth_nonce
//oauth_timestamp
//oauth_token
QString KpSDK::getUsrInfoSignature(QString &paraStr, const QString &consKeyStr, const QString &consKeySecretStr,\
                                   const QString &oauTknStr, const QString &oauTknSercetStr)
{
    QString getUsrInfoBaseUrl;
    getUsrInfoBaseUrl.clear(); //将请求的URI路径进行URL编码
    getUsrInfoBaseUrl.append("GET&");
    getUsrInfoBaseUrl.append(QUrl::toPercentEncoding(KP_GET_USR_INFO_URL));
    getUsrInfoBaseUrl.append("&");

    //对参数进行升序排列 然后合并
    addTknNonceTimes(paraStr,consKeyStr);
    paraStr.append("&");
    paraStr.append(OATOKEN);        //oauth_token
    paraStr.append(oauTknStr);

    getUsrInfoBaseUrl.append(QUrl::toPercentEncoding(paraStr));// 对参数进行编码 然后合并成源串

    QString secret=consKeySecretStr+"&";//构建密钥
    secret=secret.append(oauTknSercetStr);
    return  Utils::hmacSha1(secret.toLatin1(),getUsrInfoBaseUrl.toLatin1()); //返回签名
}

//收到 用户信息
void KpSDK::usrInfoReplyFinished()
{
    mRet=mUsrInfoReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray getBuf=mUsrInfoReply->readAll();
    //qDebug()<<getBuf;
    qDebug() << "mRet:" << mRet;
    if(KP_CORRECT_RESULT==mRet)//返回正确
    {
        QList<QByteArray> list=getBuf.split('"');
        QString tmpStr;//去后面一位空格，然后去2~（len-3）位
        tmpStr=list.at(USR_MAX_FILE_SIZE_INDEX).trimmed();//": 314572800, "
        mUsrInfo.maxFileSize=tmpStr.mid(2,tmpStr.length()-3);

        tmpStr=list.at(USR_TOTAL_SIZE_INDEX).trimmed();
        mUsrInfo.quotaTotal=tmpStr.mid(2,tmpStr.length()-3);

        tmpStr=list.at(USR_USED_SIZE_INDEX).trimmed();
        mUsrInfo.quotaUsed=tmpStr.mid(2,tmpStr.length()-3);
        mUsrInfo.usrName=list.at(USR_NAME_INDEX);
    }
    else
    {
        mUsrInfo.maxFileSize="NULL";
        mUsrInfo.quotaTotal="NULL";
        mUsrInfo.quotaUsed="NULL";
        mUsrInfo.usrName="NULL";
    }
    mUsrInfoReply->deleteLater();
    eLoop->exit();
}

//-------------------------------------------------获取文件夹信息
//获取文件夹信息
void KpSDK::reqMetaData()
{
    QString dataPath=QUrl::toPercentEncoding(mDataPath);
    QString metaDataUrl=buildMetaDataUrl(mConsumerKey,mConsumerSecret,\
                                       mAuTokenInfo.auToken,mAuTokenInfo.auTokenSecret,\
                                         mIsAppPath,dataPath);
    //qDebug()<<metaDataUrl;
    inputUrl.setUrl(metaDataUrl.toLatin1());
    request.setUrl(inputUrl);
    mMetaDataReply=manager->get(request);

    connect(mMetaDataReply, SIGNAL(finished()), eLoop, SLOT(quit()));
    eLoop->exec();
    metaDataReplyFinished();
}

QString KpSDK::buildMetaDataUrl(const QString &consKeyStr, const QString &consKeySecretStr,\
                                const QString &oauTknStr, const QString &oauTknSercetStr,\
                                bool &isAppPath, QString &dataPath)
{
    QString para;
    QString newGetMetaDataUrl(KP_GET_META_DATA_URL);
    if(isAppPath)
    {
        newGetMetaDataUrl.append("app_folder");
    }
    else
    {
        newGetMetaDataUrl.append("kuaipan");
    }
    if(dataPath.length()>0)
    {
        newGetMetaDataUrl.append("/");
        newGetMetaDataUrl.append(dataPath);
    }
    QString _metaDataUrl=newGetMetaDataUrl;
    _metaDataUrl.append("?");
    _metaDataUrl.append(OASIGNATURE);
    _metaDataUrl.append(getMetaDataSignature(para,consKeyStr,consKeySecretStr,\
                                             oauTknStr,oauTknSercetStr,\
                                             newGetMetaDataUrl));

    //添加签名
    _metaDataUrl.append("&");
    _metaDataUrl.append(Utils::removeUrlEncode(para));//添加去掉编码的参数
    return _metaDataUrl;
}

//构造获取文件夹信息的签名
//oauth_consumer_key
//oauth_nonce
//oauth_timestamp
//oauth_token
QString KpSDK::getMetaDataSignature(QString &paraStr, const QString &consKeyStr, const QString &consKeySecretStr, \
                                    const QString &oauTknStr, const QString &oauTknSercetStr, \
                                    QString &newGetMetaUrl)
{
    QString getMetaDataBaseUrl;
    getMetaDataBaseUrl.clear(); //将请求的URI路径进行URL编码
    getMetaDataBaseUrl.append("GET&");
    getMetaDataBaseUrl.append(QUrl::toPercentEncoding(newGetMetaUrl));
    getMetaDataBaseUrl.append("&");

    //对参数进行升序排列 然后合并
    addTknNonceTimes(paraStr,consKeyStr);
    paraStr.append("&");
    paraStr.append(OATOKEN);        //oauth_token
    paraStr.append(oauTknStr);

    getMetaDataBaseUrl.append(QUrl::toPercentEncoding(paraStr));// 对参数进行编码 然后合并成源串

    QString secret=consKeySecretStr+"&";//构建密钥
    secret=secret.append(oauTknSercetStr);
    return  Utils::hmacSha1(secret.toLatin1(),getMetaDataBaseUrl.toLatin1()); //返回签名
}

//返回可读文件(夹)信息
void KpSDK::metaDataReadReady()
{
    mRet=mMetaDataReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray getBuf=mMetaDataReply->readAll();
//        QString str=QString(getBuf).remove(' ');
//        str=str.remove(',');
//        str=str.remove('\n');
//        QList<QString> list=str.split('{');
    mJsonBuf.clear();
    mJsonBuf.append(getBuf);//返回的json不做任何处理

}

//返回可读文件(夹)信息完毕
void KpSDK::metaDataReplyFinished()
{
    mRet=mMetaDataReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray getBuf=mMetaDataReply->readAll();
    mJsonBuf.clear();
    mJsonBuf.append(getBuf);
    mMetaDataReply->deleteLater();
    eLoop->exit();
}

//----------------------------------------------新建文件夹
//创建文件夹
void KpSDK::reqCreateFloder()
{
    QString createFolderUrl=buildCreateFolderUrl(mConsumerKey,mConsumerSecret,\
                                                 mAuTokenInfo.auToken,mAuTokenInfo.auTokenSecret,\
                                                 mIsAppPath,mCreateFolderPath);
    inputUrl.setUrl(createFolderUrl.toLatin1());
    request.setUrl(inputUrl);
    qDebug()<< "reqCreateFloder:" << inputUrl;
    mCreateFolderReply=manager->get(request);
//    connect(mCreateFolderReply,SIGNAL(readyRead()),this,SLOT(createFolderReadReady()));
    //    connect(mCreateFolderReply,SIGNAL(finished()),this,SLOT(createFolderReplyFinished()));
    connect(mCreateFolderReply,SIGNAL(finished()),eLoop,SLOT(quit()));
    eLoop->exec();
    createFolderReplyFinished();
}

//构造创建文件夹rul
QString KpSDK::buildCreateFolderUrl(const QString &consKeyStr, const QString &consKeySecretStr,\
                                    const QString &oauTknStr, const QString &oauTknSercetStr, \
                                    bool &isAppPath, QString &folderName)
{
    QString para;
    QString _createFolderUrl=KP_CREATE_FOLDER_URL;
    _createFolderUrl.append("?");
    _createFolderUrl.append(OASIGNATURE);
    _createFolderUrl.append(getCreateFolderSignature(para,consKeyStr,consKeySecretStr,\
                                           oauTknStr,oauTknSercetStr,isAppPath,folderName));

    //添加签名
    _createFolderUrl.append("&");
    _createFolderUrl.append(para);//添加无编码的参数
    return _createFolderUrl;
}

//构造创建文件夹的签名
//oauth_consumer_key
//oauth_nonce
//oauth_timestamp
//oauth_token
//path
//root
QString KpSDK::getCreateFolderSignature(QString &paraStr, const QString &consKeyStr, const QString &consKeySecretStr,\
                                        const QString &oauTknStr, const QString &oauTknSercetStr,\
                                        bool &isAppPath, QString &folderName)
{
    QString createFolderBaseUrl;
    createFolderBaseUrl.clear(); //将请求的URI路径进行URL编码
    createFolderBaseUrl.append("GET&");
    createFolderBaseUrl.append(QUrl::toPercentEncoding(KP_CREATE_FOLDER_URL));
    createFolderBaseUrl.append("&");

    //对参数进行升序排列 然后合并
    addTknNonceTimes(paraStr,consKeyStr);
    paraStr.append("&");
    paraStr.append(OATOKEN);        //oauth_token
    paraStr.append(oauTknStr);

    paraStr.append("&");
    paraStr.append(FOLDER_NAME);
    paraStr.append(QString(QUrl::toPercentEncoding(folderName)));
    paraStr.append("&");
    paraStr.append(FOLDER_ROOT);
    if(isAppPath)
    {
        paraStr.append("slfile");
    }
    else
    {
        paraStr.append("kuaipan");
    }

    createFolderBaseUrl.append(QUrl::toPercentEncoding(paraStr));// 对参数进行编码 然后合并成源串
    QString secret=consKeySecretStr+"&";//构建密钥
    secret=secret.append(oauTknSercetStr);
    return  Utils::hmacSha1(secret.toLatin1(),createFolderBaseUrl.toLatin1()); //返回签名
}

//创建文件夹 反馈完毕
void KpSDK::createFolderReplyFinished()
{
    mRet=mCreateFolderReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray getBuf=mCreateFolderReply->readAll();

    qDebug() << "createFolderReplyFinished mRet:" << mRet;

    mJsonBuf.clear();
    mJsonBuf.append(getBuf);
    mCreateFolderReply->deleteLater();
    eLoop->exit();
}

//-------------------------------------------删除文件
//删除文件
void KpSDK::reqDelFile()
{
    QString delFileUrl=buildDelFileUrl(mConsumerKey,mConsumerSecret,\
                                       mAuTokenInfo.auToken,mAuTokenInfo.auTokenSecret,\
                                       mIsAppPath,mDelFilePath,mIsToRecyle);

    inputUrl.setUrl(delFileUrl.toLatin1());
    request.setUrl(inputUrl);
    mDelFileReply=manager->get(request);
    connect(mDelFileReply,SIGNAL(finished()),eLoop,SLOT(quit()));
    eLoop->exec();
    delFileReplyFinished();
}

//构造删除文件的url
QString KpSDK::buildDelFileUrl(const QString &consKeyStr, const QString &consKeySecretStr, \
                               const QString &oauTknStr, const QString &oauTknSercetStr, \
                               bool &isAppPath, QString &fileName, bool &toRecyle)
{
    QString para;
    QString _delFileUrl=KP_DEL_FILE_URL;
    _delFileUrl.append("?");
    _delFileUrl.append(OASIGNATURE);
    _delFileUrl.append(getDelFileSignature(para,consKeyStr,consKeySecretStr,\
                                           oauTknStr,oauTknSercetStr,isAppPath,fileName,toRecyle));

    //添加签名
    _delFileUrl.append("&");
    _delFileUrl.append(para);//添加无编码的参数
    return _delFileUrl;
}

//构造删除文件 的签名
//oauth_consumer_key
//oauth_nonce
//oauth_timestamp
//oauth_token
//path
//root
//to_recycle
QString KpSDK::getDelFileSignature(QString &paraStr, const QString &consKeyStr, const QString &consKeySecretStr, \
                                   const QString &oauTknStr, const QString &oauTknSercetStr, \
                                   bool &isAppPath, QString &fileName, bool &toRecyle)
{
    QString delFileBaseUrl;
    delFileBaseUrl.clear(); //将请求的URI路径进行URL编码
    delFileBaseUrl.append("GET&");
    delFileBaseUrl.append(QUrl::toPercentEncoding(KP_DEL_FILE_URL));
    delFileBaseUrl.append("&");

    //对参数进行升序排列 然后合并
    addTknNonceTimes(paraStr,consKeyStr);
    paraStr.append("&");
    paraStr.append(OATOKEN);        //oauth_token
    paraStr.append(oauTknStr);
    paraStr.append("&");
    paraStr.append(FOLDER_NAME);
    paraStr.append(QString(QUrl::toPercentEncoding(fileName)));
    paraStr.append("&");
    paraStr.append(FOLDER_ROOT);
    if(isAppPath)
    {
        paraStr.append("app_folder&");
    }
    else
    {
        paraStr.append("kuaipan&");
    }
    paraStr.append(TO_RECYLE);
    if(toRecyle)
    {
        paraStr.append("True");
    }
    else paraStr.append("False");

    delFileBaseUrl.append(QUrl::toPercentEncoding(paraStr));// 对参数进行编码 然后合并成源串
    QString secret=consKeySecretStr+"&";//构建密钥
    secret=secret.append(oauTknSercetStr);
    return  Utils::hmacSha1(secret.toLatin1(),delFileBaseUrl.toLatin1()); //返回签名
}

//删除文件反馈 完毕
void KpSDK::delFileReplyFinished()
{
    mRet=mDelFileReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray getBuf=mDelFileReply->readAll();
    mJsonBuf.clear();
    mJsonBuf.append(getBuf);
    mDelFileReply->deleteLater();
    eLoop->exit();
}

//-----------------------------------------剪切文件
//请求剪切文件
void KpSDK::reqMoveFile()
{
    QString moveFileUrl=buildMoveFileUrl(mConsumerKey,mConsumerSecret,\
                                         mAuTokenInfo.auToken,mAuTokenInfo.auTokenSecret,\
                                         mIsAppPath,mFromPath,mToPath);
    inputUrl.setUrl(moveFileUrl.toLatin1());
    request.setUrl(inputUrl);
    mMvFileReply=manager->get(request);
    connect(mMvFileReply,SIGNAL(finished()),eLoop,SLOT(quit()));
    eLoop->exec();
    moveFileReplyFinished();
}

//构造剪切文件的url
QString KpSDK::buildMoveFileUrl(const QString &consKeyStr, const QString &consKeySecretStr,\
                                const QString &oauTknStr, const QString &oauTknSercetStr, \
                                bool &isAppPath, QString &fromPath, QString &toPath)
{
    QString para;
    QString _mvFileUrl=KP_MOVE_FILE_URL;
    _mvFileUrl.append("?");
    _mvFileUrl.append(OASIGNATURE);
    _mvFileUrl.append(getMoveFileSignature(para,consKeyStr,consKeySecretStr,\
                                           oauTknStr,oauTknSercetStr,isAppPath,fromPath,toPath));
    //添加签名
    _mvFileUrl.append("&");
    _mvFileUrl.append(para);//添加无编码的参数
    return _mvFileUrl;
}

//构造剪切文件的签名
//from_path
//oauth_consumer_key
//oauth_nonce
//oauth_timestamp
//oauth_token
//root
//to_path
QString KpSDK::getMoveFileSignature(QString &paraStr, const QString &consKeyStr, const QString &consKeySecretStr, \
                                    const QString &oauTknStr, const QString &oauTknSercetStr, \
                                    bool &isAppPath, QString &fromPath, QString &toPath)
{
    QString mvFileBaseUrl;
    mvFileBaseUrl.clear(); //将请求的URI路径进行URL编码
    mvFileBaseUrl.append("GET&");
    mvFileBaseUrl.append(QUrl::toPercentEncoding(KP_MOVE_FILE_URL));
    mvFileBaseUrl.append("&");

    paraStr.append(DATA_FROM_PATH);
    paraStr.append(QUrl::toPercentEncoding(fromPath));
    paraStr.append("&");

    //对参数进行升序排列 然后合并
    addTknNonceTimes(paraStr,consKeyStr);
    paraStr.append("&");
    paraStr.append(OATOKEN);        //oauth_token
    paraStr.append(oauTknStr);

    paraStr.append("&");
    paraStr.append(FOLDER_ROOT);
    if(isAppPath)
    {
        paraStr.append("app_folder&");
    }
    else
    {
        paraStr.append("kuaipan&");
    }
    paraStr.append(DATA_TO_PATH);
    paraStr.append(QUrl::toPercentEncoding(toPath));

    mvFileBaseUrl.append(QUrl::toPercentEncoding(paraStr));// 对参数进行编码 然后合并成源串
    QString secret=consKeySecretStr+"&";//构建密钥
    secret=secret.append(oauTknSercetStr);
    return  Utils::hmacSha1(secret.toLatin1(),mvFileBaseUrl.toLatin1()); //返回签名
}

//剪切文件后反馈完毕
void KpSDK::moveFileReplyFinished()
{
    mRet=mMvFileReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray getBuf=mMvFileReply->readAll();
    mJsonBuf.clear();
    mJsonBuf.append(getBuf);
    mMvFileReply->deleteLater();
    eLoop->exit();
}

//------------------------------------------复制文件
//请求复制文件
void KpSDK::reqCopyFile()
{

    QString copyFileUrl=buildCopyFileUrl(mConsumerKey,mConsumerSecret,\
                                         mAuTokenInfo.auToken,mAuTokenInfo.auTokenSecret,\
                                         mIsAppPath,mFromPath,mToPath);
    inputUrl.setUrl(copyFileUrl.toLatin1());
    request.setUrl(inputUrl);
    mCpFileReply=manager->get(request);

    connect(mCpFileReply,SIGNAL(finished()),eLoop,SLOT(quit()));
    eLoop->exec();
    copyFileReplyFinished();
}

//构造复制文件的 url
QString KpSDK::buildCopyFileUrl(const QString &consKeyStr, const QString &consKeySecretStr, \
                                const QString &oauTknStr, const QString &oauTknSercetStr,\
                                bool &isAppPath, QString &fromPath, QString &toPath)
{
    QString para;
    QString _cpFileUrl=KP_COPY_FILE_URL;
    _cpFileUrl.append("?");
    _cpFileUrl.append(OASIGNATURE);
    _cpFileUrl.append(getCopyFileSignature(para,consKeyStr,consKeySecretStr,\
                                           oauTknStr,oauTknSercetStr,isAppPath,fromPath,toPath));
    //添加签名
    _cpFileUrl.append("&");
    _cpFileUrl.append(para);//添加无编码的参数
    return _cpFileUrl;

}

//构造复制文件的 签名
//from_path
//oauth_consumer_key
//oauth_nonce
//oauth_timestamp
//oauth_token
//root
//to_path
QString KpSDK::getCopyFileSignature(QString &paraStr, const QString &consKeyStr, const QString &consKeySecretStr, \
                                    const QString &oauTknStr, const QString &oauTknSercetStr, \
                                    bool &isAppPath, QString &fromPath, QString &toPath)
{
    QString cpFileBaseUrl;
    cpFileBaseUrl.clear(); //将请求的URI路径进行URL编码
    cpFileBaseUrl.append("GET&");
    cpFileBaseUrl.append(QUrl::toPercentEncoding(KP_COPY_FILE_URL));
    cpFileBaseUrl.append("&");

    paraStr.append(DATA_FROM_PATH);
    paraStr.append(QUrl::toPercentEncoding(fromPath));
    paraStr.append("&");

    //对参数进行升序排列 然后合并
    addTknNonceTimes(paraStr,consKeyStr);
    paraStr.append("&");
    paraStr.append(OATOKEN);        //oauth_token
    paraStr.append(oauTknStr);

    paraStr.append("&");
    paraStr.append(FOLDER_ROOT);
    if(isAppPath)
    {
        paraStr.append("app_folder&");
    }
    else
    {
        paraStr.append("kuaipan&");
    }
    paraStr.append(DATA_TO_PATH);
    paraStr.append(QUrl::toPercentEncoding(toPath));

    cpFileBaseUrl.append(QUrl::toPercentEncoding(paraStr));// 对参数进行编码 然后合并成源串
    QString secret=consKeySecretStr+"&";//构建密钥
    secret=secret.append(oauTknSercetStr);
    return  Utils::hmacSha1(secret.toLatin1(),cpFileBaseUrl.toLatin1()); //返回签名
}

//复制文件 反馈结束
void KpSDK::copyFileReplyFinished()
{
    mRet=mCpFileReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray getBuf=mCpFileReply->readAll();
    mJsonBuf.clear();
    mJsonBuf.append(getBuf);
    mCpFileReply->deleteLater();
    eLoop->exit();
}

//------------------------------------------获取上传节点
//获取上传节点
void KpSDK::reqUploadLocate()
{
    QString uploadLocUrl=buildUploadLocateUrl(mConsumerKey,mConsumerSecret,\
                                              mAuTokenInfo.auToken,mAuTokenInfo.auTokenSecret);
    inputUrl.setUrl(uploadLocUrl.toLatin1());
    request.setUrl(inputUrl);
    mUploadLocateReply=manager->get(request);
    connect(mUploadLocateReply,SIGNAL(finished()),eLoop,SLOT(quit()));
    eLoop->exec();
    getUploadLocateFinished();
}

//构造获取上传节点 url
QString KpSDK::buildUploadLocateUrl(const QString &consKeyStr, const QString &consKeySecretStr,\
                                    const QString &oauTknStr, const QString &oauTknSercetStr)
{
    QString para;
    QString _locateUrl=KP_UPLOAD_LOCATE_URL;
    _locateUrl.append("?");
    _locateUrl.append(OASIGNATURE);
    _locateUrl.append(getUploadLocateSignature(para,consKeyStr,consKeySecretStr,\
                                           oauTknStr,oauTknSercetStr));
    //添加签名
    _locateUrl.append("&");
    _locateUrl.append(para);//添加无编码的参数
    return _locateUrl;
}

//构造获取上传节点 签名
QString KpSDK::getUploadLocateSignature(QString &paraStr, const QString &consKeyStr, const QString &consKeySecretStr, \
                                        const QString &oauTknStr, const QString &oauTknSercetStr)
{
    QString upLocaBaseUrl;
    upLocaBaseUrl.clear(); //将请求的URI路径进行URL编码
    upLocaBaseUrl.append("GET&");
    upLocaBaseUrl.append(QUrl::toPercentEncoding(KP_UPLOAD_LOCATE_URL));
    upLocaBaseUrl.append("&");

    //对参数进行升序排列 然后合并
    addTknNonceTimes(paraStr,consKeyStr);
    paraStr.append("&");
    paraStr.append(OATOKEN);        //oauth_token
    paraStr.append(oauTknStr);

    upLocaBaseUrl.append(QUrl::toPercentEncoding(paraStr));// 对参数进行编码 然后合并成源串
    QString secret=consKeySecretStr+"&";//构建密钥
    secret=secret.append(oauTknSercetStr);
    return  Utils::hmacSha1(secret.toLatin1(),upLocaBaseUrl.toLatin1()); //返回签名
}

//获取到上传节点
void KpSDK::getUploadLocateFinished()
{
    mRet=mUploadLocateReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray getBuf=mUploadLocateReply->readAll();
    qDebug() << "mRet:" << mRet;
    if(KP_CORRECT_RESULT==mRet)
    {
        QList<QByteArray> list=getBuf.split('"');
        mUploadNode=list.at(3);//上传节点
    }
    else
    {
        mUploadNode.clear();
        mUploadNode.append(getBuf);
    }
    mUploadLocateReply->deleteLater();
    eLoop->exit();
}

//------------------------------------------上传文件
//上传文件
void KpSDK::reqUploadFile()
{
    QByteArray data;
    QString uploadFileUrl=buildUploadFileUrl(mConsumerKey,mConsumerSecret,\
                                             mAuTokenInfo.auToken,mAuTokenInfo.auTokenSecret,\
                                             mIsOverWrite,mIsAppPath,mToPath,mUploadNode);

    inputUrl.setUrl(uploadFileUrl.toLatin1());
    uploadRequest.setUrl(inputUrl);
    buildMultiPart(data,mFromPath);//使用multipart方式上传 构造multipart包
    mUploadFileReply=manager->post(uploadRequest,data);//上传
    connect(mUploadFileReply,SIGNAL(finished()),eLoop,SLOT(quit()));
    eLoop->exec();
    uploadFileReplyFinished();
}

//构造上传文件 url
QString KpSDK::buildUploadFileUrl(const QString &consKeyStr, const QString &consKeySecretStr,\
                                  const QString &oauTknStr, const QString &oauTknSercetStr, \
                                  const bool &isOverWrite, const bool &isAppPath, const QString &toPath, const QString &preStr)
{
    QString para;
    QString fullUploadFileUrl=preStr+KP_UPLOAD_FILE_URL;
    QString _sendFileUrl=fullUploadFileUrl;
    _sendFileUrl.append("?");
    _sendFileUrl.append(OASIGNATURE);
    _sendFileUrl.append(getUploadFileSignature(para,consKeyStr,consKeySecretStr,\
                                               oauTknStr,oauTknSercetStr,\
                                               isOverWrite,isAppPath,\
                                               toPath,fullUploadFileUrl));
    //添加签名
    _sendFileUrl.append("&");
    _sendFileUrl.append(para);//添加无编码的参数
    return _sendFileUrl;
}

//构造上传文件 签名
QString KpSDK::getUploadFileSignature(QString &paraStr, const QString &consKeyStr, const QString &consKeySecretStr, \
                                      const QString &oauTknStr, const QString &oauTknSercetStr,\
                                      const bool &isOverWrite, const bool &isAppPath, const QString &toPath, const QString &fullUrl)
{
    QString uploadFileBaseUrl;
    uploadFileBaseUrl.clear(); //将请求的URI路径进行URL编码
    uploadFileBaseUrl.append("POST&");
    uploadFileBaseUrl.append(QUrl::toPercentEncoding(fullUrl));
    uploadFileBaseUrl.append("&");


    //对参数进行升序排列 然后合并
    addTknNonceTimes(paraStr,consKeyStr);
    paraStr.append("&");
    paraStr.append(OATOKEN);        //oauth_token
    paraStr.append(oauTknStr);

    paraStr.append("&");
    paraStr.append(UPLOAD_OVER_WRITE); //overwrite
    if(isOverWrite)
        paraStr.append("True");
    else paraStr.append("False");

    paraStr.append("&");
    paraStr.append(FOLDER_NAME);       //path
    paraStr.append(QUrl::toPercentEncoding(toPath));
    paraStr.append("&");
    paraStr.append(FOLDER_ROOT);        //root
    if(isAppPath)
    {
        paraStr.append("app_folder");
    }
    else
    {
        paraStr.append("kuaipan");
    }

    uploadFileBaseUrl.append(QUrl::toPercentEncoding(paraStr));// 对参数进行编码 然后合并成源串
    QString secret=consKeySecretStr+"&";//构建密钥
    secret=secret.append(oauTknSercetStr);
    return  Utils::hmacSha1(secret.toLatin1(),uploadFileBaseUrl.toLatin1()); //返回签名
}

// 构造MultiPart 包
void KpSDK::buildMultiPart(QByteArray &data,const QString &fileName)
{
    QByteArray needToUploadFile;
    if(openFile(needToUploadFile,fileName)<=0)
    {//文件打开失败
        return ;
    }

    QString crlf="\r\n";
    QString boundary="--------Michael" + Utils::getRandNonce();
    QString contentType="multipart/form-data; boundary="+boundary; //开始的头部信息

    QString endBoundary=crlf+"--"+boundary+"--"+crlf; //结束处

    boundary="--"+boundary+crlf; //每行数据开头
    QByteArray bond=boundary.toLatin1();

    data.append(bond);


    data.append(QString("Content-Disposition: form-data; name=\"file\"; filename=\""\
                        +fileName+"\""+crlf).toLatin1());
    data.append(QString("Content-Type: application/octet-stream"+crlf).toLatin1());

    data.append(crlf.toLatin1());
    data.append(needToUploadFile);
    data.append(endBoundary.toLatin1());
    uploadRequest.setHeader(QNetworkRequest::ContentTypeHeader, contentType.toLatin1());
    uploadRequest.setHeader(QNetworkRequest::ContentLengthHeader, QVariant(data.size()).toString());
}

//上传文件完毕
void KpSDK::uploadFileReplyFinished()
{
    mRet=mUploadFileReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray getBuf=mUploadFileReply->readAll();
    mJsonBuf.clear();
    mJsonBuf.append(getBuf);
    mUploadFileReply->deleteLater();
    eLoop->exit();
}

//------------------------------------------下载文件
//下载文件
void KpSDK::reqDownLoadFile()
{
    mDwnFileBuf.clear();

    dwnFile=new QFile(mToPath);
    if(!dwnFile->open(QIODevice::WriteOnly))
    {   //如果打开文件失败，则删除file，并使file指针为0，然后返回
        delete dwnFile;
        dwnFile =NULL;
        return;
    }
    QString downLoadFileUrl=buildDownFileUrl(mConsumerKey,mConsumerSecret,\
                                             mAuTokenInfo.auToken,mAuTokenInfo.auTokenSecret,\
                                             mIsAppPath,mFromPath);
    inputUrl.setUrl(downLoadFileUrl.toLatin1());
    request.setUrl(inputUrl);
    mDownloadFileReply=manager->get(request);
    connect(mDownloadFileReply,SIGNAL(finished()),eLoop,SLOT(quit()));
    eLoop->exec();
    downLoadFileReplyFinished();
}

//构造 下载文件 url
QString KpSDK::buildDownFileUrl(const QString &consKeyStr, const QString &consKeySecretStr,\
                                const QString &oauTknStr, const QString &oauTknSercetStr, \
                                bool &isAppPath, const QString &fromPath)
{
    QString para;
    QString _dwnFileUrl=KP_DOWNLOAD_FILE_URL;
    _dwnFileUrl.append("?");
    _dwnFileUrl.append(OASIGNATURE);
    _dwnFileUrl.append(getDownFileSignature(para,consKeyStr,consKeySecretStr,\
                                           oauTknStr,oauTknSercetStr,isAppPath,fromPath));
    //添加签名
    _dwnFileUrl.append("&");
    _dwnFileUrl.append(para);//添加无编码的参数
    return _dwnFileUrl;
}

//构造 下载文件的签名
//oauth_consumer_key
//oauth_nonce
//oauth_timestamp
//oauth_token
//path
//root
QString KpSDK::getDownFileSignature(QString &paraStr, const QString &consKeyStr, const QString &consKeySecretStr, \
                                    const QString &oauTknStr, const QString &oauTknSercetStr, \
                                    bool &isAppPath, const QString &fromPath)
{
    QString dwnFileBaseUrl;
    dwnFileBaseUrl.clear(); //将请求的URI路径进行URL编码
    dwnFileBaseUrl.append("GET&");
    dwnFileBaseUrl.append(QUrl::toPercentEncoding(KP_DOWNLOAD_FILE_URL));
    dwnFileBaseUrl.append("&");

    paraStr.append(DATA_FROM_PATH);
    paraStr.append(QUrl::toPercentEncoding(fromPath));
    paraStr.append("&");

    //对参数进行升序排列 然后合并
    addTknNonceTimes(paraStr,consKeyStr);
    paraStr.append("&");
    paraStr.append(OATOKEN);        //oauth_token
    paraStr.append(oauTknStr);

    paraStr.append("&");
    paraStr.append(FOLDER_NAME);
    paraStr.append(QUrl::toPercentEncoding(fromPath));
    paraStr.append("&");
    paraStr.append(FOLDER_ROOT);
    if(isAppPath)
    {
        paraStr.append("app_folder");
    }
    else
    {
        paraStr.append("kuaipan");
    }

    dwnFileBaseUrl.append(QUrl::toPercentEncoding(paraStr));// 对参数进行编码 然后合并成源串
    QString secret=consKeySecretStr+"&";//构建密钥
    secret=secret.append(oauTknSercetStr);
    return  Utils::hmacSha1(secret.toLatin1(),dwnFileBaseUrl.toLatin1()); //返回签名
}

//反馈完毕 获取重定向地址
void KpSDK::downLoadFileReplyFinished()
{
    mRet = mDownloadFileReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if(301==mRet ||  302==mRet)//重定位值
    {
        QEventLoop   *downloadEloop=new QEventLoop();
        for(int i=0;i<mDownloadFileReply->rawHeaderPairs().count();i++)
        {
            //qDebug()<<"Pairs()"<<mDownloadFileReply->rawHeaderPairs().at(i) ;
            if( "Location"==mDownloadFileReply->rawHeaderPairs().at(i).first)
            {
                QUrl realDwnFileUrl=QUrl(mDownloadFileReply->rawHeaderPairs().at(i).second);
                mDwnFileRealReply=manager->get(QNetworkRequest(realDwnFileUrl));//用重定向地址重新下载

                connect(mDwnFileRealReply,SIGNAL(finished()),downloadEloop,SLOT(quit()));
                downloadEloop->exec();
                dwnFileRealReplyFinished();
                break;
            }
        }
        downloadEloop->exit();
    }
    mDownloadFileReply->deleteLater();
    eLoop->exit();
}

//下载完成 写入文件
void KpSDK::dwnFileRealReplyFinished()
{
    mRet=mDwnFileRealReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    // 返回正确
    qDebug() << "mRet:" << mRet;
    if(KP_CORRECT_RESULT==mRet)
    {
        if (dwnFile!=NULL) dwnFile->write(mDwnFileRealReply->readAll());
    }
    dwnFile->flush();
    dwnFile->close();
    delete dwnFile;
    dwnFile=NULL;
    mDwnFileRealReply->deleteLater();
}

//--------------------------------------分享文件
//请求分享文件
void KpSDK::reqShareFile()
{
    QString shareFile=QString(QUrl::toPercentEncoding(mFromPath));
    QString shareFileUrl=buildShareFileUrl(mConsumerKey,mConsumerSecret,\
                                           mAuTokenInfo.auToken,mAuTokenInfo.auTokenSecret,\
                                           mIsAppPath,shareFile);
    inputUrl.setUrl(shareFileUrl.toLatin1());
    request.setUrl(inputUrl);
    mShareFileReply=manager->get(request);
    connect(mShareFileReply,SIGNAL(finished()),eLoop,SLOT(quit()));
    eLoop->exec();
    shareFileReplyFinished();
}

//构造分享文件 url
QString KpSDK::buildShareFileUrl(const QString &consKeyStr, const QString &consKeySecretStr,\
                                 const QString &oauTknStr, const QString &oauTknSercetStr, \
                                 bool &isAppPath, const QString &dataPath)
{
    QString para;
    QString newShareFileUrl(KP_SHARE_FILE_URL);
    if(isAppPath)
    {
        newShareFileUrl.append("app_folder");
    }
    else newShareFileUrl.append("kuaipan");
    if(dataPath.length()>0)
    {
        newShareFileUrl.append("/");
        newShareFileUrl.append(dataPath);
    }

    QString _shareFileUrl=newShareFileUrl;
    _shareFileUrl.append("?");
    _shareFileUrl.append(OASIGNATURE);
    _shareFileUrl.append(getShareFileSignature(para,consKeyStr,consKeySecretStr,\
                                               oauTknStr,oauTknSercetStr,\
                                               newShareFileUrl));
    // 添加签名
    _shareFileUrl.append("&");
    // 添加无编码的参数
    _shareFileUrl.append(para);
    return _shareFileUrl;
}

//构造 分享文件 签名
//oauth_consumer_key
//oauth_nonce
//oauth_timestamp
//oauth_token
QString KpSDK::getShareFileSignature(QString &paraStr, const QString &consKeyStr, const QString &consKeySecretStr, \
                                     const QString &oauTknStr, const QString &oauTknSercetStr, \
                                     const QString &newShareFileUrl)
{
    QString shareFileBaseUrl;
    shareFileBaseUrl.clear(); //将请求的URI路径进行URL编码
    shareFileBaseUrl.append("GET&");
    shareFileBaseUrl.append(QUrl::toPercentEncoding(newShareFileUrl));
    shareFileBaseUrl.append("&");

    //对参数进行升序排列 然后合并
    addTknNonceTimes(paraStr,consKeyStr);
    paraStr.append("&");
    paraStr.append(OATOKEN);        //oauth_token
    paraStr.append(oauTknStr);

    shareFileBaseUrl.append(QUrl::toPercentEncoding(paraStr));// 对参数进行编码 然后合并成源串
    QString secret=consKeySecretStr+"&";//构建密钥
    secret=secret.append(oauTknSercetStr);
    return  Utils::hmacSha1(secret.toLatin1(),shareFileBaseUrl.toLatin1()); //返回签名
}

//反馈完毕 提取分享的url
void KpSDK::shareFileReplyFinished()
{
    mRet=mShareFileReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray getBuf = mShareFileReply->readAll();
    mJsonBuf.clear();
    mJsonBuf.append(getBuf);
    mShareFileReply->deleteLater();
    eLoop->exit();
}



