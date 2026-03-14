#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonObject>
#include <QTimer>

class NetworkClient : public QObject
{
    Q_OBJECT

public:
    explicit NetworkClient(QObject *parent = nullptr);

    void connectToServer(const QString &host, quint16 port);
    void sendJson(const QJsonObject &obj);
    void sendRollDice();
    void sendStartGame();
    void sendBuyDecision(bool decision, int playerId, int pendingBuyFieldIndex);
    void sendEndTurn();
    void sendGetState();
    void sendSetName(const QString name);
    void sendSurrender();
    void sendSetReady(bool ready);
    void sendBuyHouse(int fieldIndex);
    void sendRestartGame();
    void setReconnectEnabled(bool enabled);

signals:
    void connected();
    void disconnected();
    void jsonReceived(const QJsonObject &obj);
    void errorOccurred(const QString &error);

private:
    QTcpSocket *socket;
    QByteArray buffer;

    // Auto-Reconnect
    QString lastHost;
    quint16 lastPort = 0;
    QTimer *reconnectTimer;
    int reconnectDelay = 2000; // ms, verdoppelt sich bei jedem Fehlversuch
    static constexpr int maxReconnectDelay = 16000;
    bool reconnectEnabled = false;

    void scheduleReconnect();

private slots:
    void onReadyRead();
    void onConnected();
    void onDisconnected();
    void tryReconnect();
};

#endif // NETWORKCLIENT_H
