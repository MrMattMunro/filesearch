#include "document.h"

Document::Document()
{

}
Document::Document(const QString &docuuid, const QString &doctitle,
         const QString &diruuid, const QString &docloc, const QString &docname,
         const QString &docseo, const QString &docurl, const QString &docauthor,
         const QString &dockeyword, const QString &doctype,const QString &docowner,
         const QString &dtcreated, const QString &dtaccessed,  const int &dociconindex,
         const int docsync,  const QString &docprotect,  const QString &docencode, const int readcount,
         const int relatecount, const QString &indexflg,const QString &openflg,const QString &delflg,
         const int version) :
        _docuuid(docuuid), _doctitle(doctitle),_diruuid(diruuid),_docloc(docloc), _docname(docname),
        _docseo(docseo),_docurl(docurl),_docauthor(docauthor),_dockeyword(dockeyword), _doctype(doctype),
        _docowner(docowner), _dtcreated(dtcreated),_dtaccessed(dtaccessed),_dociconindex(dociconindex),
        _docsync(docsync), _docprotect(docprotect),_docencode(docencode),_readcount(readcount),
        _relatecount(relatecount), _indexflg(indexflg), _openflg(openflg), _delflg(delflg),
        _version(version)
{

}

void Document::setDocuuid(const QString &docuuid){
    _docuuid = docuuid;
}
QString Document::docUuid() const{
    return _docuuid;
}

void Document::setDocTitle(const QString &title){
   _doctitle = title;
}
QString Document::docTitle() const{
   return _doctitle;
}

void Document::setDirUuid(const QString &diruuid){
   _diruuid = diruuid;
}
QString Document::dirUuid() const{
   return _diruuid;
}

void Document::setDocLoc(const QString &docloc){
   _docloc = docloc;
}
QString Document::docLoc() const{
   return _docloc;
}

void Document::setDocName(const QString &docname){
    _docname = docname;
}
QString Document::docName() const{
    return _docname;
}

void Document::setDocSeo(const QString &docseo){
    _docseo = docseo;
}
QString Document::docSeo() const{
    return _docseo;
}

void Document::setDocUrl(const QString &docurl){
    _docurl = docurl;
}
QString Document::docUrl() const{
    return _docurl;
}

void Document::setDocAuthor(const QString &docauthor){
    _docauthor = docauthor;
}
QString Document::docAuthor() const{
    return _docauthor;
}

void Document::setDocKeyWord(const QString &dockeyword){
    _dockeyword = dockeyword;
}
QString Document::docKeyWord() const{
    return _dockeyword;
}

void Document::setDocType(const QString &doctype){
    _doctype = doctype;
}
QString Document::docType() const{
    return _doctype;
}

void Document::setDocOwner(const QString &docowner){
     _docowner = docowner;
}
QString Document::docOwner() const{
     return _docowner;
}

void Document::setDtCreated(const QString &dtcreated){
     _dtcreated = dtcreated;
}
QString Document::dtCreated() const{
     return _dtcreated;
}

void Document::setDtAccessed(const QString &dtaccessed){
     _dtaccessed = dtaccessed;
}
QString Document::dtAccessed() const{
     return _dtaccessed;
}

void Document::setDocIconIndex(const int &dociconindex){
     _dociconindex = dociconindex;
}
int Document::docIconIndex() const{
     return _dociconindex;
}

void Document::setDocSync(const int docsync){
     _docsync = docsync;
}
int Document::docSync() const{
     return _docsync;
}

void Document::setDocProtect(const QString &docprotect){
     _docprotect = docprotect;
}
QString Document::docProtect() const{
     return _docprotect;
}

void Document::setDocEncode(const QString &docencode){
     _docencode = docencode;
}
QString Document::docEncode() const{
     return _docencode;
}

void Document::setReadCount(const int readcount){
     _readcount = readcount;
}
int Document::readcount() const{
     return _readcount;
}

void Document::setRelateCount(const int relatecount){
     _relatecount = relatecount;
}
int Document::relateCount() const{
     return _relatecount;
}

void Document::setIndexFlg(const QString &indexflg){
     _indexflg = indexflg;
}
QString Document::indexFlg() const{
     return _indexflg;
}

void Document::setOpenFlg(const QString &openflg){
     _openflg = openflg;
}
QString Document::openflg() const{
     return _openflg;
}

void Document::setDelFlg(const QString &delflg){
     _delflg = delflg;
}
QString Document::delFlg() const{
     return _delflg;
}

void Document::setVersion(const int version){
     _version = version;
}
int Document::version() const{
     return _version;
}
