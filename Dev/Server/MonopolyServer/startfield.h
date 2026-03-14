#pragma once
#include "field.h"

class StartField : public Field {
public:
    int startBonus = 200;

    void onLand(Player& player) override;
};
