UPDATE MF_DIR 
SET 
    DIR_PARENT_UUID='%1',
    DIR_NAME='%2',
    DIR_DESCRIPTION='%3', 
    DIR_ICON='%4', 
    DIR_ORDER='%5', 
    MF_VERSION='%6', 
    DT_MODIFIED=datetime(CURRENT_TIMESTAMP,'localtime'),
    DELETE_FLAG='%7'
WHERE DIR_GUID='%8'
