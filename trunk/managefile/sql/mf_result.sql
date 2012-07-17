CREATE TABLE IF NOT EXISTS MF_RESULT
(
   DOCUMENT_GUID              char(36)                       not null,
   KEY_WORD                   varchar(300),
   FILE_TYPE                  char(36)                    not null,                    
   FILE_PATH                  varchar(300),
   FILE_NAME                  varchar(100),
   DESP                       varchar(300),
   CONTENT                    varchar(1000),
   SHEET_NAME                 varchar(100),
   ROW_NB                      int           default 0,
   PAGE                        int           default 0,
   DT_CREATED                  char(19)
)