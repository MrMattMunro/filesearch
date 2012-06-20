#include <QFileDialog>
#include <QMessageBox>

#include <QtDebug>
#include "downloadcontrol.h"
#include "download.h"

//用阻塞的方式获取下载文件的长度
qint64 DownloadControl::GetFileSize(QUrl url)
{
    QNetworkAccessManager manager;
    qDebug() << "Getting the file size...";
    QEventLoop loop;
    //发出请求，获取目标地址的头部信息
    QNetworkReply *reply = manager.head(QNetworkRequest(url));
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()), Qt::DirectConnection);
    loop.exec();
    QVariant var = reply->header(QNetworkRequest::ContentLengthHeader);
    delete reply;
    qint64 size = var.toLongLong();
    qDebug() << "The file size is: " << size;
    return size;
}

DownloadControl::DownloadControl(QObject *parent)
: QObject(parent)
{
    m_DownloadCount = 0;
    m_FinishedNum = 0;
    m_FileSize = 0;
    m_File = new QFile;
}

void DownloadControl::StartFileDownload(const QString &url, int count)
{
    m_DownloadCount = count;
    m_FinishedNum = 0;
    m_Url = QUrl(url);
    m_FileSize = GetFileSize(m_Url);
    //先获得文件的名字
    QFileInfo fileInfo(m_Url.path());
    QString fileName = fileInfo.fileName();
    if (fileName.isEmpty())
        fileName = "index.html";

    m_File->setFileName(fileName);
    //打开文件
    m_File->open(QIODevice::WriteOnly);
    Download *tempDownload;

    //将文件分成PointCount段，用异步的方式下载
    qDebug() << "Start download file from " << url;
    for(int i=0; i < m_DownloadCount; i++)
    {
        //先算出每段的开头和结尾（HTTP协议所需要的信息）
        int start = m_FileSize * i / m_DownloadCount;
        int end = m_FileSize * (i+1) / m_DownloadCount;
        if( i != 0 )
            start--;

        //分段下载该文件
        tempDownload = new Download(i+1, this);
        connect(tempDownload, SIGNAL(DownloadFinished()),
            this, SLOT(SubPartFinished()));
        connect(tempDownload, SIGNAL(DownloadFinished()),
            tempDownload, SLOT(deleteLater()));
        tempDownload->StartDownload(m_Url, m_File, start, end);
    }
}

void DownloadControl::SubPartFinished()
{
    m_FinishedNum++;
    //如果完成数等于文件段数，则说明文件下载完毕，关闭文件，发生信号
    if( m_FinishedNum == m_DownloadCount )
    {
        m_File->close();
        emit FileDownloadFinished();
        qDebug() << "Download finished";
    }
}
