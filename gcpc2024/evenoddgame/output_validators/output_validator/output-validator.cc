#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <set>
#include <vector>

#include "game.h"
#include "player.h"
#include "human-player.h"
#include "random-player.h"
#include "smart-player.h"
#include "prio-player.h"
#include "validation.h"

int main(int argc, char **argv) {
    std::ifstream in(argv[1]);
    OutputValidator v(argc, argv);

    Game g(in);

    Player *human, *computer;
    human = new HumanPlayer(v);

    std::string who = v.test_strings({"me", "you"});

    std::string mode; in >> mode;
    if (mode == "random") {
        computer = new RandomPlayer();
    } else if (mode == "smart") {
        computer = new SmartPlayer(g, who == "you");
    } else if (mode == "prio") {
        std::array<int,3> prio;
        for (int &k: prio) in >> k;
        computer = new PrioPlayer(g, who == "you", prio);
    } else {
        assert(false);
    }

    bool is_computer = who == "you";
    while (!g.over()) {
        Player *player = is_computer ? computer : human;
        Card c = player->select_move(g);
        if (auto msg = g.make_move(c)) {
            std::cerr << msg.value() << std::endl;
            v.check(is_computer, "Player made an illegal move, stopping interaction.");
            std::cerr << "Computer made an illegal move. This should not be possible." << std::endl;
            assert(false);
        }
        if (is_computer) {
            std::cout << c.op << ' ' << c.x << std::endl;
        }
        is_computer = !is_computer;
    }

    v.check(g.current != (who == "you"), "Game ended, but parity does not match. Computer opponent wins.");
}
