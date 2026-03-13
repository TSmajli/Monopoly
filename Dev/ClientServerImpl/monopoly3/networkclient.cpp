#include "networkclient.h"
#include <QJsonDocument>

NetworkClient::NetworkClient(QObject *parent)
    : QObject(parent)
{
    socket = new QTcpSocket(this);
    reconnectTimer = new QTimer(this);
    reconnectTimer->setSingleShot(true);

    connect(socket, &QTcpSocket::connected,    this, &NetworkClient::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &NetworkClient::onDisconnected);
    connect(socket, &QTcpSocket::readyRead,    this, &NetworkClient::onReadyRead);
    connect(reconnectTimer, &QTimer::timeout,  this, &NetworkClient::tryReconnect);

    connect(socket, &QTcpSocket::errorOccurred, this,
            [=](QAbstractSocket::SocketError) {
                emit errorOccurred(socket->errorString());
            });
}

void NetworkClient::connectToServer(const QString &host, quint16 port)
{
    lastHost = host;
    lastPort = port;
    reconnectEnabled = true;
    reconnectDelay = 2000;
    reconnectTimer->stop();

    if (socket->state() != QAbstractSocket::UnconnectedState) {
        socket->abort();
    }
    socket->connectToHost(host, port);
}

void NetworkClient::onConnected()
{
    reconnectDelay = 2000; // Backoff zurücksetzen
    reconnectTimer->stop();
    emit connected();
}

void NetworkClient::onDisconnected()
{
    emit disconnected();
    if (reconnectEnabled && !lastHost.isEmpty()) {
        scheduleReconnect();
    }
}

void NetworkClient::scheduleReconnect()
{
    reconnectTimer->start(reconnectDelay);
    reconnectDelay = qMin(reconnectDelay * 2, maxReconnectDelay);
}

void NetworkClient::tryReconnect()
{
    if (lastHost.isEmpty() || !reconnectEnabled) {
        return;
    }
    if (socket->state() != QAbstractSocket::UnconnectedState) {
        socket->abort();
    }
    socket->connectToHost(lastHost, lastPort);
}

void NetworkClient::sendJson(const QJsonObject &obj)
{
    if (socket->state() != QAbstractSocket::ConnectedState) {
        return;
    }
    QJsonDocument doc(obj);
    socket->write(doc.toJson(QJsonDocument::Compact) + "\n");
}

void NetworkClient::onReadyRead()
{
    buffer.append(socket->readAll());

    while (true) {
        int nl = buffer.indexOf('\n');
        if (nl < 0) break;

        QByteArray line = buffer.left(nl);
        buffer.remove(0, nl + 1);

        line = line.trimmed();
        if (line.isEmpty()) continue;

        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(line, &err);

        if (err.error != QJsonParseError::NoError || !doc.isObject()) {
            qDebug() << "JSON Parse Error:" << err.errorString()
            << "raw=" << line;
            continue;
        }

        emit jsonReceived(doc.object());
    }
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

void NetworkClient::sendSetName(const QString name)
{
    QJsonObject msg;
    msg["type"] = "setName";
    msg["name"] = name;
    sendJson(msg);
}
void NetworkClient::sendSurrender()
{
    QJsonObject msg;
    msg["type"] = "surrender";
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

void NetworkClient::sendSetReady(bool ready)
{
    QJsonObject msg;
    msg["type"] = "setReady";
    msg["ready"] = ready;
    sendJson(msg);
}

void NetworkClient::sendBuyHouse(int fieldIndex)
{
    QJsonObject msg;
    msg["type"] = "buyHouse";
    msg["fieldIndex"] = fieldIndex;
    sendJson(msg);
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
