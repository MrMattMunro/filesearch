#ifndef DOCDAO_H
#define DOCDAO_H

#include <QCoreApplication>
#include <QList>

typedef struct
{
        QString DOCUMENT_GUID;
        QString DOCUMENT_TITLE;
        QString DIR_GUID;
        QString DOCUMENT_LOCATION;
        QString DOCUMENT_NAME;
        QString DOCUMENT_SEO;
        QString DOCUMENT_URL;
        QString DOCUMENT_AUTHOR;
        QString DOCUMENT_KEYWORDS;
        QString DOCUMENT_TYPE;
        QString DOCUMENT_OWNER;
        QChar DT_CREATED;
        QChar DT_MODIFIED;
        QChar DT_ACCESSED;
        int DOCUMENT_ICON_INDEX;
        int DOCUMENT_SYNC;
        QString DOCUMENT_PROTECT;
        QChar DOCUMENT_ENCODE;
        int DOCUMENT_READ_COUNT;
        int DOCUMENT_RELATE_COUNT;
        QChar DOCUMENT_INDEXFLG;
        QChar DOCUMENT_OPERFLG;
        QChar DELETE_FLAG;
        int MF_VERSION;
}Doc;

class DocDao
{
            Q_DECLARE_TR_FUNCTIONS(DocDao)
        public:
                // ≤Â»Î±Í«©
                static bool insertDoc(Doc doc);
                static bool updateDoc(Doc doc);
                static bool deleteDoc(QString docUuId);
                static Doc selectDoc(const QString & docUuId);
                static QList<Doc> selectDocsbyDir(const QString & dirUuid);

        private:
                static void exception(const QString & message);
};

#endif
