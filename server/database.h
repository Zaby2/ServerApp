
#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QSqlDatabase>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>


class dataBase
{


public:
    QSqlDatabase db;
    QSqlDatabase connect();
    QString select(QString query_);
    QString createQuery(QJsonObject obj);
    dataBase();

};

#endif // DATABASE_H
