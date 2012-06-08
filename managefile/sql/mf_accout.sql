CREATE TABLE IF NOT EXISTS MF_ACCOUT
(
   ACOUNT_GUID                    char(36)                       not null,
   NAME                           varchar(100)                   not null,
   PWD                            varchar(200)                   not null,
   EMAIL                          varchar(200),
   primary key (ACOUNT_GUID)
)