#pragma once
#include "propertyfield.h"

class UtilityField : public PropertyField {
public:
    int lastDiceRoll = 0;

    int calculateRent() const override;
    void onLand(Player& player) override;
};
