#pragma once
#include "field.h"
#include <QString>

// "Unterricht"-Felder: zufällige Ereigniskarte mit Schulthema
class CardField : public Field {
public:
    QString lastCardMessage; // wird nach onLand() vom Server ausgelesen und gebroadcastet

    void onLand(Player& player) override;
};
