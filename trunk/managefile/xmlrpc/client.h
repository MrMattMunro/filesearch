#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QVariant>

typedef struct struAuToken
{
    QString token;
    QString userGuid;
    QString dbGuid;
}struAuToken;

class Client : public QObject
{
      Q_OBJECT
public:
      QVariant revalue;
      QVariantMap userMap;
      Client( const QString &address, quint16 port, QObject *parent = 0 );
      ~Client();

      void createAccount(const QString &user_guid, const QString &user_id, const QString &user_email, const QString &password);
      void clientLogin(const QString &accountUserId,const QString &password);
      void clientLogout(const QString &accountUserId,const QString &password);
      void getAllDir();
      void getAllTag();
      void getSimpleList();
      void getSimpleListByDir();
      void getSimpleListByTag();
      void upload();
      void download();
      void postDocSimpleData();
      void postNoteList();
      void postTagList();
      void getVersion();
      void changePwd(const QString &oldPwd,const QString &newPwd);

      void addCommonParam(QVariantMap &param);
      bool isSuccess();
signals:
      void clientLoginDataReady();
      void createAccountDataReady();
      void getVersionDataReady();
      void postTagListDataReady();
      void postNoteListDataReady();
      void postDocSimpleDataReady();
      void uploadDataReady();
      void downloadDataReady();
      void getSimpleListByTagDataReady();
      void getSimpleListByDirDataReady();
      void getSimpleListDataReady();
      void getAllTagDataReady();
      void getAllDirDataReady();
      void clientLogoutDataReady();
      void changePwdDataReady();

private slots:

      void onClientLoginDataReady( const QVariant &response );
      void onCreateAccountDataReady( const QVariant &response );
      void onGetVersionDataReady( const QVariant &response );
      void onPostTagListDataReady( const QVariant &response );
      void onPostNoteListDataReady( const QVariant &response );
      void onPostDocSimpleDataReady( const QVariant &response );
      void onUploadDataReady( const QVariant &response );
      void onDownloadDataReady( const QVariant &response );
      void onGetSimpleListByTagDataReady( const QVariant &response );
      void onGetSimpleListByDirDataReady( const QVariant &response );
      void onGetSimpleListDataReady( const QVariant &response );
      void onGetAllTagDataReady( const QVariant &response );
      void onGetAllDirDataReady( const QVariant &response );
      void onClientLogoutDataReady( const QVariant &response );
      void onChangePwdDataReady( const QVariant &response );
private:
      QString address;
      quint16 port;
      struAuToken autoken;


};

#endif // CLIENT_H
