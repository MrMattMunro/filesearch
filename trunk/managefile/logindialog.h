/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/

#ifndef IMPORTTABLEDIALOG_H
#define IMPORTTABLEDIALOG_H
#endif

#include "ui_logindialog.h"

#include <QStandardItemModel>
#include <QHttp>
#include <QFile>
#include <QNetworkReply>
#include <QNetworkAccessManager>

/*! \brief Import data into table using various importer types.
\note XML import requires Qt library at least in the 4.3.0 version.
\author Petr Vanek <petr@scribus.info>
*/
class LoginDialog : public QDialog, public Ui::LoginDialog
{
	Q_OBJECT

	public:
                LoginDialog(QWidget * parent = 0);
                bool update;

                QNetworkAccessManager *manager;
                QHttp *http;
                QNetworkReply *reply;
                QUrl url;     //存储网络地址
                QFile* file;  //文件指针
                QFile* pic;
                QString fileName;

        private:
                void startRequest(QUrl url);
	private slots:
                void loginBtn_clicked();
                void registerBtn_clicked();
                void resetBtn_clicked();
                void httpFinished();  //完成下载后的处理
                void httpReadyRead();  //接收到数据时的处理

        signals:
                //确定按钮点击
                void  comfirmBtnClk();


};
