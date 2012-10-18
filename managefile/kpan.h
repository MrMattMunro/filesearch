#pragma once

#ifndef KPAN_H
#define KPAN_H

#endif // KPAN_H

#include "windows.h"
#include "jni.h"
#include <string>
#include <iostream>
#include <QString>
#include <QList>
#include <QObject>
#include <QMap>
#include <db/docdao.h>

/*! \brief A model for extensions dipslay.
Extensions are stored as a files with full path in m_values.
\author Petr Vanek <petr@scribus.info>
*/
class Kpan : public QObject
{
        Q_OBJECT

        public:
               // Kpan(QObject * parent = 0);
                ~Kpan();
                int kpReqTmpToken(QString &tmpOauthToken,QString &tmpOauthTokenSecret,\
                                                                     QString &authoriseUrl,\
                                                                     const QString &consumerKey,const QString &consumerSecret);

                int kpAccessToken(QString &oauth_token, QString &oauth_token_secret,\
                                                                      QString &user_id,      QString &charged_dir,\
                                                                      const QString &consumerKey,const QString &consumerSecret,\
                                                                      const QString &tmpOauthToken,const QString &tmpOauthTokenSecret
                                                                      );

                int kpUsrInfo(QString &max_file_size, QString &user_name,\
                                                                  QString &quota_used,    QString &quota_total,\
                                                                  const QString &consumerKey,const QString &consumerSecret,\
                                                                  const QString &oauthToken,const QString &oauthTokenSecret
                                                                  );

                int kpMetaData(QString &jsonMetaData,\
                                                                  const QString &consumerKey,const QString &consumerSecret,\
                                                                  const QString &oauthToken,const QString &oauthTokenSecret,
                                                                  const bool   &isAppPath, const QString &dataPath
                                                                  );

                int kpCreateFolder(QString &jsonCreateFolder,\
                                                                    const QString &consumerKey,const QString &consumerSecret,\
                                                                    const QString &oauthToken,const QString &oauthTokenSecret,
                                                                    const bool   &isAppPath, const QString &floderPath
                                                                    );

                int kpDelFile(QString &jsonDelFile,\
                                                               const QString &consumerKey,const QString &consumerSecret,\
                                                               const QString &oauthToken,const QString &oauthTokenSecret,
                                                               const bool   &isAppPath, const QString &floderPath,
                                                               const bool   &to_recycle
                                                               );

                int kpMvFile(QString &jsonMvFile,\
                                                              const QString &consumerKey,const QString &consumerSecret,\
                                                              const QString &oauthToken,const QString &oauthTokenSecret,
                                                              const bool   &isAppPath, \
                                                              const QString &fromPath, const QString &toPath
                                                              );
                int kpCpFile(QString &jsonCpFile,\
                                                              const QString &consumerKey,const QString &consumerSecret,\
                                                              const QString &oauthToken,const QString &oauthTokenSecret,
                                                              const bool   &isAppPath, \
                                                              const QString &fromPath, const QString &toPath
                                                              );

                int kpUploadLocate(QString &uploadNode,\
                                                                       const QString &consumerKey,const QString &consumerSecret,\
                                                                       const QString &oauthToken,const QString &oauthTokenSecret
                                                                       );

                int kpUploadFile(QString &jsonUploadFile,
                                                                  const QString &consumerKey,const QString &consumerSecret,\
                                                                  const QString &oauthToken,const QString &oauthTokenSecret,\
                                                                  const bool &isOverWrite, const bool &isAppPath,\
                                                                  const QString &uploadNode, const QString &fromPath,
                                                                  const QString &toPath
                                                                  );

                int kpDownloadFile(const QString &consumerKey,const QString &consumerSecret,\
                                                                  const QString &oauthToken,const QString &oauthTokenSecret,\
                                                                  const bool &isAppPath,const QString &fromPath,
                                                                  const QString &toPath
                                                                  );

                int kpShareFile(QString &jsonShareFile, const QString &consumerKey,const QString &consumerSecret,\
                                                                 const QString &oauthToken,const QString &oauthTokenSecret,\
                                                                 const bool &isAppPath,const QString &fromPath
                                                                 );
        private:

};

