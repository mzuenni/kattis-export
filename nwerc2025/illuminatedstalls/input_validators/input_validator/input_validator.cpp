#include "validate.h"
using namespace InputValidator;
using namespace std;

constexpr int MAX_T = 20'000;
constexpr int MIN_N = 4;
constexpr int MAX_N = 200'000;
constexpr int MIN_COORD = 0;
constexpr int MAX_COORD = 1e9;

int main(int argc, char **argv) {
    InputValidator::init(argc, argv);

    Integer t = testIn.integer(1, MAX_T + 1, constraint["t"]);
    testIn.newline();

    Integer sm_n = 0;
    for (int tt=0; tt<t; tt++) {
        Integer n = testIn.integer(MIN_N, MAX_N + 1, constraint["n"]);
        testIn.newline();
        sm_n += n;

        map<Integer, vector<pair<Integer, Integer>>> horizontal, vertical;

        for (int i=0; i<n; i++) {
            Integer x1 = testIn.integer(MIN_COORD, MAX_COORD + 1, constraint["x"]);
            testIn.space();
            Integer y1 = testIn.integer(MIN_COORD, MAX_COORD + 1, constraint["y"]);
            testIn.space();
            Integer x2 = testIn.integer(MIN_COORD, MAX_COORD + 1, constraint["x"]);
            testIn.space();
            Integer y2 = testIn.integer(MIN_COORD, MAX_COORD + 1, constraint["y"]);
            testIn.newline();

            if (pair{x1, y1} == pair{x2, y2}) {
                juryOut << "Line segment " << i+1 << ": ";
                juryOut << "endpoints are not distinct" << WA;
            }
            if (x1 > x2 || y1 > y2) {
                juryOut << "Line segment " << i+1 << ": ";
                juryOut << "X- or Y-coordinates of the second endpoint not larger than first" << WA;
            }
            if (x1 != x2 && y1 != y2) {
                juryOut << "Line segment " << i+1 << ": ";
                juryOut << "segment is neither vertical nor horizontal" << WA;
            }

            if (x1 == x2) {
                vertical[x1].emplace_back(y1, y2);
            }
            if (y1 == y2) {
                horizontal[y1].emplace_back(x1, x2);
            }
        }

        for (auto mp : array{horizontal, vertical}) {
            for (auto [_, vec] : mp) {
                sort(vec.begin(), vec.end());
                for (int i=1; i<ssize(vec); i++) {
                    if (vec[i].first <= vec[i-1].second) {
                        juryOut << "Found two intersecting line segments" << WA;
                    }
                }
            }
        }
    }

    if (sm_n > MAX_N) {
        juryOut << "Sum over n is too high (" << sm_n << ")" << WA;
    }

    testIn.eof();
    juryOut << AC;
}
