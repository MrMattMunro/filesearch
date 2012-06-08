CREATE TABLE IF NOT EXISTS MF_META
(
   ACOUNT_GUID                    char(36)                       not null,
   META_NAME                      varchar(100)                   not null,
   META_KEY                       varchar(200)                   not null,
   META_VALUE                     varchar(200),
   primary key (ACOUNT_GUID, META_NAME, META_KEY)
)