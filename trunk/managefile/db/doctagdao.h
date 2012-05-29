#ifndef DocTagDAO_H
#define DocTagDAO_H

#include <QCoreApplication>
#include <QList>
#include <db/tagdao.h>

typedef struct
{
        QString DOCUMENT_GUID;
        QString TAG_GUID;

}DocTag;

class DocTagDao
{
            Q_DECLARE_TR_FUNCTIONS(DocTagDao)
        public:
                static bool insertDocTag(DocTag docTag);
                static bool deleteDocTag(DocTag docTag);
                static bool deleteDocTagByDoc(QString docUuId);
                // ÓÃTagUuId É¾³ýÎÄµµ±êÇ©
                static bool deleteDocTagByTag(QString taguid);
                static QList<Tag> selectTagsbyDocUuId(const QString & docUuid);

        private:
                static void exception(const QString & message);
};

#endif
