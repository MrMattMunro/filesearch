#ifndef TABLERESULT_H
#define TABLERESULT_H

#include <QString>
#include <QMetaType>


//QString DOC_UUID;
//QString KEY_WORD;
//QString FILE_TYPE;
//QString FILE_PATH;
//QString FILE_NAME;
//QString DESP;
//QString CONTENT;
//QString SHEET_NAME;
//int ROW_NB;
//int PAGE;
//QString DT_CREATED;

class TableResult
{
public:
    explicit TableResult();
    TableResult(const QString &docuuid, const QString &keyword,
           const QString &filetype, const QString &filepath, const QString &filename,
           const QString &desp, const QString &content, const QString &sheetname, const int rownb, const int page,
           const QString &dtcreated);
    virtual ~TableResult() { ; }

    void setDocuuid(const QString &docuuid);
    QString docuuid() const;

    void setKeyword(const QString &keyword);
    QString keyword() const;

    void setFiletype(const QString &filetype);
    QString filetype() const;

    void setFilepath(const QString &filepath);
    QString filepath() const;

    void setFilename(const QString &filename);
    QString filename() const;

    void setDesp(const QString &desp);
    QString desp() const;

    void setContent(const QString &content);
    QString content() const;

    void setSheetname(const QString &sheetname);
    QString sheetname() const;

    void setRownb(const int rownb);
    int rownb() const;

    void setPage(const int &page);
    int page() const;

    void setDtcreatede(const QString &dtcreated);
    QString dtcreated() const;

private:
    long _id;

    QString _docuuid;
    QString _keyword;
    QString _filetype;
    QString _filepath;
    QString _filename;
    QString _desp;
    QString _content;
    QString _sheetname;
    int _rownb;
    int _page;
    QString _dtcreated;

};

Q_DECLARE_METATYPE(TableResult);

#endif // TABLERESULT_H
