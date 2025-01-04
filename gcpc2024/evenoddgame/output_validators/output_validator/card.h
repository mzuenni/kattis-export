#ifndef CARD_H_
#define CARD_H_

#include <tuple>

struct Card {
    char op;
    int x;

    Card(char op, int x): op(op), x(x) {}

    bool operator<(const Card &c) const {
        return std::tie(op, x) < std::tie(c.op, c.x);
    }

    int operator()(int y) {
        return (op == '+' ? x+y : x*y) % 2;
    }
};

#endif // CARD_H_
