#pragma once
#include "field.h"

class PropertyField : public Field {
public:
    int price;
    int baseRent;
    Player* owner = nullptr;

    virtual int calculateRent() const = 0;
    void buy(Player& player);
};
