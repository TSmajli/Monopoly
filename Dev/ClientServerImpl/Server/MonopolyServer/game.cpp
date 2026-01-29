#include "game.h"

#include <QRandomGenerator>

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

void Game::setCurrentPlayerIndex(int index)
{
    if (players.isEmpty()) {
        currentPlayerIndex = 0;
        return;
    }

    if (index < 0) {
        currentPlayerIndex = 0;
        return;
    }

    currentPlayerIndex = index % players.size();
}

void Game::setRandomStart()
{
    if (players.isEmpty()) {
        currentPlayerIndex = 0;
        return;
    }

    const int idx = QRandomGenerator::global()->bounded(players.size());
    currentPlayerIndex = idx;
}

int Game::boardSize() const
{
    return 40; // Monopoly Standard
}
