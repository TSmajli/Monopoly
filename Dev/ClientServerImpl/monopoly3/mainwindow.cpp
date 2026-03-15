#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "networkclient.h"

#include <QFile>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonObject>
#include <QPushButton>
#include <QSet>
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

QJsonObject filterArchivedStatePlayers(const QJsonObject &state, const QSet<QString> &allowedNames)
{
    if (state.isEmpty() || allowedNames.isEmpty() || !state.contains("players")) {
        return state;
    }

    QJsonObject filteredState = state;
    QJsonArray filteredPlayers;
    const QJsonArray players = state.value("players").toArray();
    for (const QJsonValue &value : players) {
        const QJsonObject player = value.toObject();
        const QString name = player.value("name").toString().trimmed();
        if (allowedNames.contains(name)) {
            filteredPlayers.push_back(player);
        }
    }
    filteredState["players"] = filteredPlayers;
    return filteredState;
}
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , network(new NetworkClient(this))
{
    ui->setupUi(this);

    ui->textEdit_3->setReadOnly(true);
    ui->textEdit_3->setAcceptRichText(true);
    ui->playersText->setReadOnly(true);
    ui->playersText->setAcceptRichText(true);

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


    updateReadyStartButtonAppearance();
    ui->rollDiceButton->setStyleSheet(buttonStyle("#469536", "#38772B"));
    ui->buyButton->setStyleSheet(buttonStyle("#275EA8", "#1e4b85"));
    ui->readyButton->setStyleSheet(buttonStyle("#252850", "#191970"));
    ui->buyProperty->setStyleSheet(buttonStyle("#252850", "#191970"));
    ui->surrenderButton->setStyleSheet(buttonStyle("#842d2d", "#6d2323"));
    ui->saveCsvButton->setStyleSheet(buttonStyle("#275EA8", "#1e4b85"));
    ui->playAgainButton->setStyleSheet(buttonStyle("#469536", "#38772B"));
    ui->logExitButton->setStyleSheet(buttonStyle("#842d2d", "#6d2323"));

    ui->readyButton->setEnabled(false);
    ui->buyButton->setEnabled(false);
    ui->rollDiceButton->setEnabled(false);
    ui->surrenderButton->setEnabled(true);

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
        field->installEventFilter(this);
        field->setCursor(Qt::PointingHandCursor);
    }

    playerColors.insert(1, QColor("#00cc44"));
    playerColors.insert(2, QColor("#ffb300"));
    playerColors.insert(3, QColor("#4dd0e1"));
    playerColors.insert(4, QColor("#ab47bc"));

    network->setReconnectEnabled(false);
    setConnectionStatus("Nicht verbunden", "#842d2d");
    ui->stackedWidget->setCurrentWidget(ui->startView);

    connect(network, &NetworkClient::connected, this, [this]() {
        setConnectionStatus("Verbunden", "#1b5e20");
        appendLog("Verbunden mit Server.", "Server");
        network->sendGetState();
    });

    connect(network, &NetworkClient::disconnected, this, [this]() {
        setConnectionStatus("Nicht verbunden", "#842d2d");
        ui->stackedWidget->setCurrentWidget(ui->startView);
        appendLog("Verbindung getrennt. Bitte erneut verbinden.", "Server");
    });

    connect(network, &NetworkClient::errorOccurred, this, [this](const QString &err) {
        setConnectionStatus("Nicht verbunden", "#842d2d");
        ui->stackedWidget->setCurrentWidget(ui->startView);
        appendLog(QString("Netzwerkfehler: %1").arg(err), "Server");
    });

    connect(network, &NetworkClient::jsonReceived, this, [this](const QJsonObject &obj) {
        const QString type = obj.value("type").toString();

        if (logViewActive && !applyingArchivedState && type == "state") {
            return;
        }

        if (type == "assignPlayerId") {
            myPlayerId = obj.value("playerId").toInt(-1);
            appendLog(QString("Verbunden als Spieler %1").arg(myPlayerId), "Server");
            network->sendGetState();
            return;
        }

        if (type == "info") {
            appendLog(QString("?? %1").arg(obj.value("message").toString()), "Server");
            return;
        }

        if (type == "error") {
            appendLog(QString("? %1").arg(obj.value("message").toString()), "Server");
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
            appendLog(QString("?? Kaufangebot: %1 (%2$)").arg(fieldName).arg(price), playerName);
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

            QString rollMessage = QString("[Wuerfel] %1 + %2 = %3").arg(d1).arg(d2).arg(steps);
            if (!fieldName.isEmpty()) {
                rollMessage += QString(" ? %1").arg(fieldName);
            }
            appendLog(rollMessage, playerName);
            if (!fieldName.isEmpty()) {
                currentFieldName = fieldName;
                ui->fieldInfoValue->setText(currentFieldName);
            }
            if (newPosition >= 0) {
                playerPositions.insert(playerId, newPosition);
                updatePlayerTokens();
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
            const bool wasGameStarted = gameStarted;
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
            QList<int> playerIdsForStart;
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
                if (id == myPlayerId) {
                    localReady = ready;
                }

                const QString readyMark = ready ? "(Bereit)" : "...";

                // Spieleruebersicht: einfache Karte wie im Design-Bild
                const bool bankrupt = p.value("bankrupt").toBool(false);
                const bool inJail   = p.value("inJail").toBool(false);
                const QColor pColor   = playerColors.value(id, QColor("#888888"));
                const QString colorHex = pColor.name();

                // Hintergrund: aktiver Spieler etwas heller
                const QString bg = (id == currentPlayerId) ? "#2a4a7f" : "#1e3a5f";

                // Extras als kleine Labels hinter dem Namen
                QString extras;
                if (id == myPlayerId)     extras += " <span style='color:#ffd700; font-size:10px;'>(Du)</span>";
                if (id == currentPlayerId) extras += " <span style='color:#ffffff; font-size:10px;'>&#9654;</span>";
                if (inJail)               extras += " <span style='color:#ff8a80; font-size:10px;'>&#128681;</span>";
                if (bankrupt)             extras += " <span style='color:#ff5252; font-size:11px; font-weight:bold;'>PLEITE</span>";

                const QString moneyColor = (money < 100) ? "#ff5252" : (money < 300 ? "#ffab40" : "#ffffff");

                // Eintrag: farbiges Quadrat | fetter Name | Extras | Geld rechts
                playerLines << QString(
                    "<table width='100%%' cellspacing='0' cellpadding='0' style='margin:3px 0;'>"
                    "<tr style='background:%1; border-radius:8px;'>"
                    "<td width='30' style='padding:7px 6px;'>"
                      "<div style='width:18px;height:18px;background:%2;border-radius:4px;'>&nbsp;</div>"
                    "</td>"
                    "<td style='padding:7px 4px; color:white; font-weight:bold; font-size:13px;'>"
                      "%3%4"
                    "</td>"
                    "<td align='right' style='padding:7px 10px; color:%5; font-size:13px; font-weight:bold; white-space:nowrap;'>"
                      "%6$"
                    "</td>"
                    "</tr>"
                    "</table>")
                    .arg(bg)
                    .arg(colorHex)
                    .arg(name.toHtmlEscaped())
                    .arg(extras)
                    .arg(moneyColor)
                    .arg(money);
                playerNamesForStart << name;
                playerReadyForStart << readyMark;
                playerIdsForStart << id;
            }

            if (gameStarted && (!wasGameStarted || historicalGamePlayers.isEmpty())) {
                historicalGamePlayers = playerNamesForStart;
            } else if (!gameStarted && !gameFinished && !logViewActive && !applyingArchivedState) {
                historicalGamePlayers.clear();
            }

            if (playerLines.isEmpty()) {
                ui->playersText->setHtml("<div style='color:#aaaaaa;'>Keine Spieler verbunden.</div>");
            } else {
                ui->playersText->setHtml(playerLines.join(""));
            }

            const QList<QPushButton *> startButtons = {
                ui->player1,
                ui->player2,
                ui->player3,
                ui->player4,
            };
            for (int i = 0; i < startButtons.size(); ++i) {
                if (i < playerNamesForStart.size()) {
                    const int pid = playerIdsForStart.value(i, -1);
                    const bool isMe = (pid == myPlayerId);
                    const QString meMark = isMe ? " (Du)" : "";
                    startButtons[i]->setText(QString("%1%2 %3")
                                                 .arg(playerNamesForStart.at(i))
                                                 .arg(meMark)
                                                 .arg(playerReadyForStart.value(i)));
                    startButtons[i]->setVisible(true);

                    // Spielerfarbe als linke Border anzeigen
                    QColor pColor = playerColors.value(pid, QColor("#555555"));
                    QString borderColor = pColor.name();
                    QString bgColor = isMe ? "#2a3a50" : "#1e2d3d";
                    startButtons[i]->setStyleSheet(QString(
                        "QPushButton {"
                        "border-left:5px solid %1;"
                        "border-radius:8px;"
                        "background-color:%2;"
                        "color:white;"
                        "font-weight:%3;"
                        "text-align:left;"
                        "padding-left:8px;"
                        "}"
                        "QPushButton:hover { background-color:#2e4060; }")
                        .arg(borderColor)
                        .arg(bgColor)
                        .arg(isMe ? "bold" : "normal"));
                } else {
                    startButtons[i]->setText(QString("Spieler %1").arg(i + 1));
                    startButtons[i]->setVisible(false);
                }
            }

            const bool allReady = !players.isEmpty() && readyCount == players.size();
            ui->readyStartButton->setEnabled(!gameStarted);
            updateReadyStartButtonAppearance();

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
                    const QString winName = resolvePlayerName(winnerId);
                    const QString winColor = playerColors.value(winnerId, QColor("#FFD700")).name();
                    ui->winWinnerLabel->setText(QString("Gewinner: %1").arg(winName));
                    ui->winWinnerLabel->setStyleSheet(QString(
                        "color:%1; font-size:28px; font-weight:bold;").arg(winColor));
                } else {
                    ui->winWinnerLabel->setText("Kein Gewinner");
                    ui->winWinnerLabel->setStyleSheet("color:#aaaaaa; font-size:22px;");
                }
                ui->stackedWidget->setCurrentWidget(ui->winView);
            } else if (gameStarted) {
                ui->stackedWidget->setCurrentWidget(ui->gameView);
            } else {
                ui->stackedWidget->setCurrentWidget(ui->startView);
            }
            ui->winnerLabel->setVisible(false);

            // CSV-View: alle Interaktions-Buttons deaktivieren
            if (logViewActive) {
                ensureDiceEnabled(false);
                ui->readyButton->setEnabled(false);
                ui->buyButton->setEnabled(false);
                ui->buyProperty->setEnabled(false);
                ui->buyProperty->setVisible(false);
                ui->readyStartButton->setEnabled(false);
                ui->surrenderButton->setEnabled(false);
            }
        }
    });

    connect(ui->readyButton, &QPushButton::clicked, this, [this]() {
        if (!ui->readyButton->isEnabled()) {
            return;
        }
        network->sendEndTurn();
        setAwaitingEndTurn(false);
        appendLog("?? Zugende angefragt.", resolvePlayerName(myPlayerId));
    });

    connect(ui->ServerButton, &QPushButton::clicked, this, [this]() {
        network->setReconnectEnabled(false);
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
        appendLog(QString("?? Log geladen: %1").arg(path), "Client");
    });

    connect(ui->buyProperty, &QPushButton::clicked, this, [this]() {
        if (!ui->buyProperty->isEnabled() || pendingHouseFieldIndex < 0) {
            return;
        }
        network->sendBuyHouse(pendingHouseFieldIndex);
        appendLog("Haus gekauft.", resolvePlayerName(myPlayerId));
        ui->buyProperty->setEnabled(false);
        ui->buyProperty->setVisible(false);
    });

    connect(ui->readyStartButton, &QPushButton::clicked, this, [this]() {
        localReady = !localReady;
        network->sendSetReady(localReady);
        updateReadyStartButtonAppearance();
    });

    connect(ui->surrenderButton, &QPushButton::clicked, this, [this]() {
        network->sendSurrender();
        appendLog("??? Du hast aufgegeben.", resolvePlayerName(myPlayerId));
    });

    connect(ui->saveCsvButton, &QPushButton::clicked, this, [this]() {
        const QString path = QFileDialog::getSaveFileName(
            this, "Spiel-Log speichern", QString(), "CSV-Dateien (*.csv)");
        if (path.isEmpty()) {
            return;
        }
        saveLogToCsv(path);
        appendLog(QString("?? Log gespeichert: %1").arg(path), "Client");
    });

    connect(ui->playAgainButton, &QPushButton::clicked, this, [this]() {
        localReady = false;
        logViewActive = false;
        historicalGamePlayers.clear();
        gameFinished = false;
        winnerId = -1;
        suppressWinViewOnce = true;
        ui->readyStartButton->setEnabled(true);
        updateReadyStartButtonAppearance();
        ui->stackedWidget->setCurrentWidget(ui->startView);
        ui->winnerLabel->setVisible(false);
        ui->logExitButton->setVisible(false);
        network->sendRestartGame();
        appendLog("----------------------------", "System");
        appendLog("Neustart - neues Spiel beginnt.", resolvePlayerName(myPlayerId));
    });

    connect(ui->logExitButton, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->startView);
        ui->logExitButton->setVisible(false);
        logViewActive = false;
        localReady = false;
        ui->readyStartButton->setEnabled(true);
        updateReadyStartButtonAppearance();
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
    appendLog("Kauf bestaetigt.", resolvePlayerName(myPlayerId));
}

void MainWindow::on_sellButton_clicked()
{
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
    appendLog("Wuerfeln angefragt.", resolvePlayerName(myPlayerId));
}

// Gibt die Spielerfarbe fuer einen Namen zurueck (Fallback: grau)
QString MainWindow::colorForPlayerName(const QString &name) const
{
    for (auto it = playerNames.constBegin(); it != playerNames.constEnd(); ++it) {
        if (it.value() == name) {
            QColor c = playerColors.value(it.key(), QColor("#888888"));
            return c.name();
        }
    }
    return QStringLiteral("#888888");
}

// Gibt die passende Nachrichtenfarbe zurueck (fuer dezente Einfaerbung der Nachricht)
static QString msgColor(const QString &msg)
{
    if (msg.contains("Wuerfelwurf"))          return "#a8d8a8"; // hellgruen
    if (msg.contains("kauft") || msg.contains("Kaufangebot")) return "#a8c4e8"; // hellblau
    if (msg.contains("Haus") || msg.contains("Hotel"))        return "#ffe082"; // gelb
    if (msg.contains("Gefaengnis") || msg.contains("pleite")) return "#ef9a9a"; // hellrot
    if (msg.contains("Unterrichtskarte"))    return "#ffcc80"; // orange
    if (msg.contains("gewinnt"))             return "#fff176"; // gold
    return "#dddddd"; // standard
}

// Gibt eine Log-Zeile als HTML zurueck (ein inline Span - append() fuegt den Zeilenumbruch hinzu)
QString MainWindow::logEntryToHtml(const LogEntry &entry) const
{
    const QString timeStr = entry.timestamp.toString("HH:mm:ss");

    QString nameColor = "#888888";
    if (entry.playerName == "Server" || entry.playerName == "System") {
        nameColor = "#777777";
    } else if (entry.playerName == "Client") {
        nameColor = "#888888";
    } else {
        nameColor = colorForPlayerName(entry.playerName);
    }

    const QString mc = msgColor(entry.message);

    // Einfache Zeile: [Zeit] Name: Nachricht
    return QString(
        "<span style='color:#666666;'>[%1]</span>"
        " <b style='color:%2;'>%3</b>"
        "<span style='color:#bbbbbb;'>: </span>"
        "<span style='color:%4;'>%5</span>")
        .arg(timeStr)
        .arg(nameColor)
        .arg(entry.playerName.toHtmlEscaped())
        .arg(mc)
        .arg(entry.message.toHtmlEscaped());
}

void MainWindow::appendLog(const QString &message, const QString &playerName)
{
    const QString name = playerName.isEmpty() ? QString("System") : playerName;
    const QDateTime timestamp = QDateTime::currentDateTime();
    logEntries.push_back({timestamp, name, message});
    // append() fuegt automatisch einen Zeilenumbruch hinzu - saubere Trennung
    ui->textEdit_3->append(logEntryToHtml(logEntries.back()));
}

void MainWindow::refreshLogView()
{
    ui->textEdit_3->clear();
    for (const auto &entry : logEntries) {
        ui->textEdit_3->append(logEntryToHtml(entry));
    }
}

void MainWindow::saveLogToCsv(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        appendLog(QString("? Konnte CSV nicht speichern: %1").arg(filePath), "Client");
        return;
    }

    QTextStream out(&file);
    const QStringList archivedPlayers = historicalGamePlayers;
    out << "timestamp;player;message\n";
    for (const auto &entry : logEntries) {
        out << entry.timestamp.toString(Qt::ISODate) << ";"
            << entry.playerName << ";"
            << entry.message << "\n";
    }
    if (!lastStateSnapshot.isEmpty()) {
        QSet<QString> allowedNames;
        for (const QString &name : archivedPlayers) {
            if (!name.trimmed().isEmpty()) {
                allowedNames.insert(name.trimmed());
            }
        }
        QJsonObject filteredState = filterArchivedStatePlayers(lastStateSnapshot, allowedNames);
        if (!archivedPlayers.isEmpty()) {
            QJsonArray archivedPlayersArray;
            for (const QString &name : archivedPlayers) {
                archivedPlayersArray.push_back(name);
            }
            filteredState["archivedPlayers"] = archivedPlayersArray;
        }
        QJsonDocument doc(filteredState);
        out << "state;;" << QString::fromUtf8(doc.toJson(QJsonDocument::Compact)) << "\n";
    }
}

void MainWindow::loadLogFromCsv(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        appendLog(QString("? Konnte CSV nicht laden: %1").arg(filePath), "Client");
        return;
    }

    QTextStream in(&file);
    QVector<LogEntry> loaded;
    QJsonObject loadedState;
    QStringList archivedPlayerNames;
    const auto collectArchivedPlayerName = [&archivedPlayerNames](const QString &name) {
        if (!name.isEmpty() && name != "Server" && name != "Client" && name != "System"
            && !archivedPlayerNames.contains(name)) {
            archivedPlayerNames.push_back(name);
        }
    };
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
        const QString player = parts.at(1).trimmed();
        const QString message = parts.mid(2).join(';');
        loaded.push_back({ts.isValid() ? ts : QDateTime::currentDateTime(), player, message});
        collectArchivedPlayerName(player);
    }

    if (!loadedState.isEmpty()) {
        QSet<QString> allowedNames;
        const QJsonArray archivedPlayersArray = loadedState.value("archivedPlayers").toArray();
        for (const QJsonValue &value : archivedPlayersArray) {
            const QString name = value.toString().trimmed();
            if (!name.isEmpty()) {
                allowedNames.insert(name);
                collectArchivedPlayerName(name);
            }
        }
        if (allowedNames.isEmpty()) {
            for (const LogEntry &entry : loaded) {
                const QString name = entry.playerName.trimmed();
                if (name.isEmpty() || name == "Server" || name == "Client" || name == "System") {
                    continue;
                }
                allowedNames.insert(name);
            }
        }
        loadedState = filterArchivedStatePlayers(loadedState, allowedNames);
        const QJsonArray archivedPlayers = loadedState.value("players").toArray();
        for (const QJsonValue &value : archivedPlayers) {
            const QString name = value.toObject().value("name").toString().trimmed();
            collectArchivedPlayerName(name);
        }
    }

    logEntries = loaded;
    refreshLogView();
    logViewActive = true;
    ui->logExitButton->setVisible(true);
    applyArchivedPlayerNames(archivedPlayerNames);

    if (!loadedState.isEmpty()) {
        lastStateSnapshot = loadedState;
        if (loadedState.value("type").toString() != "state") {
            loadedState["type"] = "state";
        }
        suppressWinViewOnce = true;
        applyingArchivedState = true;
        emit network->jsonReceived(loadedState);
        applyingArchivedState = false;
        applyArchivedPlayerNames(archivedPlayerNames);
    }
}

void MainWindow::applyArchivedPlayerNames(const QStringList &names)
{
    playerNames.clear();
    playerPositions.clear();

    QStringList playerLines;
    const QList<QPushButton *> startButtons = {
        ui->player1,
        ui->player2,
        ui->player3,
        ui->player4,
    };

    for (int i = 0; i < startButtons.size(); ++i) {
        if (i < names.size()) {
            const int playerId = i + 1;
            const QString name = names.at(i);
            playerNames.insert(playerId, name);
            playerLines << QString(
                "<table width='100%%' cellspacing='0' cellpadding='0' style='margin:3px 0;'>"
                "<tr style='background:#1e3a5f; border-radius:8px;'>"
                "<td width='30' style='padding:7px 6px;'>"
                  "<div style='width:18px;height:18px;background:%1;border-radius:4px;'>&nbsp;</div>"
                "</td>"
                "<td style='padding:7px 4px; color:white; font-weight:bold; font-size:13px;'>"
                  "%2"
                "</td>"
                "<td align='right' style='padding:7px 10px; color:#aaaaaa; font-size:13px; font-weight:bold; white-space:nowrap;'>"
                  "Archiv"
                "</td>"
                "</tr>"
                "</table>")
                .arg(playerColors.value(playerId, QColor("#888888")).name())
                .arg(name.toHtmlEscaped());

            startButtons[i]->setText(QString("%1 Archiv").arg(name));
            startButtons[i]->setVisible(true);
            startButtons[i]->setStyleSheet(QString(
                "QPushButton {"
                "border-left:5px solid %1;"
                "border-radius:8px;"
                "background-color:#1e2d3d;"
                "color:white;"
                "font-weight:normal;"
                "text-align:left;"
                "padding-left:8px;"
                "}"
                "QPushButton:hover { background-color:#1e2d3d; }")
                .arg(playerColors.value(playerId, QColor("#555555")).name()));
        } else {
            startButtons[i]->setText(QString("Spieler %1").arg(i + 1));
            startButtons[i]->setVisible(false);
        }
    }

    if (playerLines.isEmpty()) {
        ui->playersText->setHtml("<div style='color:#aaaaaa;'>Keine Spielernamen in der CSV gefunden.</div>");
    } else {
        ui->playersText->setHtml(playerLines.join(""));
    }

    ui->stackedWidget->setCurrentWidget(ui->gameView);
    ensureDiceEnabled(false);
    ui->readyButton->setEnabled(false);
    ui->buyButton->setEnabled(false);
    ui->buyProperty->setEnabled(false);
    ui->buyProperty->setVisible(false);
    ui->readyStartButton->setEnabled(false);
    ui->surrenderButton->setEnabled(false);
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

    // Meine aktuelle Position: mit meiner Spielerfarbe umranden
    const int myPos = playerPositions.value(myPlayerId, -1);
    if (myPos >= 0 && myPos < boardFields.size()) {
        QColor myColor = playerColors.value(myPlayerId, QColor("#00cc44"));
        QWidget *field = boardFields.at(myPos);
        field->setStyleSheet(highlightStyle(field->styleSheet(), myColor.name()));
    }

    // Position des aktiven Spielers (falls nicht ich): mit DESSEN Farbe umranden
    if (currentPlayerId != myPlayerId) {
        const int currentPos = playerPositions.value(currentPlayerId, -1);
        if (currentPos >= 0 && currentPos < boardFields.size()) {
            QColor theirColor = playerColors.value(currentPlayerId, QColor("#ffb300"));
            QWidget *field = boardFields.at(currentPos);
            field->setStyleSheet(highlightStyle(field->styleSheet(), theirColor.name()));
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

    if (type == "card") {
        lines << "[Unterrichtskarte]";
        lines << "Ziehe eine Karte!";
    } else if (type == "gotojail") {
        lines << "Gehe direkt in die";
        lines << "Berufsschule!";
    } else if (type == "tax") {
        if (price > 0) {
            lines << QString("Steuer: %1$").arg(price);
        }
    } else if (type == "jail") {
        lines << "Nur zu Besuch";
    } else if (type == "start") {
        lines << "Start: +200$ Bonus";
    }

    if (!color.isEmpty()) {
        lines << QString("Farbe: %1").arg(color);
    }
    if (price >= 0 && type == "property") {
        lines << QString("Preis: %1$").arg(price);
    }
    if (type == "property") {
        const QString subtype = info.value("subtype").toString();
        if (subtype == "utility") {
            lines << "Miete: Wuerfel x 4";
        } else if (baseRent >= 0) {
            lines << QString("Miete: %1$").arg(baseRent);
        }
        if (subtype == "street") {
            const int hotelPrice = info.value("hotelPrice").toInt(-1);
            const int hotelRent = info.value("hotelRent").toInt(-1);
            const bool hasHotel = info.value("hasHotel").toBool(false);
            if (hasHotel) {
                lines << QString("Haus: JA  (+%1$ Miete)").arg(hotelRent >= 0 ? hotelRent : 0);
            } else {
                if (hotelPrice >= 0) {
                    lines << QString("Haus kaufen: %1$").arg(hotelPrice);
                }
                lines << "Haus: nein";
            }
        }
        lines << QString("Besitzer: %1").arg(ownerName);
    }

    ui->fieldInfoValue->setText(lines.join("\n"));
}

void MainWindow::updateHouseBuyAvailability()
{
    pendingHouseFieldIndex = -1;

    const int myPos = playerPositions.value(myPlayerId, -1);
    if (myPos < 0 || !gameStarted) {
        ui->buyProperty->setEnabled(false);
        ui->buyProperty->setVisible(false);
        return;
    }

    const QJsonObject &info = fieldInfoByIndex.value(myPos);
    const bool isStreet  = info.value("subtype").toString() == "street";
    const bool isOwner   = info.value("ownerId").toInt(-1) == myPlayerId;
    const bool hasHotel  = info.value("hasHotel").toBool(false);
    const bool isMyTurn  = currentPlayerId == myPlayerId;

    const bool canBuy = isStreet && isOwner && !hasHotel && isMyTurn;
    ui->buyProperty->setVisible(canBuy);
    ui->buyProperty->setEnabled(canBuy);

    if (canBuy) {
        pendingHouseFieldIndex = myPos;
        ui->buyProperty->setText("Haus kaufen (200$)");
        ui->buyProperty->setStyleSheet(buttonStyle("#2e7d32", "#1b5e20"));
    }
}

void MainWindow::updateReadyStartButtonAppearance()
{
    ui->readyStartButton->setText(localReady ? "Nicht Bereit" : "Bereit");
    if (localReady) {
        ui->readyStartButton->setStyleSheet(buttonStyle("#c94f4f", "#b53f3f"));
    } else {
        ui->readyStartButton->setStyleSheet(buttonStyle("#469536", "#38772B"));
    }
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

        // Besitzerfarbe fuer den Haus-Marker ermitteln
        const int ownerId = info.value("ownerId").toInt(-1);
        QColor ownerColor = playerColors.value(ownerId, QColor("#2e7d32"));
        // Randfarbe: etwas hellere Version der Besitzerfarbe
        QColor borderColor = ownerColor.lighter(160);

        QLabel *marker = houseMarkers.value(index, nullptr);
        if (!marker) {
            marker = new QLabel(ui->Brettspiel_2);
            marker->setAlignment(Qt::AlignCenter);
            marker->setFixedSize(22, 22);
            houseMarkers.insert(index, marker);
        }
        // Stil immer aktualisieren (Besitzer kann sich aendern)
        marker->setText("H");
        marker->setStyleSheet(QString(
            "background-color:%1;"
            "color:#ffffff;"
            "font-weight:bold;"
            "font-size:12px;"
            "border-radius:5px;"
            "border:2px solid %2;")
            .arg(ownerColor.name())
            .arg(borderColor.name()));

        const QWidget *field = boardFields.at(index);
        const QRect rect = field->geometry();
        const int x = rect.x() + rect.width() - marker->width() - 2;
        const int y = rect.y() + 2;
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
    awaitingBuyDecisionLocal = awaiting && pendingBuyPlayerId == myPlayerId;
    ui->buyButton->setEnabled(awaitingBuyDecisionLocal);
    if (!awaiting) {
        pendingBuyFieldIndex = -1;
        pendingBuyPlayerId = -1;
    }
}

void MainWindow::setAwaitingEndTurn(bool awaiting)
{
    const bool canEndTurn = (awaiting
        && pendingEndTurnPlayerId == myPlayerId
        && currentPlayerId == myPlayerId)
        || awaitingBuyDecisionLocal;
    ui->readyButton->setEnabled(canEndTurn);
}

void MainWindow::ensureDiceEnabled(bool enabled)
{
    ui->rollDiceButton->setEnabled(enabled);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QWidget *w = qobject_cast<QWidget*>(watched);
        if (w) {
            const int idx = boardFields.indexOf(w);
            if (idx >= 0) {
                updateFieldInfo(idx);
                return true;
            }
        }
    }
    return QMainWindow::eventFilter(watched, event);
}






