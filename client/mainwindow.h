
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qmessagebox.h"
#include <QMainWindow>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_4_clicked();
    void reading();
    void sendToServer(QString str);
    QJsonObject createRequest(int num);
    void parseRes(QString str);
    void on_pushButton_3_clicked();
    void changeCheckColor();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QByteArray data;
    QTimer *timer;
    QMessageBox msgBox;
};

#endif // MAINWINDOW_H
