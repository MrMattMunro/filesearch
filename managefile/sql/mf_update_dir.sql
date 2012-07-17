UPDATE MF_DIR 
SET 
    DIR_PARENT_UUID='%1',
    DIR_NAME='%2',
    DIR_DESCRIPTION='%3', 
    DIR_ICON='%4', 
    DIR_ORDER='%5',
    DIR_PROTECT='%6',
    MF_VERSION='%7', 
    DT_MODIFIED=datetime(CURRENT_TIMESTAMP,'localtime'),
    DELETE_FLAG='%8'
WHERE DIR_GUID='%9'
