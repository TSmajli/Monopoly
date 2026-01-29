#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>


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

        if (type == "buyRequest") {
            pendingBuyFieldIndex = obj.value("fieldIndex").toInt(-1);

            qDebug() << "🟢 BUY REQUEST:"
                     << "fieldIndex=" << pendingBuyFieldIndex
                     << "fieldName=" << obj.value("fieldName").toString()
                     << "price=" << obj.value("price").toInt();

            // 👉 HIER UI anzeigen (Ja / Nein)
            return;
        }

        if (type == "state") {
            qDebug() << "🟦 STATE RECEIVED reason="
                     << obj.value("reason").toString();


            const int current = obj.value("currentPlayerId").toInt(-1);
            QJsonArray players = obj.value("players").toArray();
            for (const QJsonValue &v : players) {
                QJsonObject p = v.toObject();

                int id = p.value("id").toInt();
                int pos = p.value("position").toInt();
                int money = p.value("money").toInt();

                if (id == myPlayerId) {
                    qDebug() << "🧍 ICH:"
                             << "Position =" << pos
                             << "Geld =" << money
                             << "am Zug?" << (id == current);
                }
            }
        }
    });


    connect(ui->rollDiceButton, &QPushButton::clicked, this, [=]() {
        network->sendRollDice(); // ohne ID
        qDebug() << "RollDice";
    });


    connect(ui->BuyDecisonYes_Button, &QPushButton::clicked, this, [=]() {
        if (pendingBuyFieldIndex < 0) {
            qDebug() << "Kein Kauf ausstehend.";
            return;
        }
        network->sendBuyDecision(true, myPlayerId, pendingBuyFieldIndex);
        pendingBuyFieldIndex = -1;
    });

    connect(ui->BuyDecsionNo_Button, &QPushButton::clicked, this, [=]() {
        if (pendingBuyFieldIndex < 0) {
            qDebug() << "Kein Kauf ausstehend.";
            return;
        }
        network->sendBuyDecision(false, myPlayerId, pendingBuyFieldIndex);
        pendingBuyFieldIndex = -1;
    });

    connect(ui->StartGame_Button, &QPushButton::clicked, this, [=]() {
        network->sendStartGame();
    });
}



MainWindow::~MainWindow()
{
    delete ui;
}
