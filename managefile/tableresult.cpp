#include "tableresult.h"

TableResult::TableResult()
{

}
TableResult::TableResult(const QString &docuuid, const QString &keyword,
               const QString &filetype, const QString &filepath, const QString &filename,
               const QString &desp, const QString &content, const QString &sheetname, const int rownb, const int page,
               const QString &dtcreated) :
    _docuuid(docuuid), _keyword(keyword), _filetype(filetype), _filepath(filepath), _filename(filename), _desp(desp),
    _content(content), _sheetname(sheetname), _rownb(rownb), _page(page), _dtcreated(dtcreated)
{

}

void TableResult::setDocuuid(const QString &docuuid)
{
    _docuuid = docuuid;
}
QString TableResult::docuuid() const
{
    return _docuuid;
}

void TableResult::setKeyword(const QString &keyword){
    _keyword = keyword;
}
QString TableResult::keyword() const{
   return _keyword;
}

void TableResult::setFiletype(const QString &filetype){
   _filetype = filetype;
}
QString TableResult::filetype() const{
   return _filetype;
}

void TableResult::setFilepath(const QString &filepath){
    _filepath = filepath;
}
QString TableResult::filepath() const{
    return _filepath;
}

void TableResult::setFilename(const QString &filename){
    _filename = filename;
}
QString TableResult::filename() const{
    return _filename;
}

void TableResult::setDesp(const QString &desp){
    _desp =  desp;
}
QString TableResult::desp() const{
    return _desp;
}

void TableResult::setContent(const QString &content){
   _content = content;
}
QString TableResult::content() const{
   return _content;
}

void TableResult::setSheetname(const QString &sheetname){
   _sheetname = sheetname;
}
QString TableResult::sheetname() const{
   return _sheetname;
}

void TableResult::setRownb(const int rownb){
   _rownb = rownb;
}
int TableResult::rownb() const{
   return _rownb;
}

void TableResult::setPage(const int &page){
   _page = page;
}
int TableResult::page() const{
    return _page;
}

void TableResult::setDtcreatede(const QString &dtcreated){
    _dtcreated = dtcreated;
}
QString TableResult::dtcreated() const{
    return _dtcreated;
}
