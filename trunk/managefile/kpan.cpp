#include <utils.h>


#include "kpsdk.h"
#include "kpan.h"



//获取临时token、secret和认证url
//输入：consumerKey    consumerSecret
//输出：tmpOauthToken  tmpOauthTokenSecret     authoriseUrl
//返回: http 状态
int Kpan::kpReqTmpToken(QString &tmpOauthToken,QString &tmpOauthTokenSecret,\
                                                     QString &authoriseUrl,\
                                                     const QString &consumerKey,const QString &consumerSecret)
{
    KpSDK *kp=new KpSDK();
    kp->mConsumerKey=consumerKey;
    kp->mConsumerSecret=consumerSecret;
    kp->reqReqTmpToken();

    tmpOauthToken=kp->mTmpToken;
    tmpOauthTokenSecret=kp->mTmpTokenSecret;
    authoriseUrl = QString(KP_AUTHORISE_SRC_URL).append(tmpOauthToken);

    int ret = kp->mRet;
    delete kp;
    return ret;
}

//获取accessToken
//输入:consumerKey     consumerSecret         tmpOauthToken  tmpOauthTokenSecret
//输出：oauthToken     oauthTokenSecret        usrID       chargedDir
//返回: http 状态
int Kpan::kpAccessToken(QString &oauth_token, QString &oauth_token_secret,\
                                                      QString &user_id,      QString &charged_dir,\
                                                      const QString &consumerKey,const QString &consumerSecret,\
                                                      const QString &tmpOauthToken,const QString &tmpOauthTokenSecret
                                                      )
{
    KpSDK *kp=new KpSDK();
    kp->mConsumerKey = consumerKey;
    kp->mConsumerSecret = consumerSecret;
    kp->mTmpToken=tmpOauthToken;
    kp->mTmpTokenSecret=tmpOauthTokenSecret;
    kp->reqAcessToken();
    oauth_token = kp->mAuTokenInfo.auToken;
    oauth_token_secret = kp->mAuTokenInfo.auTokenSecret;
    user_id=kp->mAuTokenInfo.usrID;
    charged_dir=kp->mAuTokenInfo.chargedDir;

    int ret=kp->mRet;
    delete kp;
    return ret;
}

//获取用户信息
//输入: consumerKey consumerSecret            oauthToken    oauthTokenSecret
//输出：max_file_size   user_name       quota_used       quota_total
//返回: http 状态
int Kpan::kpUsrInfo(QString &max_file_size, QString &user_name,\
                                                  QString &quota_used,    QString &quota_total,\
                                                  const QString &consumerKey,const QString &consumerSecret,\
                                                  const QString &oauthToken,const QString &oauthTokenSecret
                                                  )
{
    KpSDK *kp=new KpSDK();
    kp->mConsumerKey=consumerKey;
    kp->mConsumerSecret=consumerSecret;
    kp->mAuTokenInfo.auToken=oauthToken;
    kp->mAuTokenInfo.auTokenSecret=oauthTokenSecret;
    kp->reqUsrInfo();
    max_file_size=kp->mUsrInfo.maxFileSize;
    user_name=kp->mUsrInfo.usrName;
    quota_used=kp->mUsrInfo.quotaUsed;
    quota_total=kp->mUsrInfo.quotaTotal;

    int ret=kp->mRet;
    delete kp;
    return ret;
}

//获取文件(夹)信息
//输入: consumerKey consumerSecret  oauthToken    oauthTokenSecret    isAppPath   dataPath
//isAppPath 若应用访问权限路径为kuaipan则为false,否为true
//dataPath  是指要获取的文件(夹)路径+名
//输出：jsonMetaData
//返回: http 状态
int Kpan::kpMetaData(QString &jsonMetaData,\
                                                  const QString &consumerKey,const QString &consumerSecret,\
                                                  const QString &oauthToken,const QString &oauthTokenSecret,
                                                  const bool   &isAppPath, const QString &dataPath
                                                  )
{
    KpSDK *kp=new KpSDK();
    kp->mConsumerKey=consumerKey;
    kp->mConsumerSecret=consumerSecret;
    kp->mAuTokenInfo.auToken=oauthToken;
    kp->mAuTokenInfo.auTokenSecret=oauthTokenSecret;
    kp->mIsAppPath=isAppPath;
    kp->mDataPath=dataPath;
    kp->reqMetaData();
    jsonMetaData=QString(kp->mJsonBuf);

    int ret=kp->mRet;
    delete kp;
    return ret;
}

//新建文件夹
//输入: consumerKey consumerSecret  oauthToken    oauthTokenSecret    isAppPath   floderPath
//isAppPath 若应用访问权限路径为kuaipan则为false,否为true
//floderPath  是指要新建的文件夹路径+名
//输出：jsonCreateFolder
//返回: http 状态
int Kpan::kpCreateFolder(QString &jsonCreateFolder,\
                                                    const QString &consumerKey,const QString &consumerSecret,\
                                                    const QString &oauthToken,const QString &oauthTokenSecret,
                                                    const bool   &isAppPath, const QString &floderPath
                                                    )
{
    KpSDK *kp=new KpSDK();
    kp->mConsumerKey=consumerKey;
    kp->mConsumerSecret=consumerSecret;
    kp->mAuTokenInfo.auToken=oauthToken;
    kp->mAuTokenInfo.auTokenSecret=oauthTokenSecret;
    kp->mIsAppPath=isAppPath;
    kp->mCreateFolderPath=floderPath;
    kp->reqCreateFloder();
    jsonCreateFolder=QString(kp->mJsonBuf);

    int ret=kp->mRet;
    delete kp;
    return ret;
}

//删除文件夹
//输入: consumerKey consumerSecret  oauthToken    oauthTokenSecret    isAppPath   floderPath  to_recycle
//isAppPath 若应用访问权限路径为kuaipan则为false,否为true
//floderPath  是指要获取的文件(夹)路径+名
//to_recycle  是否删除到回收站？
//输出：jsonDelFile
int Kpan::kpDelFile(QString &jsonDelFile,\
                                               const QString &consumerKey,const QString &consumerSecret,\
                                               const QString &oauthToken,const QString &oauthTokenSecret,
                                               const bool   &isAppPath, const QString &floderPath,
                                               const bool   &to_recycle
                                               )
{
    KpSDK *kp=new KpSDK();
    kp->mConsumerKey=consumerKey;
    kp->mConsumerSecret=consumerSecret;
    kp->mAuTokenInfo.auToken=oauthToken;
    kp->mAuTokenInfo.auTokenSecret=oauthTokenSecret;
    kp->mIsAppPath=isAppPath;
    kp->mIsToRecyle=to_recycle;
    kp->mDelFilePath=floderPath;
    kp->reqDelFile();
    jsonDelFile = QString(kp->mJsonBuf);

    int ret=kp->mRet;
    delete kp;
    return ret;
}

//移动文件(夹)
//输入: consumerKey consumerSecret  oauthToken    oauthTokenSecret    isAppPath   fromPath    toPath
//isAppPath 若应用访问权限路径为kuaipan则为false,否为true
//输出：jsonMvFile
//返回: http 状态
int Kpan::kpMvFile(QString &jsonMvFile,\
                                              const QString &consumerKey,const QString &consumerSecret,\
                                              const QString &oauthToken,const QString &oauthTokenSecret,
                                              const bool   &isAppPath, \
                                              const QString &fromPath, const QString &toPath
                                              )
{
    KpSDK *kp=new KpSDK();
    kp->mConsumerKey=consumerKey;
    kp->mConsumerSecret=consumerSecret;
    kp->mAuTokenInfo.auToken=oauthToken;
    kp->mAuTokenInfo.auTokenSecret=oauthTokenSecret;
    kp->mIsAppPath=isAppPath;
    kp->mFromPath=fromPath;
    kp->mToPath=toPath;
    kp->reqMoveFile();
    jsonMvFile=QString(kp->mJsonBuf);

    int ret=kp->mRet;
    delete kp;
    return ret;
}

//复制文件(夹)
//输入: consumerKey consumerSecret  oauthToken    oauthTokenSecret    isAppPath   fromPath    toPath
//isAppPath 若应用访问权限路径为kuaipan则为false,否为true
//输出：jsonMvFile
int Kpan::kpCpFile(QString &jsonCpFile,\
                                              const QString &consumerKey,const QString &consumerSecret,\
                                              const QString &oauthToken,const QString &oauthTokenSecret,
                                              const bool   &isAppPath, \
                                              const QString &fromPath, const QString &toPath
                                              )
{
    KpSDK *kp=new KpSDK();
    kp->mConsumerKey=consumerKey;
    kp->mConsumerSecret=consumerSecret;
    kp->mAuTokenInfo.auToken=oauthToken;
    kp->mAuTokenInfo.auTokenSecret=oauthTokenSecret;
    kp->mIsAppPath=isAppPath;
    kp->mFromPath=fromPath;
    kp->mToPath=toPath;
    kp->reqCopyFile();
    jsonCpFile=QString(kp->mJsonBuf);

    int ret=kp->mRet;
    delete kp;
    return ret;
}

//获取上传节点
//输入: consumerKey consumerSecret  oauthToken    oauthTokenSecret
//输出：uploadNode
//返回: http 状态
int Kpan::kpUploadLocate(QString &uploadNode,\
                                                       const QString &consumerKey,const QString &consumerSecret,\
                                                       const QString &oauthToken,const QString &oauthTokenSecret
                                                       )
{
    KpSDK *kp=new KpSDK();
    kp->mConsumerKey=consumerKey;
    kp->mConsumerSecret=consumerSecret;
    kp->mAuTokenInfo.auToken=oauthToken;
    kp->mAuTokenInfo.auTokenSecret=oauthTokenSecret;
    kp->reqUploadLocate();
    uploadNode=kp->mUploadNode;
    int ret=kp->mRet;
    delete kp;
    return ret;
}

//上传文件
//输入: consumerKey consumerSecret  oauthToken    oauthTokenSecret    、
//     isOverWrite isAppPath   uploadNode  fromPath toPath
//输出：jsonUploadFile
//返回: http 状态
int Kpan::kpUploadFile(QString &jsonUploadFile,
                                                  const QString &consumerKey,const QString &consumerSecret,\
                                                  const QString &oauthToken,const QString &oauthTokenSecret,\
                                                  const bool &isOverWrite, const bool &isAppPath,\
                                                  const QString &uploadNode, const QString &fromPath,
                                                  const QString &toPath
                                                  )
{
    KpSDK *kp=new KpSDK();
    kp->mConsumerKey=consumerKey;
    kp->mConsumerSecret=consumerSecret;
    kp->mAuTokenInfo.auToken=oauthToken;
    kp->mAuTokenInfo.auTokenSecret=oauthTokenSecret;
    kp->mIsOverWrite=isOverWrite;
    kp->mIsAppPath=isAppPath;
    kp->mUploadNode=uploadNode;
    kp->mFromPath=fromPath;
    kp->mToPath=toPath;
    kp->reqUploadFile();
    jsonUploadFile=kp->mJsonBuf;
    int ret=kp->mRet;
    delete kp;
    return ret;
}

//下载文件
//输入: consumerKey consumerSecret  oauthToken    oauthTokenSecret    、
//     isAppPath   fromPath toPath
//返回: http 状态
int Kpan::kpDownloadFile(const QString &consumerKey,const QString &consumerSecret,\
                                                  const QString &oauthToken,const QString &oauthTokenSecret,\
                                                  const bool &isAppPath,const QString &fromPath,
                                                  const QString &toPath
                                                  )
{
    KpSDK *kp=new KpSDK();
    kp->mConsumerKey=consumerKey;
    kp->mConsumerSecret=consumerSecret;
    kp->mAuTokenInfo.auToken=oauthToken;
    kp->mAuTokenInfo.auTokenSecret=oauthTokenSecret;
    kp->mIsAppPath=isAppPath;
    kp->mFromPath=fromPath;
    kp->mToPath=toPath;
    kp->reqDownLoadFile();

    int ret=kp->mRet;
    delete kp;
    return ret;
}


//分享文件
//输入: consumerKey consumerSecret  oauthToken    oauthTokenSecret    、
//     isAppPath   fromPath
//输出：jsonShareFile
//返回: http 状态
int Kpan::kpShareFile(QString &jsonShareFile, const QString &consumerKey,const QString &consumerSecret,\
                                                 const QString &oauthToken,const QString &oauthTokenSecret,\
                                                 const bool &isAppPath,const QString &fromPath
                                                 )
{
    KpSDK *kp=new KpSDK();
    kp->mConsumerKey=consumerKey;
    kp->mConsumerSecret=consumerSecret;
    kp->mAuTokenInfo.auToken=oauthToken;
    kp->mAuTokenInfo.auTokenSecret=oauthTokenSecret;
    kp->mIsAppPath=isAppPath;
    kp->mFromPath=fromPath;
    kp->reqShareFile();
    jsonShareFile=kp->mJsonBuf;

    int ret=kp->mRet;
    delete kp;
    return ret;
}
