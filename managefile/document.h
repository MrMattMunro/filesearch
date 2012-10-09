#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QString>
#include <QMetaType>


//QString DOCUMENT_GUID;
//QString DOCUMENT_TITLE;
//QString DIR_GUID;
//QString DOCUMENT_LOCATION;
//QString DOCUMENT_NAME;
//QString DOCUMENT_SEO;
//QString DOCUMENT_URL;
//QString DOCUMENT_AUTHOR;
//QString DOCUMENT_KEYWORDS;
//QString DOCUMENT_TYPE;
//QString DOCUMENT_OWNER;
//QString DT_CREATED;
//QString DT_MODIFIED;
//QString DT_ACCESSED;
//int DOCUMENT_ICON_INDEX;
//int DOCUMENT_SYNC;
//QString DOCUMENT_PROTECT;
//QString DOCUMENT_ENCODE;
//int DOCUMENT_READ_COUNT;
//int DOCUMENT_RELATE_COUNT;
//QString DOCUMENT_INDEXFLG;
//QString DOCUMENT_OPERFLG;
//QString DELETE_FLAG;
//int MF_VERSION;

class Document
{
public:
    explicit Document();
    Document(const QString &docuuid, const QString &doctitle,
           const QString &diruuid, const QString &docloc, const QString &docname,
           const QString &docseo, const QString &docurl, const QString &docauthor,
           const QString &dockeyword, const QString &doctype,const QString &docowner,
           const QString &dtcreated,  const QString &dtmodified, const QString &dtaccessed,
           const int &dociconindex, const int docsync,  const QString &docprotect,
           const QString &docencode, const int readcount,const int relatecount, const QString &indexflg,
           const QString &openflg,const QString &delflg, const int version);
    virtual ~Document() { ; }

    void setDocuuid(const QString &docuuid);
    QString docUuid() const;

    void setDocTitle(const QString &title);
    QString docTitle() const;

    void setDirUuid(const QString &diruuid);
    QString dirUuid() const;

    void setDocLoc(const QString &docloc);
    QString docLoc() const;

    void setDocName(const QString &docname);
    QString docName() const;

    void setDocSeo(const QString &docseo);
    QString docSeo() const;

    void setDocUrl(const QString &docurl);
    QString docUrl() const;

    void setDocAuthor(const QString &docauthor);
    QString docAuthor() const;

    void setDocKeyWord(const QString &dockeyword);
    QString docKeyWord() const;

    void setDocType(const QString &doctype);
    QString docType() const;

    void setDocOwner(const QString &docowner);
    QString docOwner() const;

    void setDtCreated(const QString &dtcreated);
    QString dtCreated() const;

    void setDtModified(const QString &dtmodified);
    QString dtModified() const;

    void setDtAccessed(const QString &dtaccessed);
    QString dtAccessed() const;

    void setDocIconIndex(const int &dociconindex);
    int docIconIndex() const;

    void setDocSync(const int docsync);
    int docSync() const;

    void setDocProtect(const QString &docprotect);
    QString docProtect() const;

    void setDocEncode(const QString &docencode);
    QString docEncode() const;

    void setReadCount(const int readcount);
    int readcount() const;

    void setRelateCount(const int relatecount);
    int relateCount() const;

    void setIndexFlg(const QString &indexflg);
    QString indexFlg() const;

    void setOpenFlg(const QString &docencode);
    QString openflg() const;

    void setDelFlg(const QString &delflg);
    QString delFlg() const;

    void setVersion(const int version);
    int version() const;

private:
    long _id;

    QString _docuuid;
    QString _doctitle;
    QString _diruuid;
    QString _docloc;
    QString _docname;
    QString _docseo;
    QString _docurl;
    QString _docauthor;
    QString _dockeyword;
    QString _doctype;
    QString _docowner;
    QString _dtcreated;
    QString _dtmodified;
    QString _dtaccessed;
    int _dociconindex;
    int _docsync;
    QString _docprotect;
    QString _docencode;
    int _readcount;
    int _relatecount;
    QString _indexflg;
    QString _openflg;
    QString _delflg;
    int _version;

};

Q_DECLARE_METATYPE(Document);

#endif // DOCUMENT_H
