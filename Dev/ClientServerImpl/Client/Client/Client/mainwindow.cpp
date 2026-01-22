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

    connect(network, &NetworkClient::jsonReceived, this, [=](const QJsonObject &obj) mutable {
        qDebug() << "Nachricht vom Server:" << obj;

        const QString type = obj.value("type").toString();

        if (type == "assignPlayerId") {
            myPlayerId = obj.value("playerId").toInt(-1);
            qDebug() << "✅ Meine Spieler-ID ist jetzt:" << myPlayerId;
            return;
        }

        if (type == "state") {
            int current = obj.value("currentPlayerId").toInt(-1);
            qDebug() << "STATE reason=" << obj.value("reason").toString()
                     << "currentPlayerId=" << current
                     << "myPlayerId=" << myPlayerId;
        }
    });


    connect(ui->rollDiceButton, &QPushButton::clicked, this, [=]() {
        network->sendRollDice(); // ohne ID
        qDebug() << "RollDice";
    });


    connect(ui->StartGameButton, &QPushButton::clicked, this, [=]() {
        network->NetworkClient::sendStartGame(); // 1 = Spieler-ID
        qDebug() << "RollDice";
    });

}



MainWindow::~MainWindow()
{
    delete ui;
}
