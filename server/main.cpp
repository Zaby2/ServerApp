
#include <QCoreApplication>
#include <iostream>
#include "server.h"
#include "database.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
   // std::cout << "2";
    Server ser;

    return a.exec();
}
