#include "railroadfield.h"
#include "player.h"

int RailroadField::calculateRent() const {
    return baseRent; // später: abhängig von Anzahl Bahnhöfe
}

void RailroadField::onLand(Player& player) {
    if (owner && owner != &player) {
        player.pay(calculateRent());
        owner->receive(calculateRent());
    }
}
