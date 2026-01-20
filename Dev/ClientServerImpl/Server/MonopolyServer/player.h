#pragma once
#include <QString>
#include <QVector>

class PropertyField;

class Player {
public:
    QString name;
    int position = 0;
    int money = 1500;
    bool isBankrupt = false;
    bool inJail = false;
    int jailTurns = 0;
    QTcpSocket* socket = nullptr;
    QVector<PropertyField*> properties;

    void move(int steps, int boardSize);
    void pay(int amount);
    void receive(int amount);
    void goToJail(int jailPos);
};
