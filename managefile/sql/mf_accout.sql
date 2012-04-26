CREATE TABLE IF NOT EXISTS MF_ACCOUT
(
   ACOUNT_GUID                    char(36)                       not null,
   NAME                           varchar(100)                   not null,
   PWD                            varchar(20)                    not null,
   EMAIL                          varchar(200),
   SCORE                          int,
   TYPE                           char(1),
   DT_EXPIRED                     char(19),
   REFEREE                        char(36),
   primary key (ACOUNT_GUID)
)