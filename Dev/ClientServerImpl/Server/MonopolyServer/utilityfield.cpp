#include "utilityfield.h"
#include "player.h"

int UtilityField::calculateRent() const {
    return lastDiceRoll * 6;
}

void UtilityField::onLand(Player& player) {
    if (owner && owner != &player) {
        player.pay(calculateRent());
        owner->receive(calculateRent());
    }
}

