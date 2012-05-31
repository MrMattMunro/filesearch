CREATE TABLE IF NOT EXISTS MF_DIR
(
   DIR_GUID                       char(36)                       not null,
   DIR_PARENT_UUID                char(36),
   DIR_NAME                       varchar(150),
   DIR_DESCRIPTION                varchar(600),
   DIR_ICON		          varchar(100),
   DIR_ORDER                      int                          default 0,
   DIR_PROTECT                    varchar(50),
   DT_MODIFIED                    char(19),  
   MF_VERSION                     int64                        default 0,
   DELETE_FLAG                    char(1)                      default '0',
   primary key (DIR_GUID)
)
