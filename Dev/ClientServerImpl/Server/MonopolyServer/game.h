#ifndef GAME_H
#define GAME_H

#include <QVector>
#include "player.h"

class Game
{
public:
    void addPlayer(Player* player);
    void removePlayer(Player* player);

    Player* getCurrentPlayer();
    void nextTurn();
    void setCurrentPlayerIndex(int index);
    void setRandomStart();

    int boardSize() const;

private:
    QVector<Player*> players;
    int currentPlayerIndex = 0;
};

#endif // GAME_H
