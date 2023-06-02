
#include "database.h"

dataBase::dataBase()
{


}
QSqlDatabase dataBase::connect() {
    db = QSqlDatabase::addDatabase("QPSQL");

    db.setDatabaseName("postgres");
    db.setHostName("127.0.0.1");
    db.setPort(5432);
    db.setUserName("postgres");
    db.setPassword("1234");


    if (!db.open()) {
        qDebug() << "Hyevo";
    } else {
        qDebug() << "Nice";
    }
    return db;
}
QString dataBase::select(QString query_) {
    bool fl = false;
    QString res;
    QSqlQuery query(db);
    QJsonDocument doc = QJsonDocument::fromJson(query_.toLatin1());
    QJsonArray arr = doc.array();
    QJsonObject obj = arr.first().toObject();
    res = createQuery(obj);
    //qDebug() << res;
    query.exec(res);
    QJsonArray resArr;
    while(query.next()) {
        fl = true;
        QJsonObject resObj;
        resObj.insert("name", query.value(1).toString());
        resObj.insert("secondname", query.value(2).toString());
        resObj.insert("familyname", query.value(3).toString());
        resObj.insert("date", query.value(4).toString());
        resObj.insert("gender", query.value(5).toString());
        resArr.push_back(resObj);
    }
    if(fl == true) {
        QJsonDocument resDoc(resArr);
        return QString::fromLatin1(resDoc.toJson());
    } else {
        return "";
    }
}

QString dataBase::createQuery(QJsonObject obj) {
     QString name;
     QString tail;
     QJsonObject::iterator it;
     it = obj.find("id");
     int num = it->toInt();
     if(it.value().toInt() == 1) {
         name = "SELECT * FROM \"Students\" WHERE ";
     } else if(it.value().toInt() == 2) {
        name = "DELETE FROM \"Students\" WHERE ";
     } else if(it.value().toInt() == 3){
         name = "INSERT INTO \"Students\" ( ";
        tail = ") VALUES (";
     }
     for(it = obj.begin(); it!=obj.end(); it++) {
        if(it.value().toString() != "" && it.key() != "id" && num != 3) {
            name +=  it.key()+ "= ";
            name += "'"+ it.value().toString() + "'" + " AND ";
        } else if(num == 3 && it.key() != "id") {
            name += it.key() + ", ";
            if(it.value() == "" ) {
                tail += "null, ";
            } else {
                tail += "'" + it.value().toString() + "', ";
            }
        }

     }


     if(num != 3) {
        name.remove(name.length()-4, 3);
     } else {
        name.remove(name.length()-2, 1);
        tail.remove(tail.length()-2, 1);
        tail += ")";
        name += tail;
     }
     if(num == 4) {
        name =  name = "SELECT * FROM \"Students\"";
     }

     return name;

}



