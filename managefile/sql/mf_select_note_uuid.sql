SELECT   NOTE_GUID,
         DOCUMENT_GUID,
         NOTE_CONTENT,
         NOTE_OWNER,
         PAGE,
         SHEETPAGE,
         ROW,
         COLUMN,
         DT_MODIFIED
FROM
   MF_DOCUMENT_NOTE
WHERE NOTE_GUID='%1'