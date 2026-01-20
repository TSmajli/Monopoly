#pragma once
#include "propertyfield.h"

class StreetField : public PropertyField {
public:
    QString color;
    bool hasHotel = false;
    int hotelPrice;
    int hotelRent;

    void buyHotel(Player& player);
    int calculateRent() const override;
    void onLand(Player& player) override;
};
