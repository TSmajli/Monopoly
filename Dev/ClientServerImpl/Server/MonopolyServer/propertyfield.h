#pragma once
#include "field.h"

class PropertyField : public Field {
public:
    int price = 0;
    int baseRent = 0;
    Player* owner = nullptr;

    virtual int calculateRent() const = 0;
    void buy(Player& player);
    void release();
};
