#include "streetfield.h"
#include "player.h"

int StreetField::calculateRent() const {
    return hasHotel ? hotelRent : baseRent;
}

void StreetField::buyHotel(Player& player) {
    if (owner == &player && !hasHotel && player.money >= hotelPrice) {
        player.pay(hotelPrice);
        hasHotel = true;
    }
}

void StreetField::onLand(Player& player) {
    if (owner && owner != &player) {
        player.pay(calculateRent());
        owner->receive(calculateRent());
    }
}
