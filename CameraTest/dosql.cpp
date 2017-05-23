#include "dosql.h"

doSQL::doSQL(QObject *parent) : QObject(parent)
{

}

void doSQL::doComand(QString comand,QString tablename, QString value)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("tzz.db");
    bool ok = db.open();

    QSqlQuery query;
    QString sql;

    if(ok)
    {
        if(comand == "SELECT")
        {
            sql = QString("SELECT %1 FROM %2").arg(value).arg(tablename);
            query.exec(sql);
            query.first();
            query.value(1).toString();
        }
        else if(comand == "INSERT")
        {

        }
        else if(comand == "UPDATE")
        {

        }
        else if(comand == "DELETE")
        {

        }
        else
        {
            db.close();
            return;
        }
    }
}
