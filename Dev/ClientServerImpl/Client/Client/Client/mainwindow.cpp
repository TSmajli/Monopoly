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

    ui->connectionStatusLabel->setText("Verbinde...");
    ui->connectionStatusLabel->setStyleSheet("color: #d17f00; font-weight: 600;");
    ui->buyPromptLabel->setText("Kein Kauf offen.");
    ui->BuyDecisonYes_Button->setEnabled(false);
    ui->BuyDecsionNo_Button->setEnabled(false);
    ui->EndTurn_Button->setEnabled(false);

    auto appendLog = [this](const QString &message) {
        ui->logTextEdit->append(message);
    };

    // Verbindung herstellen
    network->connectToServer("127.0.0.1", 4242);

    // Signale
    connect(network, &NetworkClient::connected, this, [=]() {
        qDebug() << "Mit Server verbunden!";
        ui->connectionStatusLabel->setText("Verbunden");
        ui->connectionStatusLabel->setStyleSheet("color: #1b5e20; font-weight: 600;");
        appendLog("✅ Mit Server verbunden.");
    });

    connect(network, &NetworkClient::disconnected, this, [=]() {
        qDebug() << "Verbindung getrennt!";
        ui->connectionStatusLabel->setText("Getrennt");
        ui->connectionStatusLabel->setStyleSheet("color: #b00020; font-weight: 600;");
        appendLog("⚠️ Verbindung getrennt.");
    });

    connect(network, &NetworkClient::errorOccurred, this, [=](const QString &err) {
        qDebug() << "Netzwerkfehler:" << err;
        appendLog(QString("❌ Netzwerkfehler: %1").arg(err));
    });

    connect(network, &NetworkClient::jsonReceived, this, [=](const QJsonObject &obj) mutable {
        qDebug() << "Nachricht vom Server:" << obj;

        const QString type = obj.value("type").toString();

        if (type == "assignPlayerId") {
            myPlayerId = obj.value("playerId").toInt(-1);
            qDebug() << "✅ Meine Spieler-ID ist jetzt:" << myPlayerId;
            ui->playerIdValue->setText(QString::number(myPlayerId));
            appendLog(QString("🎲 Spieler-ID erhalten: %1").arg(myPlayerId));
            return;
        }

        if (type == "info") {
            appendLog(QString("ℹ️ %1").arg(obj.value("message").toString()));
            return;
        }

        if (type == "error") {
            appendLog(QString("❌ %1").arg(obj.value("message").toString()));
            return;
        }

        if (type == "buyRequest") {
            pendingBuyFieldIndex = obj.value("fieldIndex").toInt(-1);
            QString fieldName = obj.value("fieldName").toString();
            int price = obj.value("price").toInt();

            ui->buyPromptLabel->setText(
                QString("Möchtest du %1 für %2$ kaufen?").arg(fieldName).arg(price));
            ui->BuyDecisonYes_Button->setEnabled(true);
            ui->BuyDecsionNo_Button->setEnabled(true);

            appendLog(QString("🟢 Kaufangebot: %1 (%2$)").arg(fieldName).arg(price));

            qDebug() << "🟢 BUY REQUEST:"
                     << "fieldIndex=" << pendingBuyFieldIndex
                     << "fieldName=" << fieldName
                     << "price=" << price;

            // 👉 HIER UI anzeigen (Ja / Nein)
            return;
        }

        if (type == "diceRolled") {
            int d1 = obj.value("d1").toInt();
            int d2 = obj.value("d2").toInt();
            int steps = obj.value("steps").toInt();
            QString fieldName = obj.value("fieldName").toString();

            ui->diceValue->setText(QString("%1 + %2 = %3").arg(d1).arg(d2).arg(steps));
            if (!fieldName.isEmpty()) {
                ui->fieldValue->setText(fieldName);
            }

            appendLog(QString("🎲 Würfelwurf: %1 + %2 = %3").arg(d1).arg(d2).arg(steps));
            return;
        }

        if (type == "state") {
            qDebug() << "🟦 STATE RECEIVED reason="
                     << obj.value("reason").toString();

            const int currentPlayerId = obj.value("currentPlayerId").toInt(-1);
            const bool awaitingBuyDecision = obj.value("awaitingBuyDecision").toBool(false);
            const bool awaitingEndTurn = obj.value("awaitingEndTurn").toBool(false);

            ui->currentPlayerValue->setText(
                currentPlayerId >= 0 ? QString("%1").arg(currentPlayerId) : "-");
            ui->turnStatusValue->setText(
                awaitingBuyDecision
                    ? "Warte auf Kauf"
                    : (awaitingEndTurn ? "Ende des Zuges" : "In Aktion"));

            const bool isMyTurn = (currentPlayerId == myPlayerId);
            ui->rollDiceButton->setEnabled(isMyTurn && !awaitingBuyDecision && !awaitingEndTurn);
            ui->EndTurn_Button->setEnabled(isMyTurn && awaitingEndTurn && !awaitingBuyDecision);


            QJsonArray players = obj.value("players").toArray();
            for (const QJsonValue &v : players) {
                QJsonObject p = v.toObject();

                int id = p.value("id").toInt();
                int pos = p.value("position").toInt();
                int money = p.value("money").toInt();

                if (id == myPlayerId) {
                    qDebug() << "🧍 ICH:"
                             << "Position =" << pos
                             << "Geld =" << money;
                             //<< "am Zug?" << (id == current);
                    ui->positionValue->setText(QString::number(pos));
                    ui->moneyValue->setText(QString("%1$").arg(money));
                }
            }

            if (!awaitingBuyDecision) {
                ui->buyPromptLabel->setText("Kein Kauf offen.");
                ui->BuyDecisonYes_Button->setEnabled(false);
                ui->BuyDecsionNo_Button->setEnabled(false);
            }
        }
    });


    connect(ui->rollDiceButton, &QPushButton::clicked, this, [=]() {
        network->sendRollDice(); // ohne ID
        qDebug() << "RollDice";
    });


    connect(ui->BuyDecisonYes_Button, &QPushButton::clicked, this, [=]() {
        network->sendBuyDecision(true,myPlayerId,pendingBuyFieldIndex);
        pendingBuyFieldIndex = -1;
        ui->buyPromptLabel->setText("Kauf gesendet...");
        ui->BuyDecisonYes_Button->setEnabled(false);
        ui->BuyDecsionNo_Button->setEnabled(false);
    });

    connect(ui->BuyDecsionNo_Button, &QPushButton::clicked, this, [=]() {
        network->sendBuyDecision(false,myPlayerId,pendingBuyFieldIndex);
        pendingBuyFieldIndex = -1;
        ui->buyPromptLabel->setText("Ablehnung gesendet...");
        ui->BuyDecisonYes_Button->setEnabled(false);
        ui->BuyDecsionNo_Button->setEnabled(false);
    });

    connect(ui->StartGame_Button, &QPushButton::clicked, this, [=]() {
        network->sendStartGame();
    });

    connect(ui->EndTurn_Button, &QPushButton::clicked, this, [=]() {
        network->sendEndTurn();
        ui->EndTurn_Button->setEnabled(false);
        appendLog("🔁 Zugende angefragt.");
    });
}



MainWindow::~MainWindow()
{
    delete ui;
}
