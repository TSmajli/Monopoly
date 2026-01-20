
#include <QCoreApplication>
#include "gameserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GameServer server;
    server.startServer(4242);

    return a.exec();
}
