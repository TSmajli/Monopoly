#include "gameserver.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QRandomGenerator>
#include <algorithm>

// Fields
#include "startfield.h"
#include "streetfield.h"
#include "railroadfield.h"
#include "utilityfield.h"
#include "taxfield.h"
#include "jailfield.h"
#include "propertyfield.h"

GameServer::GameServer(QObject *parent)
    : QObject(parent)
{
    connect(&server, &QTcpServer::newConnection,
            this, &GameServer::onNewConnection);
}

void GameServer::startServer(quint16 port)
{
    if (!server.listen(QHostAddress::Any, port)) {
        qWarning() << "[SERVER] konnte nicht starten:" << server.errorString();
        return;
    }
    qDebug() << "[SERVER] läuft auf Port" << port;
}

void GameServer::onNewConnection()
{
    while (server.hasPendingConnections()) {
        QTcpSocket* client = server.nextPendingConnection();
        if (!client) continue;

        auto player = std::make_unique<Player>();
        player->id = nextPlayerId++;
        player->socket = client;
        player->name = QString("Player%1").arg(player->id);

        players.push_back(std::move(player));
        game.addPlayer(players.back().get());

        recvBuffers.insert(client, QByteArray());

        connect(client, &QTcpSocket::readyRead,
                this, &GameServer::onReadyRead);
        connect(client, &QTcpSocket::disconnected,
                this, &GameServer::onClientDisconnected);

        initBoardIfNeeded();

        // Assign ID
        QJsonObject msg;
        msg["type"] = "assignPlayerId";
        msg["playerId"] = players.back()->id;
        msg["name"] = players.back()->name;
        sendToSocket(client, msg);

        qDebug() << "[NET] Neuer Client:" << players.back()->name
                 << "| players=" << players.size();

        // State an alle
        broadcastGameState("playerJoined");
    }
}

void GameServer::onReadyRead()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;

    Player *playerPtr = findPlayerBySocket(socket);
    if (!playerPtr) return;

    // newline-delimited JSON
    recvBuffers[socket].append(socket->readAll());
    auto &buf = recvBuffers[socket];

    while (true) {
        int nl = buf.indexOf('\n');
        if (nl < 0) break;

        QByteArray line = buf.left(nl);
        buf.remove(0, nl + 1);

        line = line.trimmed();
        if (line.isEmpty()) continue;

        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(line, &err);
        if (err.error != QJsonParseError::NoError || !doc.isObject()) {
            qWarning() << "[NET] JSON parse error:" << err.errorString()
            << "raw=" << line;
            continue;
        }

        qDebug() << "[NET] <= from" << playerPtr->name << line;
        processMessage(*playerPtr, doc.object());
    }
}

void GameServer::processMessage(Player &player, const QJsonObject &msg)
{
    const QString type = msg.value("type").toString();

    if (type == "startGame") {
        handleStartGame(player);
        return;
    }

    if (type == "rollDice") {
        handleRollDice(player);
        return;
    }

    if (type == "endTurn") {
        handleEndTurn(player);
        return;
    }

    if (type == "surrender") {
        handleSurrender(player);
        return;
    }

    if (type == "setReady") {
        const bool ready = msg.value("ready").toBool(true);
        handleSetReady(player, ready);
        return;
    }

    if (type == "setName") {
        const QString name = msg.value("name").toString().trimmed();
        handleSetName(player, name);
        return;
    }

    if (type == "restartGame") {
        handleRestartGame(player);
        return;
    }

    if (type == "buyHouse") {
        handleBuyHouse(player);
        return;
    }

    if (type == "buyDecision") {
        const int pid = msg.value("playerId").toInt();
        const int fieldIndex = msg.value("fieldIndex").toInt();
        const bool buy = msg.value("buy").toBool(false);

        qDebug() << "[BUY] decision from pid=" << pid
                 << "field=" << fieldIndex
                 << "buy=" << buy;

        if (!awaitingBuyDecision ||
            pid != pendingBuyPlayerId ||
            fieldIndex != pendingBuyFieldIndex) {
            qWarning() << "[BUY] Ignored (not pending / mismatch). pending pid="
                       << pendingBuyPlayerId << "field=" << pendingBuyFieldIndex;
            return;
        }

        Player *p = findPlayerById(pid);
        Field *f = board.getField(fieldIndex);
        auto *pf = dynamic_cast<PropertyField*>(f);

        if (p && pf && pf->owner == nullptr) {
            if (buy) {
                qDebug() << "[BUY] Player" << p->id << "buys" << pf->name
                         << "for" << pf->price << "(money before=" << p->money << ")";
                pf->buy(*p);
                qDebug() << "[BUY] money after=" << p->money;
                broadcastLog(p->id, QString("kauft %1 für %2$")
                                       .arg(pf->name)
                                       .arg(pf->price));
            } else {
                qDebug() << "[BUY] Player" << p->id << "declined" << pf->name;
                broadcastLog(p->id, QString("lehnt den Kauf von %1 ab")
                                       .arg(pf->name));
            }
        } else {
            qWarning() << "[BUY] Invalid buy target or player not found.";
        }

        awaitingBuyDecision = false;
        pendingBuyPlayerId = -1;
        pendingBuyFieldIndex = -1;

        awaitingEndTurn = true;
        pendingEndTurnPlayerId = pid;

        broadcastGameState("buyResolved");
        broadcastGameState("awaitingEndTurn");
        return;
    }

    if (type == "getState") {
        sendToPlayer(player, buildGameState("getState"));
        return;
    }

    qWarning() << "[NET] Unknown type:" << type;
}

void GameServer::handleStartGame(Player &player)
{
    if (gameStarted) {
        qDebug() << "[GAME] startGame ignored (already started)";
        QJsonObject info;
        info["type"] = "info";
        info["message"] = "Game already started.";
        sendToPlayer(player, info);
        return;
    }

    // Mindestspieler (ändere auf 1 wenn du solo willst)
    if (players.size() < 2) {
        qDebug() << "[GAME] startGame blocked (need 2 players), have" << players.size();
        QJsonObject err;
        err["type"] = "error";
        err["message"] = "Mindestens 2 Spieler nötig um zu starten.";
        sendToPlayer(player, err);
        return;
    }

    if (!areAllPlayersReady()) {
        QJsonObject err;
        err["type"] = "error";
        err["message"] = "Alle Spieler müssen bereit sein, bevor das Spiel startet.";
        sendToPlayer(player, err);
        return;
    }

    gameStarted = true;
    gameFinished = false;
    winnerId = -1;
    qDebug() << "[GAME] STARTED by" << player.name
             << "| currentPlayerId=" << (game.getCurrentPlayer() ? game.getCurrentPlayer()->id : -1);

    broadcastLog(player.id, "startet das Spiel");
    broadcastGameState("gameStarted");
}

void GameServer::handleSetReady(Player &player, bool ready)
{
    player.isReady = ready;
    broadcastLog(player.id, ready ? "ist bereit" : "ist nicht mehr bereit");
    broadcastGameState("playerReady");

    if (!gameStarted && areAllPlayersReady()) {
        handleStartGame(player);
    }
}

void GameServer::handleSetName(Player &player, const QString &name)
{
    if (name.isEmpty()) {
        return;
    }
    player.name = name.left(20);
    broadcastLog(player.id, QString("heißt jetzt %1").arg(player.name));
    broadcastGameState("playerName");
}

void GameServer::handleRestartGame(Player &player)
{
    gameStarted = false;
    gameFinished = false;
    winnerId = -1;
    awaitingBuyDecision = false;
    pendingBuyPlayerId = -1;
    pendingBuyFieldIndex = -1;
    awaitingEndTurn = false;
    pendingEndTurnPlayerId = -1;

    boardInitialized = false;
    initBoardIfNeeded();

    for (const auto &p : players) {
        if (!p) {
            continue;
        }
        p->position = 0;
        p->money = 1500;
        p->isBankrupt = false;
        p->inJail = false;
        p->jailTurns = 0;
        p->properties.clear();
        p->isReady = false;
    }

    game.resetTurnOrder();

    broadcastLog(player.id, "startet einen Neustart");
    broadcastGameState("gameRestarted");
}

void GameServer::handleBuyHouse(Player &player)
{
    if (!gameStarted || gameFinished) {
        QJsonObject err;
        err["type"] = "error";
        err["message"] = "Hauskauf ist nur während eines laufenden Spiels möglich.";
        sendToPlayer(player, err);
        return;
    }

    if (awaitingBuyDecision) {
        QJsonObject err;
        err["type"] = "error";
        err["message"] = "Warte auf Kaufentscheidung. Hauskauf derzeit gesperrt.";
        sendToPlayer(player, err);
        return;
    }

    Player *current = game.getCurrentPlayer();
    if (!current || current->id != player.id) {
        QJsonObject err;
        err["type"] = "error";
        err["message"] = "Du bist nicht dran.";
        sendToPlayer(player, err);
        return;
    }

    Field *f = board.getField(player.position);
    auto *sf = dynamic_cast<StreetField*>(f);
    if (!sf || sf->owner != &player) {
        QJsonObject err;
        err["type"] = "error";
        err["message"] = "Hauskauf nur auf eigener Straße möglich.";
        sendToPlayer(player, err);
        return;
    }

    if (sf->hasHotel) {
        QJsonObject err;
        err["type"] = "error";
        err["message"] = "Es steht bereits ein Haus.";
        sendToPlayer(player, err);
        return;
    }

    if (player.money < sf->hotelPrice) {
        QJsonObject err;
        err["type"] = "error";
        err["message"] = "Nicht genug Geld für ein Haus.";
        sendToPlayer(player, err);
        return;
    }

    sf->buyHotel(player);
    broadcastLog(player.id, QString("kauft ein Haus auf %1 für %2$")
                               .arg(sf->name)
                               .arg(sf->hotelPrice));
    broadcastGameState("houseBought");
}

void GameServer::handleRollDice(Player &player)
{
    initBoardIfNeeded();

    if (gameFinished) {
        QJsonObject err;
        err["type"] = "error";
        err["message"] = "Spiel ist bereits beendet.";
        sendToPlayer(player, err);
        return;
    }

    if (!gameStarted) {
        qDebug() << "[TURN] rollDice blocked - game not started";
        QJsonObject err;
        err["type"] = "error";
        err["message"] = "Spiel ist noch nicht gestartet. Sende {\"type\":\"startGame\"}.";
        sendToPlayer(player, err);
        return;
    }

    if (awaitingEndTurn) {
        qDebug() << "[TURN] rollDice blocked - awaiting endTurn";
        QJsonObject err;
        err["type"] = "error";
        err["message"] = "Bitte zuerst den Zug beenden.";
        sendToPlayer(player, err);
        return;
    }

    if (awaitingBuyDecision) {
        qDebug() << "[TURN] rollDice blocked - waiting for buyDecision";
        QJsonObject err;
        err["type"] = "error";
        err["message"] = "Warte auf Kaufentscheidung. Erst buyDecision senden.";
        sendToPlayer(player, err);
        return;
    }

    Player *current = game.getCurrentPlayer();

    if (!current) return;

    if (current->id != player.id) {
        qDebug() << "[TURN] rollDice blocked - not your turn"
                 << "| current=" << current->id
                 << "| you=" << player.id;
        QJsonObject err;
        err["type"] = "error";
        err["message"] = "Du bist nicht dran.";
        sendToPlayer(player, err);
        return;
    }

    // Minimal Jail-Wartezug (falls du jail benutzt)
    if (current->inJail) {
        current->jailTurns--;
        qDebug() << "[JAIL] Player" << current->id << "waits. remaining=" << current->jailTurns;

        if (current->jailTurns <= 0) {
            current->inJail = false;
            current->jailTurns = 0;
            qDebug() << "[JAIL] Player" << current->id << "released.";
        }

        broadcastGameState("jailWait");
        awaitingEndTurn = true;
        pendingEndTurnPlayerId = current->id;
        broadcastGameState("awaitingEndTurn");
        return;
    }

    int d1 = int(QRandomGenerator::global()->bounded(1, 7));
    int d2 = int(QRandomGenerator::global()->bounded(1, 7));
    int steps = d1 + d2;

    const int oldPos = current->position;
    const int oldMoney = current->money;

    current->move(steps);

    Field *f = board.getField(current->position);

    qDebug() << "[TURN] Player" << current->id
             << "rolled" << d1 << "+" << d2 << "=" << steps
             << "| pos" << oldPos << "->" << current->position
             << "| money" << oldMoney << "->" << current->money
             << "| field=" << (f ? f->name : QString("<null>"));

    // Utility: lastDiceRoll setzen, bevor onLand Miete berechnet
    if (auto *uf = dynamic_cast<UtilityField*>(f)) {
        uf->lastDiceRoll = steps;
        qDebug() << "[FIELD] Utility lastDiceRoll set to" << steps;
    }

    // Würfel-Event an alle
    QJsonObject roll;
    roll["type"] = "diceRolled";
    roll["playerId"] = current->id;
    roll["d1"] = d1;
    roll["d2"] = d2;
    roll["steps"] = steps;
    roll["newPosition"] = current->position;
    roll["fieldName"] = f ? f->name : QString();
    broadcast(roll);

    // Feld auswerten (Miete/Steuer etc. passiert in deinen Field-Klassen)
    if (f) {
        const int before = current->money;
        qDebug() << "[FIELD] onLand ->" << f->index << f->name
                 << "| playerMoneyBefore=" << before;

        f->onLand(*current);

        qDebug() << "[FIELD] onLand done"
                 << "| playerMoneyAfter=" << current->money;
    }

    // Freies Property? -> Kaufen anbieten
    if (auto *pf = dynamic_cast<PropertyField*>(f)) {
        if (pf->owner == nullptr && current->money >= pf->price) {
            qDebug() << "[BUY?] Offer to player" << current->id
                     << "field=" << pf->index << pf->name
                     << "price=" << pf->price;

            askToBuy(*current, pf->index, pf->price, pf->name);
            broadcastGameState("buyRequested");
            return; // Turn erst nach buyDecision beenden
        }
    }

    broadcastGameState("turnResolved");
    awaitingEndTurn = true;
    pendingEndTurnPlayerId = current->id;
    broadcastGameState("awaitingEndTurn");
}

void GameServer::handleEndTurn(Player &player)
{
    if (gameFinished) {
        QJsonObject err;
        err["type"] = "error";
        err["message"] = "Spiel ist bereits beendet.";
        sendToPlayer(player, err);
        return;
    }

    if (!gameStarted) {
        QJsonObject err;
        err["type"] = "error";
        err["message"] = "Spiel ist noch nicht gestartet.";
        sendToPlayer(player, err);
        return;
    }

    if (awaitingBuyDecision) {
        QJsonObject err;
        err["type"] = "error";
        err["message"] = "Erst Kaufentscheidung treffen.";
        sendToPlayer(player, err);
        return;
    }

    Player *current = game.getCurrentPlayer();
    if (!current) return;

    if (!awaitingEndTurn || pendingEndTurnPlayerId != player.id || current->id != player.id) {
        QJsonObject err;
        err["type"] = "error";
        err["message"] = "Du kannst den Zug gerade nicht beenden.";
        sendToPlayer(player, err);
        return;
    }

    awaitingEndTurn = false;
    pendingEndTurnPlayerId = -1;
    broadcastLog(player.id, "beendet den Zug");
    finishTurnAndBroadcast();
}

void GameServer::handleSurrender(Player &player)
{
    if (!gameStarted || gameFinished) {
        QJsonObject err;
        err["type"] = "error";
        err["message"] = "Aufgeben ist nur während eines laufenden Spiels möglich.";
        sendToPlayer(player, err);
        return;
    }

    if (awaitingBuyDecision && pendingBuyPlayerId == player.id) {
        awaitingBuyDecision = false;
        pendingBuyPlayerId = -1;
        pendingBuyFieldIndex = -1;
    }

    if (awaitingEndTurn && pendingEndTurnPlayerId == player.id) {
        awaitingEndTurn = false;
        pendingEndTurnPlayerId = -1;
    }

    player.isBankrupt = true;
    broadcastLog(player.id, "gibt auf");
    updateWinnerIfNeeded("playerSurrendered");
    broadcastGameState("playerSurrendered");
}

void GameServer::initBoardIfNeeded()
{
    if (boardInitialized) return;
    boardInitialized = true;

    qDebug() << "[BOARD] initializing...";

    for (Field *f : board.fields) {
        delete f;
    }
    board.fields.clear();
    board.fields.reserve(40);

    auto fast = [](int value) {
        return std::max(1, value / 2);
    };

    auto mkStart = [&](int idx, const QString &nm, int bonus){
        auto *f = new StartField();
        f->index = idx;
        f->name = nm;
        f->startBonus = fast(bonus);
        board.fields.append(f);
    };

    auto mkStreet = [&](int idx, const QString &nm, const QString &color,
                        int price, int baseRent, int hotelPrice, int hotelRent){
        auto *f = new StreetField();
        f->index = idx;
        f->name = nm;
        f->color = color;
        f->price = fast(price);
        f->baseRent = fast(baseRent);
        f->hotelPrice = fast(hotelPrice);
        f->hotelRent = fast(hotelRent);
        board.fields.append(f);
    };

    auto mkRail = [&](int idx, const QString &nm, int price, int rent){
        auto *f = new RailroadField();
        f->index = idx;
        f->name = nm;
        f->price = fast(price);
        f->baseRent = fast(rent);
        board.fields.append(f);
    };

    auto mkUtil = [&](int idx, const QString &nm, int price){
        auto *f = new UtilityField();
        f->index = idx;
        f->name = nm;
        f->price = fast(price);
        f->baseRent = 0;
        board.fields.append(f);
    };

    auto mkTax = [&](int idx, const QString &nm, int tax){
        auto *f = new TaxField();
        f->index = idx;
        f->name = nm;
        f->taxAmount = fast(tax);
        board.fields.append(f);
    };

    auto mkJail = [&](int idx, const QString &nm){
        auto *f = new JailField();
        f->index = idx;
        f->name = nm;
        board.fields.append(f);
    };

    mkStart(0, "GO", 200);
    mkStreet(1, "Mediterranean Avenue", "brown", 60, 2, 50, 10);
    mkTax(2, "Community Chest", 0);
    mkStreet(3, "Baltic Avenue", "brown", 60, 4, 50, 20);
    mkTax(4, "Income Tax", 200);
    mkRail(5, "Reading Railroad", 200, 25);
    mkStreet(6, "Oriental Avenue", "lightblue", 100, 6, 50, 30);
    mkTax(7, "Chance", 0);
    mkStreet(8, "Vermont Avenue", "lightblue", 100, 6, 50, 30);
    mkStreet(9, "Connecticut Avenue", "lightblue", 120, 8, 50, 40);
    mkJail(10, "Jail / Just Visiting");
    mkStreet(11, "St. Charles Place", "pink", 140, 10, 100, 50);
    mkUtil(12, "Electric Company", 150);
    mkStreet(13, "States Avenue", "pink", 140, 10, 100, 50);
    mkStreet(14, "Virginia Avenue", "pink", 160, 12, 100, 60);
    mkRail(15, "Pennsylvania Railroad", 200, 25);
    mkStreet(16, "St. James Place", "orange", 180, 14, 100, 70);
    mkTax(17, "Community Chest", 0);
    mkStreet(18, "Tennessee Avenue", "orange", 180, 14, 100, 70);
    mkStreet(19, "New York Avenue", "orange", 200, 16, 100, 80);
    mkTax(20, "Free Parking", 0);
    mkStreet(21, "Kentucky Avenue", "red", 220, 18, 150, 90);
    mkTax(22, "Chance", 0);
    mkStreet(23, "Indiana Avenue", "red", 220, 18, 150, 90);
    mkStreet(24, "Illinois Avenue", "red", 240, 20, 150, 100);
    mkRail(25, "B. & O. Railroad", 200, 25);
    mkStreet(26, "Atlantic Avenue", "yellow", 260, 22, 150, 110);
    mkStreet(27, "Ventnor Avenue", "yellow", 260, 22, 150, 110);
    mkUtil(28, "Water Works", 150);
    mkStreet(29, "Marvin Gardens", "yellow", 280, 24, 150, 120);
    mkTax(30, "Go To Jail", 0);
    mkStreet(31, "Pacific Avenue", "green", 300, 26, 200, 130);
    mkStreet(32, "North Carolina Avenue", "green", 300, 26, 200, 130);
    mkTax(33, "Community Chest", 0);
    mkStreet(34, "Pennsylvania Avenue", "green", 320, 28, 200, 150);
    mkRail(35, "Short Line", 200, 25);
    mkTax(36, "Chance", 0);
    mkStreet(37, "Park Place", "darkblue", 350, 35, 200, 175);
    mkTax(38, "Luxury Tax", 100);
    mkStreet(39, "Boardwalk", "darkblue", 400, 50, 200, 200);

    qDebug() << "[BOARD] ready with fields=" << board.fields.size();
}

void GameServer::askToBuy(Player &player, int fieldIndex, int price, const QString &fieldName)
{
    awaitingBuyDecision = true;
    pendingBuyPlayerId = player.id;
    pendingBuyFieldIndex = fieldIndex;

    QJsonObject req;
    req["type"] = "buyRequest";
    req["playerId"] = player.id;
    req["fieldIndex"] = fieldIndex;
    req["fieldName"] = fieldName;
    req["price"] = price;

    sendToPlayer(player, req);
}

void GameServer::finishTurnAndBroadcast()
{
    awaitingEndTurn = false;
    pendingEndTurnPlayerId = -1;
    game.nextTurn();
    qDebug() << "[TURN] nextTurn -> currentPlayerId="
             << (game.getCurrentPlayer() ? game.getCurrentPlayer()->id : -1);
    broadcastGameState("nextTurn");
}

void GameServer::sendToSocket(QTcpSocket *socket, const QJsonObject &obj)
{
    if (!socket) return;
    QByteArray data = QJsonDocument(obj).toJson(QJsonDocument::Compact);
    data.append('\n');
    socket->write(data);
    socket->flush();

    qDebug() << "[NET] => to socket" << data.trimmed();
}

void GameServer::sendToPlayer(Player &player, const QJsonObject &obj)
{
    sendToSocket(player.socket, obj);
}

void GameServer::broadcast(const QJsonObject &obj)
{
    for (auto &p : players) {
        if (p && p->socket) {
            sendToPlayer(*p, obj);
        }
    }
}

void GameServer::broadcastLog(int playerId, const QString &message)
{
    QJsonObject log;
    log["type"] = "log";
    log["playerId"] = playerId;
    log["message"] = message;
    broadcast(log);
}

QJsonObject GameServer::buildGameState(const QString &reason) const
{
    QJsonObject state;
    state["type"] = "state";
    state["reason"] = reason;
    state["gameStarted"] = gameStarted;
    state["gameFinished"] = gameFinished;
    state["winnerId"] = winnerId;

    Player *cur = const_cast<Game&>(game).getCurrentPlayer();
    if (gameStarted && !cur && !players.empty()) {
        cur = players.front().get();
    }
    state["currentPlayerId"] = (gameStarted && cur) ? cur->id : -1;

    QJsonArray parr;
    for (const auto &p : players) {
        QJsonObject po;
        if (!p) {
            continue;
        }
        po["id"] = p->id;
        po["name"] = p->name;
        po["position"] = p->position;
        po["money"] = p->money;
        po["inJail"] = p->inJail;
        po["jailTurns"] = p->jailTurns;
        po["bankrupt"] = p->isBankrupt;
        po["ready"] = p->isReady;
        parr.append(po);
    }
    state["players"] = parr;

    QJsonArray farr;
    for (int i = 0; i < board.fields.size(); ++i) {
        Field *f = board.fields[i];
        QJsonObject fo;
        fo["index"] = i;
        fo["name"] = f ? f->name : QString();

        if (auto *pf = dynamic_cast<PropertyField*>(f)) {
            fo["type"] = "property";
            fo["price"] = pf->price;
            fo["baseRent"] = pf->baseRent;
            fo["ownerId"] = pf->owner ? pf->owner->id : -1;

            if (auto *sf = dynamic_cast<StreetField*>(f)) {
                fo["subtype"] = "street";
                fo["color"] = sf->color;
                fo["hasHotel"] = sf->hasHotel;
                fo["hotelPrice"] = sf->hotelPrice;
                fo["hotelRent"] = sf->hotelRent;
            } else if (dynamic_cast<RailroadField*>(f)) {
                fo["subtype"] = "railroad";
            } else if (dynamic_cast<UtilityField*>(f)) {
                fo["subtype"] = "utility";
            }
        } else if (dynamic_cast<TaxField*>(f)) {
            fo["type"] = "tax";
        } else if (dynamic_cast<StartField*>(f)) {
            fo["type"] = "start";
        } else if (dynamic_cast<JailField*>(f)) {
            fo["type"] = "jail";
        } else {
            fo["type"] = "field";
        }

        farr.append(fo);
    }
    state["fields"] = farr;

    state["awaitingBuyDecision"] = awaitingBuyDecision;
    state["pendingBuyPlayerId"] = pendingBuyPlayerId;
    state["pendingBuyFieldIndex"] = pendingBuyFieldIndex;
    state["awaitingEndTurn"] = awaitingEndTurn;
    state["pendingEndTurnPlayerId"] = pendingEndTurnPlayerId;

    return state;
}

bool GameServer::areAllPlayersReady() const
{
    if (players.empty()) {
        return false;
    }
    for (const auto &p : players) {
        if (!p || !p->isReady) {
            return false;
        }
    }
    return true;
}

void GameServer::broadcastGameState(const QString &reason)
{
    broadcast(buildGameState(reason));
}

void GameServer::updateWinnerIfNeeded(const QString &reason)
{
    if (gameFinished) {
        return;
    }

    int activePlayers = 0;
    Player *lastActive = nullptr;
    for (const auto &p : players) {
        if (p && !p->isBankrupt) {
            activePlayers++;
            lastActive = p.get();
        }
    }

    if (activePlayers == 1 && lastActive) {
        gameFinished = true;
        winnerId = lastActive->id;
        broadcastLog(winnerId, "gewinnt das Spiel");
        broadcastGameState(reason);
    }
}

Player* GameServer::findPlayerBySocket(QTcpSocket *socket)
{
    auto it = std::find_if(players.begin(), players.end(),
                           [&](const std::unique_ptr<Player>& p){
                               return p && p->socket == socket;
                           });
    if (it == players.end()) return nullptr;
    return it->get();
}

Player* GameServer::findPlayerById(int id)
{
    auto it = std::find_if(players.begin(), players.end(),
                           [&](const std::unique_ptr<Player>& p){
                               return p && p->id == id;
                           });
    if (it == players.end()) return nullptr;
    return it->get();
}

void GameServer::onClientDisconnected()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;

    auto it = std::find_if(players.begin(), players.end(),
                           [&](const std::unique_ptr<Player>& p){
                               return p && p->socket == socket;
                           });

    if (it != players.end()) {
        qDebug() << "[NET] client disconnected:" << (*it)->name;

        // pending buy abbrechen, falls nötig
        if (awaitingBuyDecision && pendingBuyPlayerId == (*it)->id) {
            qWarning() << "[BUY] pending buy canceled due disconnect";
            awaitingBuyDecision = false;
            pendingBuyPlayerId = -1;
            pendingBuyFieldIndex = -1;
        }
        if (awaitingEndTurn && pendingEndTurnPlayerId == (*it)->id) {
            qWarning() << "[TURN] pending endTurn canceled due disconnect";
            awaitingEndTurn = false;
            pendingEndTurnPlayerId = -1;
        }

        game.removePlayer(it->get());
        players.erase(it);
        updateWinnerIfNeeded("playerLeft");
        broadcastGameState("playerLeft");
    }

    recvBuffers.remove(socket);
    socket->deleteLater();
}
