#ifndef ResultDao_H
#define ResultDao_H

#include <QCoreApplication>
#include <QList>

typedef struct
{
        QString DOC_UUID;
        QString KEY_WORD;
        QString FILE_TYPE;
        QString FILE_PATH;
        QString FILE_NAME;
        QString DESP;
        QString CONTENT;
        QString SHEET_NAME;
        int ROW_NB;
        int PAGE;
        QString DT_CREATED;

}Result;

class ResultDao
{
            Q_DECLARE_TR_FUNCTIONS(ResultDao)
        public:
                // 前缀
                static QList<Result> selectByPrefix(const QString & keyword);
                // 后缀
                static QList<Result> selectBySuffix(const QString & keyword);
                // 中间
                static QList<Result> selectByMiddle(const QString & keyword);
                // 完全相等
                static QList<Result> selectByFullEqual(const QString & keyword);
                // 删除关于某个文档的所有检索记录
                static bool deleteResultByDocUid(const QString & docUuid);

        private:
                static void exception(const QString & message);
};

#endif
