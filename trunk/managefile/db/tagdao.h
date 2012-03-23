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
                static bool insertTag(const Tag & tag);
                static bool updateTag(Tag tag);
                static QList<Tag> selectTagsbyGroup(const QString & groupUuid);

        private:
                static void exception(const QString & message);
};

#endif
