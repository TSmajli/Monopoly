#pragma once
#include "field.h"

class StartField : public Field {
public:
    int startBonus = 300;

    void onLand(Player& player) override;
};

