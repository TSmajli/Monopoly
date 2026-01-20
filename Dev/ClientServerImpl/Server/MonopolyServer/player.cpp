#include "player.h"

void Player::move(int steps, int boardSize) {
    position = (position + steps) % boardSize;
}

void Player::pay(int amount) {
    money -= amount;
    if (money < 0)
        isBankrupt = true;
}

void Player::receive(int amount) {
    money += amount;
}

void Player::goToJail(int jailPos) {
    position = jailPos;
    inJail = true;
    jailTurns = 3;
}
