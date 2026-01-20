#include "networkclient.h"
#include <QJsonDocument>

NetworkClient::NetworkClient(QObject *parent)
    : QObject(parent)
{
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::connected,
            this, &NetworkClient::connected);

    connect(socket, &QTcpSocket::disconnected,
            this, &NetworkClient::disconnected);

    connect(socket, &QTcpSocket::readyRead,
            this, &NetworkClient::onReadyRead);

    connect(socket, &QTcpSocket::errorOccurred, this,
            [=](QAbstractSocket::SocketError) {
                emit errorOccurred(socket->errorString());
            });
}

void NetworkClient::connectToServer(const QString &host, quint16 port)
{
    socket->connectToHost(host, port);
}

void NetworkClient::sendJson(const QJsonObject &obj)
{
    QJsonDocument doc(obj);
    socket->write(doc.toJson(QJsonDocument::Compact)+ "\n");
}

void NetworkClient::onReadyRead()
{
    QByteArray data = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);

    if (doc.isObject()) {
        emit jsonReceived(doc.object());
    }
}
void NetworkClient::sendRollDice(int playerId)
{
    QJsonObject msg;
    msg["type"] = "rollDice";
    msg["playerId"] = playerId;

    // Sende die Nachricht
    sendJson(msg);

}
