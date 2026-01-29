#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QTcpSocket>
#include <QVector>

class PropertyField; // Forward Declaration

class Player
{
public:
    // Netzwerk
    int id = 0;
    QString name;
    QTcpSocket* socket = nullptr;

    // Spielstatus
    int position = 0;
    int money = 1500;

    bool isBankrupt = false;
    bool inJail = false;
    int jailTurns = 0;

    QVector<PropertyField*> properties;

    // Spielaktionen
    void move(int steps);
    void pay(int amount);
    void receive(int amount);
    void goToJail(int jailPos);
};

#endif // PLAYER_H
