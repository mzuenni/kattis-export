#include "validate.h"
#include <cassert>
using namespace std;

constexpr int R = 59;
constexpr int C = 42;
using Cell = complex<int>;

int main(int argc, char *argv[]) {
    Interactor::init(argc, argv);
    using namespace Interactor;
    int first_drow = testIn.integer(-R, R);
    testIn.space();
    int first_dcol = testIn.integer(-C, C);
    testIn.space();
    string strategy = testIn.string();
    testIn.space();
    int selector = testIn.integer(0, 100);
    testIn.newline();
    testIn.eof();

    constexpr int TEAM = 1, JURY = -1;
    array<array<int, C>, R> board{}; int OUTSIDE = 2;
    auto f = [&] (Cell c) -> int& {
        return real(c) < 1 || imag(c) < 1 || real(c) > R || imag(c) > C ? OUTSIDE : board[real(c) - 1][imag(c)- 1];
    };
    auto cell_less = [] (Cell a, Cell b) {
        return pair{real(a), imag(a)} < pair{real(b), imag(b)};
    };
    auto threats = [&] (int player) {
        set<Cell, decltype(cell_less)> ans(cell_less);
        for (int row = 1; row <= R; row++) {
            for (Cell c{row, 1}; imag(c) <= C; c += 1i) {
                if (f(c)) continue;
                for (Cell off : vector<Cell>{{1, 0}, {0, 1}, {1, 1}, {1, -1}}) {
                    for (auto [i, j] : vector<pair<int,int>>{{-2, -1}, {-1, 1}, {1, 2}})
                        if (f(c + i * off) == player && f(c + j * off) == player)
                            ans.insert(c);
                }
            }
        }
        return ans;
    };
    // We don't need to handle the case of the board getting filled up. The team will lose due to being unable to pick an empty cell, as they should.
    for (int turn = 0;; turn++) {
        int team_row = fromTeam.integer(1, R + 1), team_col = (fromTeam.space(), fromTeam.integer(1, C + 1));
        fromTeam.newline();
        Cell team_last_move{team_row, team_col};
        if (f(team_last_move)) {
            toTeam << "0 0" << endl;
            juryOut << "Cell " << team_last_move << " was already occupied" << WA;
        }
        if (threats(TEAM).contains(team_last_move)) {
            toTeam << "0 0" << endl;
            juryOut << "Team wins" << AC;
        }
        f(team_last_move) = TEAM;
        // If we can win, we should do so.
        if (auto x = threats(JURY); !empty(x)) {
            toTeam << "0 0" << endl;
            juryOut << "Jury wins by picking cell " << *begin(x) << "." << WA;
        }
        // Choose move to make
        Cell move = [&] () {
            auto t = threats(TEAM);
            if (!turn) { // Our response to the first turn is parametrized as an offset by the test case
                int jury_row = ((team_row + first_drow - 1) % R + R) % R + 1;
                int jury_col = ((team_col + first_dcol - 1) % C + C) % C + 1;
                return Cell{jury_row, jury_col};
            }
            // After the first turn, we do one of three things: Block a threat, create a [major] threat, or make a weird move.
            set<Cell, decltype(cell_less)> counter_threats(cell_less);
            // Look for a pattern ..X. -> .XX.
            for (int row = 1; row <= R; row++) {
                for (Cell c{row, 1}; imag(c) <= C; c += 1i) {
                    if (f(c) != JURY) continue;
                    for (Cell off : vector<Cell>{{1, 0}, {0, 1}, {1, 1}, {1, -1}}) {
                        for (auto [i, j, k] : vector<array<int,3>>{{-2, -1, 1}, {-1, 1, 2}})
                            if (!f(c + i * off) && !f(c + j * off) && !f(c + k * off))
                                counter_threats.insert(c + j * off);
                    }
                }
            }
            if (empty(t) && !empty(counter_threats)) // We can win if team hasn't presented a threat.
                return *begin(counter_threats);
            set<Cell, decltype(cell_less)> weirds(cell_less);
            for (int row = 1; row <= R; row++) {
                for (Cell c{row, 1}; imag(c) <= C; c += 1i) {
                    if (f(c) != TEAM) continue;
                    for (Cell off : vector<Cell>{{1, 0}, {0, 1}, {1, 1}, {1, -1}})
                        for (int i : array{-1, 1})
                            if (!f(c + i * off))
                                weirds.insert(c + i * off);
                }
            }
            auto source = t;
            if (empty(source) || strategy == "COUNTER"s)
                source = counter_threats;
            if (empty(source) || strategy == "WEIRD"s) {
                source = weirds;
            }
            assert(!empty(source));
            return *next(begin(source), selector % size(source));
        } ();
        assert(!f(move));
        f(move) = JURY;
        toTeam << real(move) << ' ' << imag(move) << endl;
    }
}
