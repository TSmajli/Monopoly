#include "player.h"

void Player::move(int steps, int boardSize)
{
    int oldPos = position;
    position = (position + steps) % boardSize;

    // Über Start gelaufen?
    if (position < oldPos)
        receive(200);
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
