CREATE TABLE IF NOT EXISTS MF_ACCOUT
(
   ACOUNT_GUID                    char(36)                       not null,
   NAME                           varchar(100)                   not null,
   PWD                            varchar(200)                   not null,
   EMAIL                          varchar(200)                   not null,
   TYPE                           varchar(100),
   SCORE                          int,
   DT_EXPIRED                     Date,  
   STORE_LIMIT                    long,
   STORE_USED                     long,  
   TRAFFIC_LIMIT                  long,
   TRAFFIC_USED                   long, 
   LAST_SEL_DIRS                  varchar(300),
   LAST_SEL_TAGS                  varchar(300),
   LAST_OPEN_DOC_                 varchar(300),
   LAST_OPEN_NOTES                varchar(300),
   LAST_OPEN_ULRS                 varchar(300),
   primary key (ACOUNT_GUID)
)

// TYPE a2b29z3fde free
// TYPE b6e70zfef3 vip
