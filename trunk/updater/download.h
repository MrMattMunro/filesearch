/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/

#ifndef DOWNLOAD_H
#define DOWNLOAD_H
#endif

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>


//用于下载文件（或文件的一部分）
class Download : public QObject
{
    Q_OBJECT
private:
    QNetworkAccessManager m_Qnam;
    QNetworkReply *m_Reply;
    QFile *m_File;

    const int m_Index;
    qint64 m_HaveDoneBytes;
    qint64 m_StartPoint;
    qint64 m_EndPoint;

public:
    Download(int index, QObject *parent = 0);
    void StartDownload(const QUrl &url, QFile *file,
    qint64 startPoint=0, qint64 endPoint=-1);
signals:
    void DownloadFinished();
    public slots:
        void HttpReadyRead();
        void FinishedSlot();
};
