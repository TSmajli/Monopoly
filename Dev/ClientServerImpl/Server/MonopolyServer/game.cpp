#include "game.h"

void Game::startGame() {
    currentPlayer = 0;
}

void Game::nextTurn() {
    currentPlayer = (currentPlayer + 1) % players.size();
}

Player& Game::getCurrentPlayer() {
    return players[currentPlayer];
}

