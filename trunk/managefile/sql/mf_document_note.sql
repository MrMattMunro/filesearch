CREATE TABLE IF NOT EXISTS T_DOCUMENT_NOTE
(
   NOTE_GUID                      char(36)                       not null,
   DOCUMENT_GUID                  char(36)                       not null,
   NOTE_CONTENT                   varchar(768)                   not null,
   DOCUMENT_OWNER                 varchar(150),
   PAGE                           int,
   SHEETPAGE                      varchar(150),
   ROW                            int,
   COLUMN                         int,
   primary key (NOTE_GUID)
)