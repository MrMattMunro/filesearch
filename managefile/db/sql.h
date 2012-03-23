#ifndef SQL_H
#define SQL_H

#include <QString>

#endif // SQL_H

Sql* Sql::_instance = 0;


Sql::Sql(QObject *parent);

class Sql
{
        Q_DECLARE_TR_FUNCTIONS(sql);

        public:
            Sql(QObject *parent = 0);
            ~Sql();

            static QString insertTag() { return "
                                         Insert + |


                                        Into "; };


};

#endif
