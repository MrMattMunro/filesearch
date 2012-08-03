/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/

#ifndef UPDATEDIALOG_H
#define UPDATEDIALOG_H
#endif

#include "ui_updatedialog.h"

#include <QStandardItemModel>
#include <QFileInfo>

/*! \brief Import data into table using various importer types.
\note XML import requires Qt library at least in the 4.3.0 version.
\author Petr Vanek <petr@scribus.info>
*/
//用于管理文件的下载
class DownloadControl : public QObject
{
    Q_OBJECT
    private:
        int m_DownloadCount;
        int m_FinishedNum;
        int m_FileSize;
        QUrl m_Url;
        QFile *m_File;
        QFileInfo *m_locfileinfo;
    public:
        DownloadControl(QObject *parent = 0,  QFileInfo *m_locfileinfo = 0);
        void StartFileDownload(const QString &url, int count);
        qint64 GetFileSize(QUrl url);
    signals:
        void FileDownloadFinished();
    private slots:
        void SubPartFinished();
        // 用户判断网络下载是否有问题

};
