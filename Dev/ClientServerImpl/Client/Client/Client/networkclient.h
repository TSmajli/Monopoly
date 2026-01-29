#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonObject>

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




signals:
    void connected();
    void disconnected();
    void jsonReceived(const QJsonObject &obj);
    void errorOccurred(const QString &error);

private:
    QTcpSocket *socket;
    QByteArray buffer;

private slots:
    void onReadyRead();
};



#endif // NETWORKCLIENT_H
