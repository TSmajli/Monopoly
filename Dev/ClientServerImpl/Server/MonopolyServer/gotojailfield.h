#pragma once
#include "field.h"

// Feld 30 "Gehe zu Berufsschule" – schickt den Spieler direkt ins Gefängnis
class GoToJailField : public Field {
public:
    void onLand(Player& player) override;
};
