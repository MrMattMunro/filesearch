#ifndef SENDMAIL_H
#define SENDMAIL_H

#endif // SENDMAIL_H

#include <QString>
#include <QObject>
#include <jvm.h>

class SendMailObj:public QObject {
    Q_OBJECT
    public:
        SendMailObj(){}
        QList<QString> toaddrs;
        QString title;
        QString content;
        QList<QString> m_failList;
        QList<QString> m_successList;

    public slots:
       void sendMail()
       {
          Jvm jvm;
          QMap<QString, QString> map;
          map.insert("title",title);
          map.insert("content",content);
          QString email;
          foreach(email, toaddrs){
              map.insert("toaddr", email);
              bool rtn = jvm.invokeMethod("com/util/mail/SendMail", "sendMail", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z", map);
              if(rtn){
                  m_successList.append(email);
              }else{
                  m_failList.append(email);
              }
          }
          emit finished();
       }
    signals:
        void finished();
        void failed();
};
class SendMailSign:public QObject {
    Q_OBJECT
    public:
        SendMailSign(QObject* parent=0):QObject(parent){
        }
   public slots:
        void emitsig()   {
           emit sig();
        }
   signals:
       void sig();
};
