
#include "server.h"
#include "database.h"

Server::Server()
{
    if(this->listen(QHostAddress::Any, 2323)) {
        qDebug() << "Start is Succesfull";

    } else {
        qDebug() << "Failed";
    }
    db.connect();
}

void Server::incomingConnection(qintptr socketDiscriptor) {
   // qDebug() << "Client connected";
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDiscriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::reading);
    connect(socket, &QTcpSocket::disconnected, socket ,&QTcpSocket::deleteLater);
     qDebug() << "Client connected";
}

void Server::reading() {
    socket = (QTcpSocket*) sender();

     QDataStream in(socket);
     in.setVersion(QDataStream::Qt_6_4);
     if (in.status() == QDataStream::Ok) {
        qDebug() << "Reading";
        QString str;
        in >> str;
        sendToClient(db.select(str));
     } else {
         qDebug() << "Error";
     }
}

void Server::sendToClient(QString str) {
     data.clear();
     QDataStream out(&data, QIODevice::WriteOnly);
     out.setVersion(QDataStream::Qt_6_4);
     out<<str;
     socket->write(data);
}
