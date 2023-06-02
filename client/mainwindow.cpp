
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    timer = new QTimer();
    msgBox.setWindowTitle("Результат");
    msgBox.setText("Запрос выполнен успешно");
    ui->radioButton->setChecked(true);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::reading);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::disconnectFromHost);

    connect(timer, SIGNAL(timeout()), this, SLOT(changeCheckColor()));

    timer->start(1000);
    ui->l->setFixedSize(10, 10);
    ui->l->setStyleSheet("border-radius: 5px; background-color: red;");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeCheckColor() {
    if(socket->state() == QTcpSocket::UnconnectedState) {
        ui->l->setStyleSheet("border-radius: 5px; background-color: red;");
    } else if(socket->state() == QTcpSocket::ConnectingState) {
        ui->l->setStyleSheet("border-radius: 5px; background-color: yellow;");
    } else if(socket->state() == QTcpSocket::ConnectedState) {
        ui->l->setStyleSheet("border-radius: 5px; background-color: green;");
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    socket->connectToHost("127.0.0.1", 2323);
}

void MainWindow::sendToServer(QString str) {
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);
    out<<str;
    socket->write(data);
}

void MainWindow::reading() {
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_4);
    if (in.status() == QDataStream::Ok) {
        qDebug() << "Reading client";
        QString str;
        in >> str;
        if(str == "") {
            msgBox.exec();
        }else {
            parseRes(str);
        }

    } else {
        qDebug() << "Error clinet";
    }

}

void MainWindow::on_pushButton_3_clicked()
{
    QJsonObject data = createRequest(3);
    QJsonArray arr {data};
    QJsonDocument doc(arr);
    sendToServer(QString::fromLatin1(doc.toJson()));

}


void MainWindow::on_pushButton_clicked()
{
    QJsonObject data = createRequest(1);
    QJsonArray arr {data};
    QJsonDocument doc(arr);

    sendToServer(QString::fromLatin1(doc.toJson()));
}


void MainWindow::on_pushButton_2_clicked()
{
    QJsonObject data = createRequest(2);
    QJsonArray arr {data};
    QJsonDocument doc(arr);
    sendToServer(QString::fromLatin1(doc.toJson()));
}

void MainWindow::parseRes(QString str) {
    QString res = "";
    QJsonDocument doc = QJsonDocument::fromJson(str.toLatin1());
    QJsonArray arr = doc.array();
    QJsonArray::iterator itArr;
    for(itArr = arr.begin(); itArr != arr.end(); itArr++) {
        QJsonObject::iterator itObj;
        QJsonObject curOb = itArr->toObject();
        res += "Имя: " + curOb.find("name")->toString() + "| ";
        res += "Фамилия: " + curOb.find("secondname")->toString()+ "| ";
        res += "Отчество: " + curOb.find("familyname")->toString()+ "| ";
        res += "Дата рождения: " + curOb.find("date")->toString()+ "| ";
        res += "Пол: " + curOb.find("gender")->toString()+ " ";
        res += "\r\n";
        res += "--------------------------------------";
        res += "\r\n";
    }
    ui->plainTextEdit->setPlainText(res);
}
QJsonObject MainWindow::createRequest(int num) {
    QJsonObject data;
    data.insert("id", num);
    data.insert("secondname", ui->lineEdit->text());
    data.insert("name", ui->lineEdit_2->text());
    data.insert("familyname", ui->lineEdit_3->text());
    data.insert("date", ui->dateEdit->text());
    if(ui->radioButton->isChecked()) {
         data.insert("gender", "Ж");
    } else {
          data.insert("gender", "М");
    }
    return data;
}

void MainWindow::on_pushButton_5_clicked()
{
    QJsonObject data = createRequest(4);
    QJsonArray arr {data};
    QJsonDocument doc(arr);
    sendToServer(QString::fromLatin1(doc.toJson()));
}

