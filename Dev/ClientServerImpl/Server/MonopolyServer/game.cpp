#include "game.h"

void Game::addPlayer(Player* player)
{
    players.append(player);
}

void Game::removePlayer(Player* player)
{
    players.removeAll(player);
    if (currentPlayerIndex >= players.size())
        currentPlayerIndex = 0;
}

Player* Game::getCurrentPlayer()
{
    if (players.isEmpty()) return nullptr;
    return players[currentPlayerIndex];
}


void Game::nextTurn()
{
    if (players.isEmpty())
        return;

    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
}

int Game::boardSize() const
{
    return 40; // Monopoly Standard
}
