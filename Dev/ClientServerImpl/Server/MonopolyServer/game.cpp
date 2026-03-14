#include "game.h"

void Game::addPlayer(Player* player)
{
    players.append(player);
    normalizeCurrentPlayer();
}

void Game::removePlayer(Player* player)
{
    const int removedIndex = players.indexOf(player);
    players.removeAll(player);
    if (removedIndex >= 0 && removedIndex < currentPlayerIndex) {
        --currentPlayerIndex;
    }
    if (currentPlayerIndex >= players.size()) {
        currentPlayerIndex = 0;
    }
    normalizeCurrentPlayer();
}

Player* Game::getCurrentPlayer()
{
    normalizeCurrentPlayer();
    if (players.isEmpty()) return nullptr;
    return players[currentPlayerIndex];
}

void Game::nextTurn()
{
    if (players.isEmpty())
        return;

    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    normalizeCurrentPlayer();
}

void Game::resetTurnOrder()
{
    currentPlayerIndex = 0;
    normalizeCurrentPlayer();
}

int Game::boardSize() const
{
    return 40; // Monopoly Standard
}

void Game::normalizeCurrentPlayer()
{
    if (players.isEmpty()) {
        currentPlayerIndex = 0;
        return;
    }

    if (currentPlayerIndex < 0 || currentPlayerIndex >= players.size()) {
        currentPlayerIndex = 0;
    }

    const int startIndex = currentPlayerIndex;
    while (players[currentPlayerIndex] && players[currentPlayerIndex]->isBankrupt) {
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
        if (currentPlayerIndex == startIndex) {
            break;
        }
    }
}
