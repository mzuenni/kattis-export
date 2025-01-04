#ifndef RANDOM_PLAYER_H_
#define RANDOM_PLAYER_H_
#include "player.h"
#include "validation.h"

class RandomPlayer : public Player {
  public:
    RandomPlayer() {}

    // Select one of the possible moves uniformly at random.
    Card select_move(const Game &g) {
        while (g.used_cards.count(g.cards[index])) index++;
        return g.cards[index];
    }

  private:
    int index = 0;
};

#endif // RANDOM_PLAYER_H_
