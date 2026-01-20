#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonObject>
#include <QVector>

struct Player {
    int id;
    QString name;
    QTcpSocket *socket;
};

class GameServer : public QObject
{
    Q_OBJECT
public:
    explicit GameServer(QObject *parent = nullptr);
    void startServer(quint16 port = 4242);

private:
    QTcpServer server;
    QVector<Player> players;
    int nextPlayerId = 1;

private slots:
    void onNewConnection();
    void onReadyRead();
    void onClientDisconnected();

    void processMessage(Player &player, const QJsonObject &msg);
};

#endif // GAMESERVER_H
