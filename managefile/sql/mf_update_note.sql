UPDATE MF_DOCUMENT_NOTE
SET 
         DOCUMENT_GUID='%1',
         NOTE_CONTENT='%2',
         NOTE_OWNER='%3',
         PAGE='%4',
         SHEETPAGE='%5',
         ROW='%6',
         COLUMN_NB='%7',
         DT_MODIFIED=datetime(CURRENT_TIMESTAMP,'localtime')
WHERE NOTE_GUID='%8'