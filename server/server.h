
#ifndef SERVER_H
#define SERVER_H


#include "database.h"
#include <QTcpServer>
#include <QTcpSocket>

class Server : public QTcpServer
{

    Q_OBJECT


public:
    Server();
    QTcpSocket *socket;
    dataBase db;

private:
    QByteArray data;

public slots:


    void incomingConnection(qintptr  socketDescriptor);
    void reading();
   // void readyRead()
    void sendToClient(QString str);

};

#endif // SERVER_H
