#include "propertyfield.h"
#include "player.h"

void PropertyField::buy(Player& player) {
    if (!owner && player.money >= price) {
        owner = &player;
        player.pay(price);
        player.properties.append(this);
    }
}
