#ifndef DIRDAO_H
#define DIRDAO_H

#include <QCoreApplication>
#include <QList>

typedef struct
{
        QString DIR_GUID;
        QString DIR_PARENT_UUID;
        QString DIR_NAME;
        QString DIR_DESCRIPTION;
        QString DIR_ICON;
        int DIR_ORDER;
        QString  DT_MODIFIED;
        int MF_VERSION;
        QString DELETE_FLAG;
}Dir;



class DirDao
{
            Q_DECLARE_TR_FUNCTIONS(DirDao)
            //static QList<Dir> selDirList;
        public:

                // 插入目录
                static bool insertDir(Dir Dir);
                static bool updateDir(Dir Dir);
                static bool deleteDir(QString dirUuId);
                // 升级文件夹为根文件夹
                static bool updateToRootDir(QString dirUuId);
                // 恢复文件夹
                bool restoreDir(QString dirUuId);
                static Dir selectDir(const QString & uuid);
                static QList<Dir> selectDirsbyParent(QString groupUuid,  QString delFlg);
                // 递归迭代父目录取得所有层级子目录
                static void selectAllSubDirbyDir(QList<Dir> & subDirList, QString dirUuid, QString delFlg);
                // 递归迭代目录取得所有层级父目录
                static void selectAllParentDirbyDir(QList<Dir> & parentDirList,  QString dirUuid);
                // 物理删除文件夹
                static bool  physicalDelDir();

                //static void clearSelDirList();
                //static QList<Dir> getSelDirList();

        private:
                static void exception(const QString & message);
};

#endif
