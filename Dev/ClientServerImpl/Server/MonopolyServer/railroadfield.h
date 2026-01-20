#pragma once
#include "propertyfield.h"

class RailroadField : public PropertyField {
public:
    int calculateRent() const override;
    void onLand(Player& player) override;
};
