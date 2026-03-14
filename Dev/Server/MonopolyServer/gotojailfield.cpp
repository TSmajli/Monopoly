#include "gotojailfield.h"
#include "player.h"

void GoToJailField::onLand(Player& player) {
    player.goToJail(10); // Berufsschule ist Feld 10
}
