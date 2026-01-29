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

        players.append(std::move(player));
        game.addPlayer(players.last().get());

        recvBuffers.insert(client, QByteArray());

        connect(client, &QTcpSocket::readyRead,
                this, &GameServer::onReadyRead);
        connect(client, &QTcpSocket::disconnected,
                this, &GameServer::onClientDisconnected);

        initBoardIfNeeded();

        // Assign ID
        QJsonObject msg;
        msg["type"] = "assignPlayerId";
        msg["playerId"] = players.last()->id;
        msg["name"] = players.last()->name;
        sendToSocket(client, msg);

        qDebug() << "[NET] Neuer Client:" << players.last()->name
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
            } else {
                qDebug() << "[BUY] Player" << p->id << "declined" << pf->name;
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

    gameStarted = true;
    qDebug() << "[GAME] STARTED by" << player.name
             << "| currentPlayerId=" << (game.getCurrentPlayer() ? game.getCurrentPlayer()->id : -1);

    broadcastGameState("gameStarted");
}

void GameServer::handleRollDice(Player &player)
{
    initBoardIfNeeded();

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
    finishTurnAndBroadcast();
}

void GameServer::initBoardIfNeeded()
{
    if (boardInitialized) return;
    boardInitialized = true;

    qDebug() << "[BOARD] initializing...";

    board.fields.clear();
    board.fields.reserve(40);

    auto mkStart = [&](int idx, const QString &nm, int bonus){
        auto *f = new StartField();
        f->index = idx;
        f->name = nm;
        f->startBonus = bonus;
        board.fields.append(f);
    };

    auto mkStreet = [&](int idx, const QString &nm, const QString &color,
                        int price, int baseRent, int hotelPrice, int hotelRent){
        auto *f = new StreetField();
        f->index = idx;
        f->name = nm;
        f->color = color;
        f->price = price;
        f->baseRent = baseRent;
        f->hotelPrice = hotelPrice;
        f->hotelRent = hotelRent;
        board.fields.append(f);
    };

    auto mkRail = [&](int idx, const QString &nm, int price, int rent){
        auto *f = new RailroadField();
        f->index = idx;
        f->name = nm;
        f->price = price;
        f->baseRent = rent;
        board.fields.append(f);
    };

    auto mkUtil = [&](int idx, const QString &nm, int price){
        auto *f = new UtilityField();
        f->index = idx;
        f->name = nm;
        f->price = price;
        f->baseRent = 0;
        board.fields.append(f);
    };

    auto mkTax = [&](int idx, const QString &nm, int tax){
        auto *f = new TaxField();
        f->index = idx;
        f->name = nm;
        f->taxAmount = tax;
        board.fields.append(f);
    };

    auto mkJail = [&](int idx, const QString &nm){
        auto *f = new JailField();
        f->index = idx;
        f->name = nm;
        board.fields.append(f);
    };

    // Minimal-Board (spielbar, kein komplettes Monopoly-Original)
    mkStart(0, "START", 200);
    mkStreet(1, "Braun 1", "brown", 60, 2, 50, 10);
    mkTax(2, "Steuer", 100);
    mkStreet(3, "Braun 2", "brown", 60, 4, 50, 20);
    mkRail(4, "Bahnhof 1", 200, 25);
    mkStreet(5, "Hellblau 1", "lightblue", 100, 6, 50, 30);
    mkUtil(6, "Wasserwerk", 150);
    mkStreet(7, "Hellblau 2", "lightblue", 100, 6, 50, 30);
    mkStreet(8, "Hellblau 3", "lightblue", 120, 8, 50, 40);
    mkTax(9, "Steuer", 100);
    mkJail(10, "GEFÄNGNIS (Besuch)");

    // Rest auffüllen
    while (board.fields.size() < 40) {
        int idx = board.fields.size();
        mkTax(idx, QString("Feld %1").arg(idx), 0);
    }

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

QJsonObject GameServer::buildGameState(const QString &reason) const
{
    QJsonObject state;
    state["type"] = "state";
    state["reason"] = reason;
    state["gameStarted"] = gameStarted;

    Player *cur = const_cast<Game&>(game).getCurrentPlayer();
    if (gameStarted && !cur && !players.isEmpty()) {
        cur = players.first().get();
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

void GameServer::broadcastGameState(const QString &reason)
{
    broadcast(buildGameState(reason));
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
        broadcastGameState("playerLeft");
    }

    recvBuffers.remove(socket);
    socket->deleteLater();
}
