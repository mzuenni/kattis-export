#ifndef SMART_PLAYER_H_
#define SMART_PLAYER_H_
#include "player.h"
#include "validation.h"

class SmartPlayer : public Player {
  public:
    SmartPlayer(const Game &g, bool is_odd): is_odd(is_odd) {
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
            // No winning strategy here, so just pick some move.
            std::mt19937_64 gen(a + 123*b + 456*c);
            Generators::UniformGenerator uniform;
            while (true) {
                k = uniform(0LL, 2LL, gen);
                if (cards[k].empty()) continue;
                if (!g.used_cards.count(cards[k].back())) break;
                cards[k].pop_back();
            }
        }
        count[k]--;
        return cards[k].back();
    }

  private:
    bool is_odd;
    int count[3];
    std::vector<Card> cards[3];

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

#endif // SMART_PLAYER_H_
