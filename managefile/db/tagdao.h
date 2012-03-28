#ifndef TAGDAO_H
#define TAGDAO_H

#include <QCoreApplication>
#include <QList>

typedef struct
{
        QString TAG_GUID;
        QString TAG_GROUP_GUID;
        QString TAG_NAME;
        QString TAG_DESCRIPTION;
        QChar  DT_MODIFIED;
        int MF_VERSION;
}Tag;

class TagDao
{
            Q_DECLARE_TR_FUNCTIONS(TagDao)
        public:
                // ≤Â»Î±Í«©
                static bool insertTag(Tag tag);
                static bool updateTag(Tag tag);
                static bool deleteTag(QString tagUuId);
                static Tag selectTag(const QString & uuid);
                static QList<Tag> selectTagsbyParent(const QString & groupUuid);

        private:
                static void exception(const QString & message);
};

#endif
