#pragma once
#include <QString>

class Player;

class Field {
public:
    QString name;
    int index;

    virtual ~Field() = default;
    virtual void onLand(Player& player) = 0;
};
