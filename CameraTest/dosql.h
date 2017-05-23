#ifndef DOSQL_H
#define DOSQL_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>


class doSQL : public QObject
{
    Q_OBJECT
protected:
    explicit doSQL(QObject *parent = 0);

public:
    static  doSQL* open()
    {
        static doSQL p_sql;
        return &p_sql;
    }

    void    doComand(QString comand, QString tablename, QString value = 0);

};

#endif // DOSQL_H
