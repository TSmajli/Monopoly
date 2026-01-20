#include "startfield.h"
#include "player.h"

void StartField::onLand(Player& player) {
    player.receive(startBonus);
}
