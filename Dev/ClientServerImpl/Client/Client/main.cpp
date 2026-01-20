#include <QCoreApplication>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include "main.moc"
class Client : public QObject {
    Q_OBJECT

public:
    Client(QString host, quint16 port) {
        connect(&socket, &QTcpSocket::connected,
                this, &Client::onConnected);
        connect(&socket, &QTcpSocket::readyRead,
                this, &Client::onReadyRead);

        socket.connectToHost(host, port);
    }

private slots:
    void onConnected() {
        QTextStream(stdout) << "Verbunden mit Server\n";
        printMenu();
        readInput();
    }

    void onReadyRead() {
        while (socket.canReadLine()) {
            QByteArray line = socket.readLine().trimmed();
            QJsonDocument doc = QJsonDocument::fromJson(line);
            QJsonObject obj = doc.object();

            QString command = obj["command"].toString();
            QJsonObject data = obj["data"].toObject();

            QTextStream out(stdout);

            if (command == "DICE_RESULT") {
                out << "🎲 Würfel: "
                    << data["dice1"].toInt()
                    << " + "
                    << data["dice2"].toInt()
                    << " = "
                    << data["sum"].toInt()
                    << "\n";
                printMenu();
                readInput();
            }
        }
    }

    void readInput() {
        QTextStream in(stdin);
        QString input = in.readLine();

        if (input == "1") {
            sendRollDice();
        } else {
            QTextStream(stdout) << "Ungültige Eingabe\n";
            printMenu();
            readInput();
        }
    }

    void sendRollDice() {
        QJsonObject obj;
        obj["type"] = "ACTION";
        obj["command"] = "ROLL_DICE";

        QJsonDocument doc(obj);
        socket.write(doc.toJson(QJsonDocument::Compact) + "\n");
    }

    void printMenu() {
        QTextStream out(stdout);
        out << "\n--- Menü ---\n";
        out << "1) Würfeln\n";
        out << "Eingabe: ";
    }

private:
    QTcpSocket socket;
};

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    // IP ggf. anpassen!
    Client client("127.0.0.1", 4242);

    return app.exec();
}

