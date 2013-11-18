#include "client.h"
#include "xmlrpcclient.h"
#include "utils.h"
#include "preferences.h"

#include <QVariantList>

//#define ApiMethodName_ClientLogin "accounts.clientLogin";
//#define ApiMethodName_ClientLogout  "accounts.clientLogout";
//#define ApiMethodName_CreateAccount  "accounts.createAccount";
//#define ApiMethodName_GetAllCategories  "category.getAll";
//#define ApiMethodName_GetAllTags "tag.getAll";
//#define ApiMethodName_DownloadDocumentList  "document.getSimpleList";
//#define ApiMethodName_DocumentsByCategory  "document.getSimpleListByCategory";
//#define ApiMethodName_DocumentsByTag  "document.getSimpleListByTag";


//#define ApiMethodName_DownloadData "data.download";
//#define ApiMethodName_UploadData "data.upload";


//#define ApiMethodName_DownloadDeletedList "deleted.getList";
//#define ApiMethodName_DocumentsByKey "document.getSimpleListByKey";
//#define ApiMethodName_UploadDeletedList "deleted.postList";

//#define ApiMethodName_UploadDocumentInfo "document.postSimpleData";
//#define ApiMethodName_UploadTags "tag.postList";
//#define ApiMethodName_GetVersion "wiz.getVersion";

//#define ApiMethodName_UploadTags "note.postList";
//#define ApiMethodName_UploadTags "tag.postList";

Client::Client( const QString &address, quint16 port, QObject *parent )
            : QObject( parent ), address( address ), port( port )
{
}

Client::~Client() {}

//user_guid, user_id, user_email, upassword

// 创建账号
void  Client::createAccount(const QString &user_guid, const QString &user_id, const QString &user_email, const QString &password){
    QVariantMap m;
    addCommonParam(m);
    m["user_guid"] = user_guid;
    m["user_id"] = user_id;
    m["user_email"] = user_email;
    m["password"] = password;

    m["product_name"] = "win";
    m["display_name"] = "";
    m["invite_code"] = "";

    QString os = Utils::getSysOs();
    QString lang = Utils::getSysLang();
    m["os"] = os;
    m["lang"] = lang;

    XmlRpcClient *client = new XmlRpcClient( address, port );
    connect( client, SIGNAL( dataReady(QVariant) ), this, SLOT( onCreateAccountDataReady(QVariant) ) );
    client->execute("accounts.createAccount", QVariantList() << QVariant( m )  );
}
// 登陆并获取Token
void  Client::clientLogin(const QString &accountUserId,const QString &password){
    QVariantMap m;
    addCommonParam(m);
    m["user_id"] = accountUserId;
    m["password"] = password;

    XmlRpcClient *client = new XmlRpcClient( address, port );
    connect( client, SIGNAL( dataReady(QVariant) ), this, SLOT( onClientLoginDataReady(QVariant) ) );
    client->execute("accounts.clientLogin", QVariantList() << QVariant( m ) );
}
// 退出系统
void  Client::clientLogout(const QString &accountUserId,const QString &token){
    QVariantMap m;
    addCommonParam(m);
    m["user_id"] = accountUserId;
    m["token"] = token;

    XmlRpcClient *client = new XmlRpcClient( address, port );
    connect( client, SIGNAL( dataReady(QVariant) ), this, SLOT( onClientLogoutDataReady(QVariant) ) );
    client->execute("accounts.clientLogout", QVariantList() << QVariant( m ) );
}
// 改变密码
void Client::changePwd(const QString &oldPwd,const QString &newPwd){
    QVariantMap m;
    addCommonParam(m);
    // 以邮件作为Uer_id
    Preferences* p = Preferences::instance();
    m["user_id"] = p->getUserEmail();

    m["old_password"] = oldPwd;
    m["new_password"] = newPwd;

    XmlRpcClient *client = new XmlRpcClient( address, port );
    connect( client, SIGNAL( dataReady(QVariant) ), this, SLOT( onChangePwdDataReady(QVariant) ) );
    client->execute("accounts.changePassword", QVariantList() << QVariant( m ) );
}

// 取出所有文件夹
void  Client::getAllDir(){
    QVariantMap m;
    addCommonParam(m);

    XmlRpcClient *client = new XmlRpcClient( address, port );
    connect( client, SIGNAL( dataReady(QVariant) ), this, SLOT( onGetAllDirDataReady(QVariant) ) );
    client->execute("dir.getAll", QVariantList() << QVariant( m ) );
}

// 取出所有标签
void  Client::getAllTag(){
    QVariantMap m;
    addCommonParam(m);

    XmlRpcClient *client = new XmlRpcClient( address, port );
    connect( client, SIGNAL( dataReady(QVariant) ), this, SLOT( onGetAllTagDataReady(QVariant) ) );
    client->execute("tag.getAll", QVariantList() << QVariant( m ) );
}

// 取出所有简单的文档
void  Client::getSimpleList(){
    QVariantMap m;
    addCommonParam(m);

    XmlRpcClient *client = new XmlRpcClient( address, port );
    connect( client, SIGNAL( dataReady(QVariant) ), this, SLOT( onGetSimpleListDataReady(QVariant) ) );
    client->execute("document.getSimpleList", QVariantList() << QVariant( m ) );
}
// 取出目录下所有的文档
void  Client::getSimpleListByDir(){
    QVariantMap m;
    addCommonParam(m);

    XmlRpcClient *client = new XmlRpcClient( address, port );
    connect( client, SIGNAL( dataReady(QVariant) ), this, SLOT( onGetSimpleListByDirDataReady(QVariant) ) );
    client->execute("document.getSimpleListByDir", QVariantList() << QVariant( m ) );
}
// 取出标签下所有的文档
void  Client::getSimpleListByTag(){
    QVariantMap m;
    addCommonParam(m);

    XmlRpcClient *client = new XmlRpcClient( address, port );
    connect( client, SIGNAL( dataReady(QVariant) ), this, SLOT( onGetSimpleListByTagDataReady(QVariant) ) );
    client->execute("document.getSimpleListByTag", QVariantList() << QVariant( m ) );
}
// 下载
void  Client::download(){
    QVariantMap m;
    addCommonParam(m);

    XmlRpcClient *client = new XmlRpcClient( address, port );
    connect( client, SIGNAL( dataReady(QVariant) ), this, SLOT( onDownloadDataReady(QVariant) ) );
    client->execute("data.download", QVariantList() << QVariant( m ) );
}
// 上传
void  Client::upload(){
    QVariantMap m;
    addCommonParam(m);

    XmlRpcClient *client = new XmlRpcClient( address, port );
    connect( client, SIGNAL( dataReady(QVariant) ), this, SLOT( onUploadDataReady(QVariant) ) );
    client->execute("data.upload", QVariantList() << QVariant( m ) );
}

//#define ApiMethodName_UploadDocumentInfo "document.postSimpleData";
//#define ApiMethodName_UploadTags "tag.postList";
//#define ApiMethodName_GetVersion "wiz.getVersion";

//#define ApiMethodName_UploadTags "note.postList";
//#define ApiMethodName_UploadTags "tag.postList";
// 提交更新文档相关信息
void  Client::postDocSimpleData(){
    QVariantMap m;
    addCommonParam(m);

    XmlRpcClient *client = new XmlRpcClient( address, port );
    connect( client, SIGNAL( dataReady(QVariant) ), this, SLOT( onPostDocSimpleDataReady(QVariant) ) );
    client->execute("document.postSimpleData", QVariantList() << QVariant( m ) );
}
// 提交更新文档笔记相关信息
void  Client::postNoteList(){
    QVariantMap m;
    addCommonParam(m);

    XmlRpcClient *client = new XmlRpcClient( address, port );
    connect( client, SIGNAL( dataReady(QVariant) ), this, SLOT( onPostNoteListDataReady(QVariant) ) );
    client->execute("note.postList", QVariantList() << QVariant( m ) );
}
// 提交更新标签相关信息
void  Client::postTagList(){
    QVariantMap m;
    addCommonParam(m);

    XmlRpcClient *client = new XmlRpcClient( address, port );
    connect( client, SIGNAL( dataReady(QVariant) ), this, SLOT( onPostTagListDataReady(QVariant) ) );
    client->execute("tag.postList", QVariantList() << QVariant( m ) );
}

// 提交更新标签相关信息
void  Client::getVersion(){
    QVariantMap m;
    addCommonParam(m);

    XmlRpcClient *client = new XmlRpcClient( address, port );
    connect( client, SIGNAL( dataReady(QVariant) ), this, SLOT( onGetVersionDataReady(QVariant) ) );
    client->execute("mf.getVersion", QVariantList() << QVariant( m ) );
}

// ------------------------共同函数-----------------------------------//
// 加入共同参数
void Client::addCommonParam(QVariantMap &param){
    param["client_type"] = "win";
    param["program_type"] = "normal";
    param["api_version"] = "1";

    if (!autoken.token.isEmpty()) {
        param["token"] = autoken.token;
    }
    if (!autoken.dbGuid.isEmpty()) {
        param["db_guid"] = autoken.dbGuid;
    }
    if (!autoken.userGuid.isEmpty()) {
        param["user_guid"] = autoken.userGuid;
    }
}
// 是否返回正常
bool Client::isSuccess()
{
    QVariantMap map = revalue.value<QVariantMap>();
    QString returnCode = map["return_code"].value<QString>();
    return returnCode == "200";
}

// ------------------------返回函数-----------------------------------//
// 登陆 如果成功则设置Token
void Client::onClientLoginDataReady( const QVariant &response )
{
    qDebug() << "onClientLoginDataReady";
    qDebug() << response;
    revalue = response;

    QVariantMap map = revalue.value<QVariantMap>();
    qDebug() << map["api_version"];
    qDebug() << map["db_guid"];
    qDebug() << map["token"];
    autoken.token = map["token"].value<QString>();
    autoken.dbGuid = map["db_guid"].value<QString>();

    // 取得用户信息
    userMap = map["user"].value<QVariantMap>();
    QString userGuid = userMap["user_guid"].value<QString>();
    autoken.userGuid = userGuid;

    // 发出数据已经准备好信息
    emit clientLoginDataReady();
}
// 创建账号
void Client::onCreateAccountDataReady( const QVariant &response )
{
    qDebug() << "onCreateAccountDataReady";
    qDebug() << response;
    revalue = response;

    // 发出数据已经准备好信息
    emit createAccountDataReady();
}
// 改变密码
void Client::onChangePwdDataReady( const QVariant &response )
{
    qDebug() << "onChangePwdDataReady";
    qDebug() << response;
    revalue = response;

    // 发出数据已经准备好信息
    emit changePwdDataReady();
}
// 取得版本
void Client::onGetVersionDataReady( const QVariant &response ){
    qDebug() << "onGetVersionDataReady";
    qDebug() << response;
    revalue = response;

    // 发出数据已经准备好信息
    emit getVersionDataReady();
}
// 提交标签信息
void Client::onPostTagListDataReady( const QVariant &response ){
    qDebug() << "onPostTagListDataReady";
    qDebug() << response;
    revalue = response;

    // 发出数据已经准备好信息
    emit postTagListDataReady();
}
// 提交笔记信息
void Client::onPostNoteListDataReady( const QVariant &response ){
    qDebug() << "onPostNoteListDataReady";
    qDebug() << response;
    revalue = response;

    // 发出数据已经准备好信息
    emit postNoteListDataReady();
}
// 提交 更新文档的信息
void Client::onPostDocSimpleDataReady( const QVariant &response ){
    qDebug() << "onPostDocSimpleDataReady";
    qDebug() << response;
    revalue = response;

    // 发出数据已经准备好信息
    emit postDocSimpleDataReady();
}
// 上传
void Client::onUploadDataReady( const QVariant &response ){
    qDebug() << "onUploadDataReady";
    qDebug() << response;
    revalue = response;

    // 发出数据已经准备好信息
    emit uploadDataReady();
}
// 下载
void Client::onDownloadDataReady( const QVariant &response ){
    qDebug() << "onDownloadDataReady";
    qDebug() << response;
    revalue = response;

    // 发出数据已经准备好信息
    emit downloadDataReady();
}
// 取得标签下文档列表
void Client::onGetSimpleListByTagDataReady( const QVariant &response ){
    qDebug() << "onGetSimpleListByTagDataReady";
    qDebug() << response;
    revalue = response;

    // 发出数据已经准备好信息
    emit getSimpleListByTagDataReady();
}
// 取得文件夹下文档列表
void Client::onGetSimpleListByDirDataReady( const QVariant &response ){
    qDebug() << "onGetSimpleListByDirDataReady";
    qDebug() << response;
    revalue = response;

    // 发出数据已经准备好信息
    emit getSimpleListByDirDataReady();
}
// 取得文档列表
void Client::onGetSimpleListDataReady( const QVariant &response ){
    qDebug() << "onGetSimpleListDataReady";
    qDebug() << response;
    revalue = response;

    // 发出数据已经准备好信息
    emit getSimpleListDataReady();
}
// 取得所有标签
void Client::onGetAllTagDataReady( const QVariant &response ){
    qDebug() << "onGetAllTagDataReady";
    qDebug() << response;
    revalue = response;

    // 发出数据已经准备好信息
    emit getAllTagDataReady();
}
// 取得所有文件夹
void Client::onGetAllDirDataReady( const QVariant &response ){
    qDebug() << "onGetAllDirDataReady";
    qDebug() << response;
    revalue = response;

    // 发出数据已经准备好信息
    emit getAllDirDataReady();
}
// 退出系统
void Client::onClientLogoutDataReady( const QVariant &response ){
    qDebug() << "onClientLogoutDataReady";
    qDebug() << response;
    revalue = response;

    // 发出数据已经准备好信息
    emit clientLogoutDataReady();
}
