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
        QChar  DT_MODIFIED;
        int MF_VERSION;     
}Dir;

class DirDao
{
            Q_DECLARE_TR_FUNCTIONS(DirDao)
        public:
                // ²åÈëÄ¿Â¼
                static bool insertDir(Dir Dir);
                static bool updateDir(Dir Dir);
                static bool deleteDir(QString DirUuId);
                static Dir selectDir(const QString & uuid);
                static QList<Dir> selectDirsbyParent(const QString & parentUuid);

        private:
                static void exception(const QString & message);
};

#endif
