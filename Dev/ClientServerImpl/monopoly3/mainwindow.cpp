#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "networkclient.h"

#include <QFile>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonObject>
#include <QPushButton>
#include <QStringList>
#include <QTextStream>

namespace {
QString highlightStyle(const QString &baseStyle, const QString &color)
{
    QString style = baseStyle;
    if (!style.endsWith(';')) {
        style.append(';');
    }
    style.append(QString("border: 3px solid %1;").arg(color));
    return style;
}

QString ownershipStyle(const QString &baseStyle, const QString &color)
{
    QString style = baseStyle;
    if (!style.endsWith(';')) {
        style.append(';');
    }
    style.append(QString("background-color:%1;").arg(color));
    return style;
}

QString buttonStyle(const QString &bg, const QString &hover)
{
    return QString(
        "QPushButton {"
        "background-color:%1;"
        "border-radius:12px;"
        "color:white;"
        "font-weight:600;"
        "}"
        "QPushButton:hover {"
        "background-color:%2;"
        "}"
        "QPushButton:disabled {"
        "background-color:#555;"
        "color:#bbb;"
        "}").arg(bg, hover);
}
} // namespace

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , network(new NetworkClient(this))
{
    ui->setupUi(this);

    ui->startLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->textEdit_3->setReadOnly(true);
    ui->playersText->setReadOnly(true);

    ui->ServerButton->setStyleSheet(
        "QPushButton {"
        "background-color:#252850;"
        "border-radius:10px;"
        "color:white;"
        "}"
        "QPushButton:hover {"
        "  background-color: #191970;"
        "}");

    ui->importCSVbutton->setStyleSheet(
        "QPushButton {"
        "background-color:#252850;"
        "border-radius:10px;"
        "color:white;"
        "border-width:2px;"
        "border-color:black;"
        "}"
        "QPushButton:hover {"
        "  background-color: #191970;"
        "}");

    ui->addPlayer->setStyleSheet(
        "QPushButton {"
        "border-radius: 13px;"
        "background-color:#469536;"
        "border-width:2px;"
        "border-color:transparent;"
        "color:white;"
        "font: 25pt ;"
        "font-weight:bold;"
        "}"
        "QPushButton:hover {"
        "  background-color: #38772B;"
        "}");

    ui->startButton->setStyleSheet(
        buttonStyle("#469536", "#38772B"));

    ui->readyStartButton->setStyleSheet(buttonStyle("#252850", "#191970"));
    ui->rollDiceButton->setStyleSheet(buttonStyle("#469536", "#38772B"));
    ui->buyButton->setStyleSheet(buttonStyle("#275EA8", "#1e4b85"));
    ui->sellButton->setStyleSheet(buttonStyle("#842d2d", "#6d2323"));
    ui->readyButton->setStyleSheet(buttonStyle("#252850", "#191970"));
    ui->buyProperty->setStyleSheet(buttonStyle("#252850", "#191970"));
    ui->surrenderButton->setStyleSheet(buttonStyle("#842d2d", "#6d2323"));
    ui->saveCsvButton->setStyleSheet(buttonStyle("#275EA8", "#1e4b85"));
    ui->playAgainButton->setStyleSheet(buttonStyle("#469536", "#38772B"));
    ui->logExitButton->setStyleSheet(buttonStyle("#842d2d", "#6d2323"));

    ui->readyButton->setEnabled(false);
    ui->buyButton->setEnabled(false);
    ui->sellButton->setEnabled(false);
    ui->rollDiceButton->setEnabled(false);
    ui->surrenderButton->setEnabled(true);
    ui->startButton->setEnabled(false);

    ui->diceResult->setText("-");
    ui->fieldInfoValue->setText("-");
    ui->winnerLabel->setVisible(false);
    ui->logExitButton->setVisible(false);
    ui->playersText->setText("Keine Spieler verbunden.");

    ui->player2->setVisible(false);
    ui->player3->setVisible(false);
    ui->player4->setVisible(false);

    boardFields = {
        ui->Feld0_3, // Start (oben links)
        ui->Feld1_3,
        ui->Feld2_3,
        ui->Feld3_3,
        ui->Feld4_3,
        ui->Feld5_3,
        ui->Feld6_3,
        ui->Feld7_3,
        ui->Feld8_3,
        ui->Feld9_3,
        ui->Feld10_4, // Ecke oben rechts
        ui->Feld17_3,
        ui->Feld12_3,
        ui->Feld13_3,
        ui->Feld14_3,
        ui->Feld15_3,
        ui->Feld16_3,
        ui->Feld11_3,
        ui->Feld18_3,
        ui->Feld19_3,
        ui->Feld20_3, // Ecke unten rechts
        ui->Feld21_3,
        ui->Feld22_3,
        ui->Feld23_3,
        ui->Feld24_3,
        ui->Feld25_3,
        ui->Feld26_3,
        ui->Feld27_3,
        ui->Feld28_3,
        ui->Feld29_3,
        ui->Feld30_3, // Ecke unten links
        ui->Feld31_3,
        ui->Feld32_3,
        ui->Feld33_3,
        ui->Feld34_3,
        ui->Feld35_3,
        ui->Feld36_3,
        ui->Feld37_3,
        ui->Feld38_3,
        ui->Feld39_3,
    };

    for (QWidget *field : boardFields) {
        fieldBaseStyles.insert(field, field->styleSheet());
    }

    playerColors.insert(1, QColor("#00cc44"));
    playerColors.insert(2, QColor("#ffb300"));
    playerColors.insert(3, QColor("#4dd0e1"));
    playerColors.insert(4, QColor("#ab47bc"));

    setConnectionStatus("Verbinde...", "#d17f00");
    network->connectToServer("127.0.0.1", 4242);

    connect(network, &NetworkClient::connected, this, [this]() {
        setConnectionStatus("Verbunden", "#1b5e20");
        appendLog("✅ Mit Server verbunden.", "Server");
    });

    connect(network, &NetworkClient::disconnected, this, [this]() {
        setConnectionStatus("Getrennt", "#b00020");
        appendLog("⚠️ Verbindung getrennt.", "Server");
    });

    connect(network, &NetworkClient::errorOccurred, this, [this](const QString &err) {
        appendLog(QString("❌ Netzwerkfehler: %1").arg(err), "Server");
    });

    connect(network, &NetworkClient::jsonReceived, this, [this](const QJsonObject &obj) {
        const QString type = obj.value("type").toString();

        if (type == "assignPlayerId") {
            myPlayerId = obj.value("playerId").toInt(-1);
            appendLog(QString("🎲 Spieler-ID erhalten: %1").arg(myPlayerId), "Server");
            ui->player1->setText(QString("Spieler %1 (Du)").arg(myPlayerId));
            network->sendGetState();
            return;
        }

        if (type == "info") {
            appendLog(QString("ℹ️ %1").arg(obj.value("message").toString()), "Server");
            return;
        }

        if (type == "error") {
            appendLog(QString("❌ %1").arg(obj.value("message").toString()), "Server");
            return;
        }

        if (type == "log") {
            const int playerId = obj.value("playerId").toInt(-1);
            const QString playerName = resolvePlayerName(playerId);
            appendLog(obj.value("message").toString(), playerName);
            return;
        }

        if (type == "buyRequest") {
            pendingBuyFieldIndex = obj.value("fieldIndex").toInt(-1);
            const QString fieldName = obj.value("fieldName").toString();
            const int price = obj.value("price").toInt();
            const int playerId = obj.value("playerId").toInt(-1);
            const QString playerName = resolvePlayerName(playerId);

            pendingBuyPlayerId = playerId;
            appendLog(QString("🟢 Kaufangebot: %1 (%2$)").arg(fieldName).arg(price), playerName);
            currentFieldName = QString("%1 (%2$)").arg(fieldName).arg(price);
            ui->fieldInfoValue->setText(currentFieldName);
            currentFieldIndex = pendingBuyFieldIndex;
            updateFieldInfo(pendingBuyFieldIndex);
            setAwaitingBuyDecision(true);
            return;
        }

        if (type == "diceRolled") {
            const int d1 = obj.value("d1").toInt();
            const int d2 = obj.value("d2").toInt();
            const int steps = obj.value("steps").toInt();
            const QString fieldName = obj.value("fieldName").toString();
            const int newPosition = obj.value("newPosition").toInt(-1);
            const int playerId = obj.value("playerId").toInt(-1);
            const QString playerName = resolvePlayerName(playerId);

            ui->diceResult->setText(QString("%1 + %2 = %3").arg(d1).arg(d2).arg(steps));

            QString rollMessage = QString("🎲 Würfelwurf: %1 + %2 = %3").arg(d1).arg(d2).arg(steps);
            if (!fieldName.isEmpty()) {
                rollMessage += QString(" → %1").arg(fieldName);
            }
            appendLog(rollMessage, playerName);
            if (!fieldName.isEmpty()) {
                currentFieldName = fieldName;
                ui->fieldInfoValue->setText(currentFieldName);
            }
            if (newPosition >= 0) {
                playerPositions.insert(playerId, newPosition);
                updatePlayerTokens();
            }
            if (playerId == myPlayerId && newPosition >= 0) {
                currentFieldIndex = newPosition;
                updateFieldInfo(newPosition);
            }
            if (playerId == myPlayerId) {
                updateHouseBuyAvailability();
            }
            return;
        }

        if (type == "state") {
            lastStateSnapshot = obj;
            const int newCurrentPlayerId = obj.value("currentPlayerId").toInt(-1);
            const bool awaitingBuyDecision = obj.value("awaitingBuyDecision").toBool(false);
            const bool awaitingEndTurn = obj.value("awaitingEndTurn").toBool(false);
            gameStarted = obj.value("gameStarted").toBool(false);
            gameFinished = obj.value("gameFinished").toBool(false);
            winnerId = obj.value("winnerId").toInt(-1);
            pendingBuyPlayerId = obj.value("pendingBuyPlayerId").toInt(-1);
            pendingBuyFieldIndex = obj.value("pendingBuyFieldIndex").toInt(-1);
            pendingEndTurnPlayerId = obj.value("pendingEndTurnPlayerId").toInt(-1);

            currentPlayerId = newCurrentPlayerId;
            setAwaitingBuyDecision(awaitingBuyDecision);
            setAwaitingEndTurn(awaitingEndTurn);

            const bool myTurn = currentPlayerId == myPlayerId;
            ensureDiceEnabled(gameStarted && myTurn && !awaitingBuyDecision && !awaitingEndTurn);

            QJsonArray players = obj.value("players").toArray();
            playerNames.clear();
            playerPositions.clear();
            QStringList playerLines;
            QStringList playerNamesForStart;
            QStringList playerReadyForStart;
            int readyCount = 0;
            for (const QJsonValue &v : players) {
                const QJsonObject p = v.toObject();
                const int id = p.value("id").toInt();
                const int pos = p.value("position").toInt();
                const int money = p.value("money").toInt();
                const bool ready = p.value("ready").toBool(false);
                const QString name = p.value("name").toString(QString("Spieler %1").arg(id));

                playerNames.insert(id, name);
                playerPositions.insert(id, pos);
                if (ready) {
                    readyCount++;
                }

                if (id == currentPlayerId) {
                    ui->Geld_6->setText(name);
                    ui->Geld_5->setText(QString("%1$").arg(money));
                }
                if (id == myPlayerId) {
                    localReady = ready;
                }
                const QString readyMark = ready ? "✅" : "⏳";
                const QString turnMark = (id == currentPlayerId) ? "▶" : "•";
                playerLines << QString("%1 %2 (ID %3) – Feld %4 – %5$ %6")
                                   .arg(turnMark)
                                   .arg(name)
                                   .arg(id)
                                   .arg(pos)
                                   .arg(money)
                                   .arg(readyMark);
                playerNamesForStart << name;
                playerReadyForStart << readyMark;
            }

            if (playerLines.isEmpty()) {
                ui->playersText->setText("Keine Spieler verbunden.");
            } else {
                ui->playersText->setText(playerLines.join("\n"));
            }

            const QList<QPushButton *> startButtons = {
                ui->player1,
                ui->player2,
                ui->player3,
                ui->player4,
            };
            for (int i = 0; i < startButtons.size(); ++i) {
                if (i < playerNamesForStart.size()) {
                    startButtons[i]->setText(QString("%1 %2")
                                                 .arg(playerNamesForStart.at(i))
                                                 .arg(playerReadyForStart.value(i)));
                    startButtons[i]->setVisible(true);
                } else {
                    startButtons[i]->setText(QString("Spieler %1").arg(i + 1));
                    startButtons[i]->setVisible(false);
                }
            }

            const bool allReady = !players.isEmpty() && readyCount == players.size();
            ui->startButton->setEnabled(!gameStarted && allReady);
            ui->readyStartButton->setEnabled(!gameStarted);
            const QString readyButtonText = localReady ? "Bereit ✔" : "Bereit";
            ui->readyStartButton->setText(readyButtonText);

            const QJsonArray fields = obj.value("fields").toArray();
            fieldInfoByIndex.clear();
            for (const QJsonValue &fv : fields) {
                const QJsonObject fo = fv.toObject();
                const int index = fo.value("index").toInt(-1);
                if (index >= 0) {
                    fieldInfoByIndex.insert(index, fo);
                }
            }

            const int myPos = playerPositions.value(myPlayerId, -1);
            if (myPos >= 0) {
                currentFieldIndex = myPos;
                updateFieldInfo(myPos);
            }

            updateBoardHighlights();
            updatePlayerTokens();
            updateHouseMarkers();
            updateHouseBuyAvailability();

            if (gameFinished && suppressWinViewOnce) {
                suppressWinViewOnce = false;
                ui->stackedWidget->setCurrentWidget(ui->gameView);
                ui->winnerLabel->setVisible(false);
            } else if (gameFinished) {
                if (winnerId > 0) {
                    ui->winWinnerLabel->setText(QString("🏆 Gewinner: %1").arg(resolvePlayerName(winnerId)));
                } else {
                    ui->winWinnerLabel->setText("🏆 Gewinner: -");
                }
                ui->stackedWidget->setCurrentWidget(ui->winView);
            } else if (gameStarted) {
                ui->stackedWidget->setCurrentWidget(ui->gameView);
            } else {
                ui->stackedWidget->setCurrentWidget(ui->startView);
            }
            ui->winnerLabel->setVisible(false);
        }
    });

    connect(ui->readyButton, &QPushButton::clicked, this, [this]() {
        if (!ui->readyButton->isEnabled()) {
            return;
        }
        network->sendEndTurn();
        setAwaitingEndTurn(false);
        appendLog("🔁 Zugende angefragt.", resolvePlayerName(myPlayerId));
    });

    connect(ui->ServerButton, &QPushButton::clicked, this, [this]() {
        setConnectionStatus("Verbinde...", "#d17f00");
        network->connectToServer("127.0.0.1", 4242);
    });

    connect(ui->importCSVbutton, &QPushButton::clicked, this, [this]() {
        const QString path = QFileDialog::getOpenFileName(
            this, "Spiel-Log laden", QString(), "CSV-Dateien (*.csv)");
        if (path.isEmpty()) {
            return;
        }
        loadLogFromCsv(path);
        appendLog(QString("📂 Log geladen: %1").arg(path), "Client");
    });

    connect(ui->buyProperty, &QPushButton::clicked, this, [this]() {
        if (!ui->buyProperty->isEnabled()) {
            return;
        }
        network->sendBuyHouse();
        appendLog("🏠 Hauskauf angefragt.", resolvePlayerName(myPlayerId));
    });

    connect(ui->readyStartButton, &QPushButton::clicked, this, [this]() {
        localReady = !localReady;
        network->sendSetReady(localReady);
        ui->readyStartButton->setText(localReady ? "Bereit ✔" : "Bereit");
    });

    connect(ui->surrenderButton, &QPushButton::clicked, this, [this]() {
        network->sendSurrender();
        appendLog("🏳️ Du hast aufgegeben.", resolvePlayerName(myPlayerId));
    });

    connect(ui->saveCsvButton, &QPushButton::clicked, this, [this]() {
        const QString path = QFileDialog::getSaveFileName(
            this, "Spiel-Log speichern", QString(), "CSV-Dateien (*.csv)");
        if (path.isEmpty()) {
            return;
        }
        saveLogToCsv(path);
        appendLog(QString("💾 Log gespeichert: %1").arg(path), "Client");
    });

    connect(ui->playAgainButton, &QPushButton::clicked, this, [this]() {
        localReady = false;
        ui->readyStartButton->setText("Bereit");
        network->sendRestartGame();
        ui->stackedWidget->setCurrentWidget(ui->startView);
        ui->winnerLabel->setVisible(false);
        ui->logExitButton->setVisible(false);
        logViewActive = false;
        appendLog("🔄 Neustart angefragt.", resolvePlayerName(myPlayerId));
    });

    connect(ui->logExitButton, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->startView);
        ui->logExitButton->setVisible(false);
        logViewActive = false;
    });

    ui->surrenderButton->raise();
    ui->fieldInfoBox->raise();
    ui->winnerLabel->raise();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    network->sendStartGame();
    network->sendGetState();
}

void MainWindow::on_backButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->startView);
}

void MainWindow::on_buyButton_clicked()
{
    if (!ui->buyButton->isEnabled()) {
        return;
    }
    network->sendBuyDecision(true, myPlayerId, pendingBuyFieldIndex);
    pendingBuyFieldIndex = -1;
    setAwaitingBuyDecision(false);
    pendingEndTurnPlayerId = myPlayerId;
    setAwaitingEndTurn(true);
    ensureDiceEnabled(false);
    appendLog("✅ Kauf bestätigt.", resolvePlayerName(myPlayerId));
}

void MainWindow::on_sellButton_clicked()
{
    if (!ui->sellButton->isEnabled()) {
        return;
    }
    network->sendBuyDecision(false, myPlayerId, pendingBuyFieldIndex);
    pendingBuyFieldIndex = -1;
    setAwaitingBuyDecision(false);
    pendingEndTurnPlayerId = myPlayerId;
    setAwaitingEndTurn(true);
    ensureDiceEnabled(false);
    appendLog("❌ Kauf abgelehnt.", resolvePlayerName(myPlayerId));
}

void MainWindow::on_addPlayer_clicked()
{
    const QString name = ui->playerNameInput->text().trimmed();
    if (!name.isEmpty()) {
        network->sendSetName(name);
    }
}

void MainWindow::on_rollDiceButton_clicked()
{
    network->sendRollDice();
    appendLog("🎲 Würfeln angefragt.", resolvePlayerName(myPlayerId));
}

void MainWindow::appendLog(const QString &message, const QString &playerName)
{
    const QString name = playerName.isEmpty() ? QString("System") : playerName;
    const QDateTime timestamp = QDateTime::currentDateTime();
    logEntries.push_back({timestamp, name, message});
    const QString line = QString("[%1] %2: %3")
                             .arg(timestamp.toString("yyyy-MM-dd HH:mm:ss"))
                             .arg(name)
                             .arg(message);
    ui->textEdit_3->append(line);
}

void MainWindow::refreshLogView()
{
    ui->textEdit_3->clear();
    for (const auto &entry : logEntries) {
        const QString line = QString("[%1] %2: %3")
                                 .arg(entry.timestamp.toString("yyyy-MM-dd HH:mm:ss"))
                                 .arg(entry.playerName)
                                 .arg(entry.message);
        ui->textEdit_3->append(line);
    }
}

void MainWindow::saveLogToCsv(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        appendLog(QString("❌ Konnte CSV nicht speichern: %1").arg(filePath), "Client");
        return;
    }

    QTextStream out(&file);
    out << "timestamp;player;message\n";
    for (const auto &entry : logEntries) {
        out << entry.timestamp.toString(Qt::ISODate) << ";"
            << entry.playerName << ";"
            << entry.message << "\n";
    }
    if (!lastStateSnapshot.isEmpty()) {
        QJsonDocument doc(lastStateSnapshot);
        out << "state;;" << QString::fromUtf8(doc.toJson(QJsonDocument::Compact)) << "\n";
    }
}

void MainWindow::loadLogFromCsv(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        appendLog(QString("❌ Konnte CSV nicht laden: %1").arg(filePath), "Client");
        return;
    }

    QTextStream in(&file);
    QVector<LogEntry> loaded;
    QJsonObject loadedState;
    bool firstLine = true;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) {
            continue;
        }
        if (firstLine && line.startsWith("timestamp;")) {
            firstLine = false;
            continue;
        }
        firstLine = false;

        const QStringList parts = line.split(';');
        if (parts.size() < 3) {
            continue;
        }
        if (parts.at(0) == "state") {
            const QString jsonText = parts.mid(2).join(';');
            QJsonParseError err;
            const QJsonDocument doc = QJsonDocument::fromJson(jsonText.toUtf8(), &err);
            if (err.error == QJsonParseError::NoError && doc.isObject()) {
                loadedState = doc.object();
            }
            continue;
        }
        const QDateTime ts = QDateTime::fromString(parts.at(0), Qt::ISODate);
        const QString player = parts.at(1);
        const QString message = parts.mid(2).join(';');
        loaded.push_back({ts.isValid() ? ts : QDateTime::currentDateTime(), player, message});
    }

    logEntries = loaded;
    refreshLogView();
    if (!loadedState.isEmpty()) {
        lastStateSnapshot = loadedState;
        if (loadedState.value("type").toString() != "state") {
            loadedState["type"] = "state";
        }
        suppressWinViewOnce = true;
        logViewActive = true;
        ui->logExitButton->setVisible(true);
        emit network->jsonReceived(loadedState);
    }
}

QString MainWindow::resolvePlayerName(int playerId) const
{
    if (playerId <= 0) {
        return QString("Unbekannt");
    }
    return playerNames.value(playerId, QString("Spieler %1").arg(playerId));
}

void MainWindow::updateBoardHighlights()
{
    for (QWidget *field : boardFields) {
        QString style = fieldBaseStyles.value(field);
        const int index = boardFields.indexOf(field);
        if (fieldInfoByIndex.contains(index)) {
            const QJsonObject info = fieldInfoByIndex.value(index);
            const int ownerId = info.value("ownerId").toInt(-1);
            if (ownerId > 0) {
                QColor color = playerColors.value(ownerId, QColor());
                if (!color.isValid()) {
                    color = QColor::fromHsv((ownerId * 70) % 360, 200, 220);
                    playerColors.insert(ownerId, color);
                }
                style = ownershipStyle(style, color.name());
            }
        }
        field->setStyleSheet(style);
    }

    const int myPos = playerPositions.value(myPlayerId, -1);
    if (myPos >= 0 && myPos < boardFields.size()) {
        QWidget *field = boardFields.at(myPos);
        field->setStyleSheet(highlightStyle(field->styleSheet(), "#00cc44"));
    }

    if (currentPlayerId != myPlayerId) {
        const int currentPos = playerPositions.value(currentPlayerId, -1);
        if (currentPos >= 0 && currentPos < boardFields.size()) {
            QWidget *field = boardFields.at(currentPos);
            field->setStyleSheet(highlightStyle(field->styleSheet(), "#ffb300"));
        }
    }
}

void MainWindow::updatePlayerTokens()
{
    for (auto it = playerTokens.begin(); it != playerTokens.end(); ++it) {
        if (it.value()) {
            it.value()->hide();
        }
    }

    QMap<int, QVector<int>> playersByPos;
    for (auto it = playerPositions.cbegin(); it != playerPositions.cend(); ++it) {
        playersByPos[it.value()].append(it.key());
    }

    for (auto it = playersByPos.cbegin(); it != playersByPos.cend(); ++it) {
        const int pos = it.key();
        if (pos < 0 || pos >= boardFields.size()) {
            continue;
        }
        const QWidget *field = boardFields.at(pos);
        const QRect rect = field->geometry();
        const QVector<int> ids = it.value();

        for (int idx = 0; idx < ids.size(); ++idx) {
            const int playerId = ids.at(idx);
            QLabel *token = playerTokens.value(playerId, nullptr);
            if (!token) {
                token = new QLabel(ui->Brettspiel_2);
                token->setFixedSize(16, 16);
                QColor color = playerColors.value(playerId, QColor());
                if (!color.isValid()) {
                    color = QColor::fromHsv((playerId * 70) % 360, 200, 220);
                    playerColors.insert(playerId, color);
                }
                token->setStyleSheet(QString(
                    "background-color:%1;"
                    "border-radius:8px;"
                    "border:2px solid white;")
                                        .arg(color.name()));
                playerTokens.insert(playerId, token);
            }

            const int offset = 6;
            const int col = idx % 2;
            const int row = idx / 2;
            const int x = rect.x() + (rect.width() - token->width()) / 2 + col * offset;
            const int y = rect.y() + (rect.height() - token->height()) / 2 + row * offset;
            token->move(x, y);
            token->raise();
            token->show();
        }
    }
}

void MainWindow::updateFieldInfo(int index)
{
    if (!fieldInfoByIndex.contains(index)) {
        ui->fieldInfoValue->setText(QString("Feld %1").arg(index));
        return;
    }

    const QJsonObject info = fieldInfoByIndex.value(index);
    const QString name = info.value("name").toString(QString("Feld %1").arg(index));
    currentFieldName = name;
    const QString type = info.value("type").toString("field");
    const QString color = info.value("color").toString();
    const int price = info.value("price").toInt(-1);
    const int baseRent = info.value("baseRent").toInt(-1);
    const int ownerId = info.value("ownerId").toInt(-1);
    const QString ownerName = ownerId > 0 ? resolvePlayerName(ownerId) : QString("frei");

    QStringList lines;
    lines << name;
    if (!color.isEmpty()) {
        lines << QString("Farbe: %1").arg(color);
    }
    if (price >= 0) {
        lines << QString("Preis: %1$").arg(price);
    }
    if (baseRent >= 0) {
        lines << QString("Miete: %1$").arg(baseRent);
    }
    if (type == "property") {
        const QString subtype = info.value("subtype").toString();
        if (subtype == "street") {
            const int hotelPrice = info.value("hotelPrice").toInt(-1);
            const int hotelRent = info.value("hotelRent").toInt(-1);
            const bool hasHotel = info.value("hasHotel").toBool(false);
            if (hotelPrice >= 0) {
                lines << QString("Hauspreis: %1$").arg(hotelPrice);
            }
            if (hotelRent >= 0) {
                lines << QString("Miete mit Haus: %1$").arg(hotelRent);
            }
            lines << QString("Haus: %1").arg(hasHotel ? "ja" : "nein");
        }
    }
    lines << QString("Besitzer: %1").arg(ownerName);

    ui->fieldInfoValue->setText(lines.join("\n"));
}

void MainWindow::updateHouseBuyAvailability()
{
    const int myPos = playerPositions.value(myPlayerId, -1);
    if (myPos < 0) {
        ui->buyProperty->setEnabled(false);
        ui->buyProperty->setVisible(false);
        return;
    }

    const QJsonObject info = fieldInfoByIndex.value(myPos);
    const int ownerId = info.value("ownerId").toInt(-1);
    const QString subtype = info.value("subtype").toString();
    const bool hasHotel = info.value("hasHotel").toBool(false);
    const bool isStreet = subtype == "street";
    const bool isOwner = ownerId == myPlayerId;

    const bool canBuyHouse = isStreet && isOwner && !hasHotel && gameStarted;
    ui->buyProperty->setEnabled(canBuyHouse);
    ui->buyProperty->setVisible(canBuyHouse);
}

void MainWindow::updateHouseMarkers()
{
    for (auto it = houseMarkers.begin(); it != houseMarkers.end(); ++it) {
        if (it.value()) {
            it.value()->hide();
        }
    }

    for (auto it = fieldInfoByIndex.cbegin(); it != fieldInfoByIndex.cend(); ++it) {
        const int index = it.key();
        const QJsonObject info = it.value();
        const QString subtype = info.value("subtype").toString();
        const bool hasHotel = info.value("hasHotel").toBool(false);
        if (subtype != "street" || !hasHotel) {
            continue;
        }
        if (index < 0 || index >= boardFields.size()) {
            continue;
        }

        QLabel *marker = houseMarkers.value(index, nullptr);
        if (!marker) {
            marker = new QLabel(ui->Brettspiel_2);
            marker->setText("🏠");
            marker->setAlignment(Qt::AlignCenter);
            marker->setFixedSize(18, 18);
            marker->setStyleSheet("background-color:#ffffff; border-radius:9px; font-size:12px;");
            houseMarkers.insert(index, marker);
        }

        const QWidget *field = boardFields.at(index);
        const QRect rect = field->geometry();
        const int x = rect.x() + rect.width() - marker->width() - 4;
        const int y = rect.y() + 4;
        marker->move(x, y);
        marker->raise();
        marker->show();
    }
}

void MainWindow::setConnectionStatus(const QString &text, const QString &color)
{
    ui->ServerButton->setText(QString("Status: %1").arg(text));
    ui->ServerButton->setStyleSheet(QString(
        "QPushButton {"
        "border-width:3px;"
        "border-color:black;"
        "color:white;"
        "background-color:%1;"
        "}").arg(color));
}

void MainWindow::setAwaitingBuyDecision(bool awaiting)
{
    const bool canRespond = awaiting && pendingBuyPlayerId == myPlayerId;
    ui->buyButton->setEnabled(canRespond);
    ui->sellButton->setEnabled(canRespond);
    if (!awaiting) {
        pendingBuyFieldIndex = -1;
        pendingBuyPlayerId = -1;
    }
}

void MainWindow::setAwaitingEndTurn(bool awaiting)
{
    const bool canEndTurn = awaiting
        && pendingEndTurnPlayerId == myPlayerId
        && currentPlayerId == myPlayerId;
    ui->readyButton->setEnabled(canEndTurn);
}

void MainWindow::ensureDiceEnabled(bool enabled)
{
    ui->rollDiceButton->setEnabled(enabled);
}
