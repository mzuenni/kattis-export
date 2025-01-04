#ifndef PRIO_PLAYER_H_
#define PRIO_PLAYER_H_
#include "player.h"
#include "validation.h"

class PrioPlayer : public Player {
  public:
    PrioPlayer(const Game &g, bool is_odd, std::array<int,3> prio): is_odd(is_odd), prio(prio) {
        for (const Card &c: g.cards) {
            cards[slot(c)].push_back(c);
        }
        for (int k = 0; k < 3; k++) {
            count[k] = cards[k].size();
        }
    }

    Card select_move(const Game &g) {
        if (g.last_played) count[slot(g.last_played.value())]--;

        int who = is_odd, cur = g.current, a = count[0], b = count[1], c = count[2], k = -1;
        if (win(who, cur, a, b, c)) {
            // We have a winning strategy from here, so play accordingly.
            if (a > 0 && !win(1-who, cur, a-1, b, c)) k = 0;
            if (b > 0 && !win(1-who, 1-cur, a, b-1, c)) k = 1;
            if (c > 0 && !win(1-who, 0, a, b, c-1)) k = 2;
            while (g.used_cards.count(cards[k].back())) cards[k].pop_back();
        } else {
            // No winning strategy here, so just pick some move according to the priority list.
            for (int j: prio) {
                auto &v = cards[j];
                while (!v.empty() && g.used_cards.count(v.back())) {
                    v.pop_back();
                }
                if (!v.empty()) {
                    k = j;
                    break;
                }
            }
        }
        count[k]--;
        return cards[k].back();
    }

  private:
    bool is_odd;
    int count[3];
    std::vector<Card> cards[3];
    std::array<int,3> prio;

    int slot(const Card &c) {
        if (c.op == '+' && c.x % 2 == 1) return 1;
        if (c.op == '*' && c.x % 2 == 0) return 2;
        return 0;
    }

    int win(int who, int cur, int a, int b, int c) {
        if (c == 0) return (cur+b) % 2 == who;
        if (who == 0) return true;
        return c == 1 && b%2 == 1;
    }
};

#endif // PRIO_PLAYER_H_
