#ifndef GAME_H_
#define GAME_H_
#include <cstdint>
#include <iostream>
#include <optional>
#include <random>
#include <set>
#include <string>
#include <vector>
#include "card.h"

struct Game {
    int current;
    std::set<Card> used_cards, unused_cards;
    std::vector<Card> cards;
    std::optional<Card> last_played = {};

    Game(std::istream &in) {
        int n; in >> n;
        std::cout << n << '\n';
        for (int i = 0; i < n; i++) {
            char op; in >> op;
            int x; in >> x;
            cards.emplace_back(op, x);
            std::cout << op << ' ' << x << '\n';
        }
        unused_cards = std::set<Card>(cards.begin(), cards.end());

        in >> current;
        std::cout << current << std::endl;
        current %= 2;

        int seed; in >> seed;
        std::shuffle(cards.begin(), cards.end(), std::mt19937_64(seed));
    }

    bool over() {
        return used_cards.size() == cards.size();
    }

    std::optional<std::string> make_move(Card c) {
        if (!unused_cards.count(c)) {
            if (used_cards.count(c)) {
                return "Illegal move, card has been used before.";
            } else {
                return "Illegal move, card is not in the game.";
            }
        } else {
            used_cards.insert(c);
            unused_cards.erase(c);
        }
        current = c(current);
        last_played = c;
        return {};
    }
};

#endif // GAME_H_
