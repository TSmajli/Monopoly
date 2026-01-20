#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    network = new NetworkClient(this);

    // Verbindung herstellen
    network->connectToServer("127.0.0.1", 4242);

    // Signale
    connect(network, &NetworkClient::connected, this, []() {
        qDebug() << "Mit Server verbunden!";
    });

    connect(network, &NetworkClient::disconnected, this, []() {
        qDebug() << "Verbindung getrennt!";
    });

    connect(network, &NetworkClient::errorOccurred, this, [](const QString &err) {
        qDebug() << "Netzwerkfehler:" << err;
    });

    connect(network, &NetworkClient::jsonReceived, this, [](const QJsonObject &obj) {
        qDebug() << "Nachricht vom Server:" << obj;
    });

    connect(ui->rollDiceButton, &QPushButton::clicked, this, [=]() {
        network->sendRollDice(1); // 1 = Spieler-ID
    });

}

void sendRollDice(QTcpSocket *socket)
{
    QJsonObject msg;
    msg["type"] = "rollDice";
    msg["playerId"] = 1;

    QJsonDocument doc(msg);
    socket->write(doc.toJson(QJsonDocument::Compact) + "\n");
}

MainWindow::~MainWindow()
{
    delete ui;
}
