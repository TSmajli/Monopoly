#include "networkclient.h"

#include <QJsonDocument>
#include <QJsonParseError>
#include <QDebug>

NetworkClient::NetworkClient(QObject *parent)
    : QObject(parent)
    , socket(new QTcpSocket(this))
{
    connect(socket, &QTcpSocket::connected, this, &NetworkClient::connected);
    connect(socket, &QTcpSocket::disconnected, this, &NetworkClient::disconnected);
    connect(socket, &QTcpSocket::readyRead, this, &NetworkClient::onReadyRead);
    connect(socket, &QTcpSocket::errorOccurred, this, [this](QAbstractSocket::SocketError) {
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
    socket->write(doc.toJson(QJsonDocument::Compact) + "\n");
}

void NetworkClient::sendRollDice()
{
    QJsonObject msg;
    msg["type"] = "rollDice";
    sendJson(msg);
}

void NetworkClient::sendStartGame()
{
    QJsonObject msg;
    msg["type"] = "startGame";
    sendJson(msg);
}

void NetworkClient::sendBuyDecision(bool decision, int playerId, int pendingBuyFieldIndex)
{
    QJsonObject msg;
    msg["type"] = "buyDecision";
    msg["playerId"] = playerId;
    msg["fieldIndex"] = pendingBuyFieldIndex;
    msg["buy"] = decision;
    sendJson(msg);

    qDebug() << "[CLIENT] buyDecision sent:"
             << "pid=" << playerId
             << "field=" << pendingBuyFieldIndex
             << "buy=" << decision;
}

void NetworkClient::sendEndTurn()
{
    QJsonObject msg;
    msg["type"] = "endTurn";
    sendJson(msg);
}

void NetworkClient::sendGetState()
{
    QJsonObject msg;
    msg["type"] = "getState";
    sendJson(msg);
}

void NetworkClient::sendSurrender()
{
    QJsonObject msg;
    msg["type"] = "surrender";
    sendJson(msg);
}

void NetworkClient::sendSetReady(bool ready)
{
    QJsonObject msg;
    msg["type"] = "setReady";
    msg["ready"] = ready;
    sendJson(msg);
}

void NetworkClient::sendSetName(const QString &name)
{
    QJsonObject msg;
    msg["type"] = "setName";
    msg["name"] = name;
    sendJson(msg);
}

void NetworkClient::sendRestartGame()
{
    QJsonObject msg;
    msg["type"] = "restartGame";
    sendJson(msg);
}

void NetworkClient::sendBuyHouse()
{
    QJsonObject msg;
    msg["type"] = "buyHouse";
    sendJson(msg);
}

void NetworkClient::onReadyRead()
{
    buffer.append(socket->readAll());

    while (true) {
        const int nl = buffer.indexOf('\n');
        if (nl < 0) {
            break;
        }

        QByteArray line = buffer.left(nl);
        buffer.remove(0, nl + 1);

        line = line.trimmed();
        if (line.isEmpty()) {
            continue;
        }

        QJsonParseError err;
        const QJsonDocument doc = QJsonDocument::fromJson(line, &err);

        if (err.error != QJsonParseError::NoError || !doc.isObject()) {
            qDebug() << "JSON Parse Error:" << err.errorString()
                     << "raw=" << line;
            continue;
        }

        emit jsonReceived(doc.object());
    }
}
