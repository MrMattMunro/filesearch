SELECT    DOCUMENT_GUID,
          DOCUMENT_TITLE,
          DIR_GUID,
          DOCUMENT_LOCATION,
          DOCUMENT_NAME,
          DOCUMENT_SEO,
          DOCUMENT_URL,
          DOCUMENT_AUTHOR,
          DOCUMENT_KEYWORDS,
          DOCUMENT_TYPE,
          DOCUMENT_OWNER,
          DT_CREATED,
          DT_MODIFIED,
          DT_ACCESSED,
          DOCUMENT_ICON_INDEX,
          DOCUMENT_SYNC,
          DOCUMENT_PROTECT,
          DOCUMENT_ENCODE,
          DOCUMENT_READ_COUNT,
          DOCUMENT_RELATE_COUNT,
          DOCUMENT_INDEXFLG,
          DOCUMENT_OPERFLG,
          DELETE_FLAG,
          MF_VERSION
FROM
   MF_DOCUMENT
WHERE DELETE_FLAG='%1'
