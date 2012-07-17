SELECT    TAG_GUID,
          TAG_NAME,
          TAG_DESCRIPTION,
          DT_MODIFIED,
          MF_VERSION
FROM
   MF_TAG
WHERE TAG_GROUP_GUID='%1'
