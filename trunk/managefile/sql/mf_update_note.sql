UPDATE MF_DOCUMENT_NOTE
SET 
         DOCUMENT_GUID='%1',
	 NOTE_NAME='%2',
         NOTE_CONTENT='%3',
         NOTE_OWNER='%4',
         PAGE='%5',
         SHEETPAGE='%6',
         ROW='%7',
	 MF_VERSION='%8',
         DT_MODIFIED=datetime(CURRENT_TIMESTAMP,'localtime')
WHERE NOTE_GUID='%9'