#ifndef PLAYER_H_
#define PLAYER_H_
#include "card.h"
#include "game.h"

class Player {
  public:
    virtual Card select_move(const Game &g) = 0;
};

#endif // PLAYER_H_
