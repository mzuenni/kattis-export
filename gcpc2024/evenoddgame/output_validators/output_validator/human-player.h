#ifndef HUMAN_PLAYER_H_
#define HUMAN_PLAYER_H_
#include "player.h"
#include "validation.h"

class HumanPlayer : public Player {
  public:
    HumanPlayer(OutputValidator &v) : v(v) {}

    Card select_move(const Game &g) {
        char op = v.read_string("op", 1, 1, "+*")[0];
        v.space();
        int x = v.read_integer("x", 1, 1e6);
        v.newline();
        return Card(op, x);
    }

  private:
    OutputValidator &v;
};

#endif // HUMAN_PLAYER_H_
