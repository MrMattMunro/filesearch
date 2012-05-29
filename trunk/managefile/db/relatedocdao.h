#ifndef RelateDocDAO_H
#define RelateDocDAO_H

#include <QCoreApplication>
#include <QList>

typedef struct
{
        QString DOCUMENT_GUID;
        QString RELATED_DOCUMENT_GUID;
}RelateDoc;


class RelateDocDao
{
            Q_DECLARE_TR_FUNCTIONS(RelateDocDao)
        public:
                // 插入关联文档关系
                static bool insertRelateDoc(RelateDoc reldoc);
                static bool deleteRelateDoc(RelateDoc reldoc);
                static QList<RelateDoc> selectRelateDocs(const QString & docUuid);
                static QList<RelateDoc> selectRelatedDocsByRel(const QString & relDocUuid);
                // 删除某个文档的所有关联
                static bool deleteRelateDocByDocUuId(const QString & docUuid);

        private:
                static void exception(const QString & message);
};

#endif
