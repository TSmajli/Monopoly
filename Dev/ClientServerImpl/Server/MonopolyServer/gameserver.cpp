
#include "gameserver.h"
#include <QJsonDocument>
#include <QDebug>

GameServer::GameServer(QObject *parent) : QObject(parent)
{
    connect(&server, &QTcpServer::newConnection, this, &GameServer::onNewConnection);
}

void GameServer::startServer(quint16 port)
{
    if (!server.listen(QHostAddress::Any, port)) {
        qDebug() << "Server konnte nicht starten!";
        return;
    }
    qDebug() << "Server läuft auf Port" << port;
}

void GameServer::onNewConnection()
{
    while (server.hasPendingConnections()) {
        QTcpSocket *client = server.nextPendingConnection();
        qDebug() << "Neuer Client verbunden:" << client->peerAddress().toString();

        Player player;
        player.id = nextPlayerId++;
        player.socket = client;
        player.name = QString("Player%1").arg(player.id);
        players.append(player);

        connect(client, &QTcpSocket::readyRead, this, &GameServer::onReadyRead);
        connect(client, &QTcpSocket::disconnected, this, &GameServer::onClientDisconnected);

        // Spieler-ID zurücksenden
        QJsonObject msg;
        msg["type"] = "assignPlayerId";
        msg["playerId"] = player.id;
        client->write(QJsonDocument(msg).toJson(QJsonDocument::Compact) + "\n");
    }
}

void GameServer::onReadyRead()
{
    // Wer hat die Nachricht geschickt?
    QTcpSocket *senderSocket = qobject_cast<QTcpSocket*>(sender());
    if (!senderSocket) return;

    // Finde Player
    auto it = std::find_if(players.begin(), players.end(),
                           [=](const Player &p){ return p.socket == senderSocket; });
    if (it == players.end()) return;

    Player &player = *it;

    while (senderSocket->canReadLine()) {
        QByteArray line = senderSocket->readLine();
        QJsonDocument doc = QJsonDocument::fromJson(line);
        if (!doc.isObject()) continue;

        QJsonObject msg = doc.object();
        processMessage(player, msg);
    }
}

void GameServer::processMessage(Player &player, const QJsonObject &msg)
{
    QString type = msg["type"].toString();

    if (type == "rollDice") {
        // Beispiel: Würfelergebnis erzeugen
        int dice1 =  6 + 1;
        int dice2 =  6 + 1;
        int newPos = (dice1 + dice2); // Beispiel, einfach hochzählen

        // Antwort an den Client
        QJsonObject reply;
        reply["type"] = "diceResult";
        reply["dice1"] = dice1;
        reply["dice2"] = dice2;
        reply["newPosition"] = newPos;

        player.socket->write(QJsonDocument(reply).toJson(QJsonDocument::Compact) + "\n");

        qDebug() << player.name << "würfelt:" << dice1 << "+" << dice2 << "=" << newPos;
    }
}

void GameServer::onClientDisconnected()
{
    QTcpSocket *senderSocket = qobject_cast<QTcpSocket*>(sender());
    if (!senderSocket) return;

    auto it = std::find_if(players.begin(), players.end(),
                           [=](const Player &p){ return p.socket == senderSocket; });
    if (it != players.end()) {
        qDebug() << it->name << "hat den Server verlassen.";
        players.erase(it);
    }

    senderSocket->deleteLater();
}
