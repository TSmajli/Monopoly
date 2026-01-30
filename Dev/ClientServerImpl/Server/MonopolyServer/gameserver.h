#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHash>
#include <QJsonObject>
#include <memory>
#include <vector>

#include "game.h"
#include "player.h"
#include "board.h"

class GameServer : public QObject
{
    Q_OBJECT

public:
    explicit GameServer(QObject *parent = nullptr);
    void startServer(quint16 port = 4242);

private:
    QTcpServer server;

    // newline-delimited JSON: wir puffern je Socket
    QHash<QTcpSocket*, QByteArray> recvBuffers;

    std::vector<std::unique_ptr<Player>> players;
    int nextPlayerId = 1;

    Game game;

    // Monopoly Board liegt beim Server
    Board board;
    bool boardInitialized = false;

    // Startlogik
    bool gameStarted = false;

    // Kaufen-Flow (max. 1 pending Kaufentscheidung)
    bool awaitingBuyDecision = false;
    int pendingBuyPlayerId = -1;
    int pendingBuyFieldIndex = -1;
    bool awaitingEndTurn = false;
    int pendingEndTurnPlayerId = -1;
    bool gameFinished = false;
    int winnerId = -1;

private slots:
    void onNewConnection();
    void onReadyRead();
    void onClientDisconnected();

private:
    void processMessage(Player &player, const QJsonObject &msg);

    // Spielablauf
    void initBoardIfNeeded();
    void handleStartGame(Player &player);
    void handleRollDice(Player &player);
    void handleEndTurn(Player &player);
    void handleSurrender(Player &player);
    void handleSetReady(Player &player, bool ready);
    void handleSetName(Player &player, const QString &name);
    void handleRestartGame(Player &player);
    void handleBuyHouse(Player &player);
    void askToBuy(Player &player, int fieldIndex, int price, const QString &fieldName);
    void finishTurnAndBroadcast();
    void updateWinnerIfNeeded(const QString &reason);
    bool areAllPlayersReady() const;

    // JSON helpers
    void sendToSocket(QTcpSocket *socket, const QJsonObject &obj);
    void sendToPlayer(Player &player, const QJsonObject &obj);
    void broadcast(const QJsonObject &obj);
    void broadcastLog(int playerId, const QString &message);

    // State
    void broadcastGameState(const QString &reason = QString());
    QJsonObject buildGameState(const QString &reason = QString()) const;

    // Lookup
    Player* findPlayerBySocket(QTcpSocket *socket);
    Player* findPlayerById(int id);
};

#endif // GAMESERVER_H
