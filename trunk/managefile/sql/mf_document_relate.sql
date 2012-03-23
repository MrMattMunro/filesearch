CREATE TABLE IF NOT EXISTS MF_DOCUMENT_RELATED
(
   RELATED_GUID                   char(36)                       not null,
   DOCUMENT_GUID                  varchar(36)                    not null,
   RELATED_NAME                   varchar(768)                   not null,
   RELATED_URL                    varchar(2048),
   RELATED_DESCRIPTION            varchar(600),
   DT_INFO_MODIFIED               char(19),
   RELATED_INFO_MD5               char(32),
   DT_DATA_MODIFIED               char(19),
   RELATED_DATA_MD5               char(32),
   MF_VERSION                     int64,
   primary key (RELATED_GUID)
)