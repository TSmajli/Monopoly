#include "player.h"

void Player::move(int steps) {
    position += steps;
    if (position >= 40) {
        position -= 40; // Startbonus könnte hier kommen
        money += 200;          // Startfeld Bonus
    }
}



void Player::pay(int amount)
{
    money -= amount;
    if (money < 0)
        isBankrupt = true;
}

void Player::receive(int amount)
{
    money += amount;
}

void Player::goToJail(int jailPos)
{
    position = jailPos;
    inJail = true;
    jailTurns = 3;
}
