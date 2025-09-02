#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include <cassert>

typedef long long ll;

using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

constexpr int CORRECT = 42;
constexpr int INCORRECT = 43;

int main(int argc, char* argv[])
{
    assert(argc == 4);

    ifstream input(argv[1]);
    ifstream answer(argv[2]);
    ofstream debug_output(argv[3] + string("/judgemessage.txt"));

    string s1, s2;
    answer >> s1;
    cin >> s2;

    if (s1 != s2 && (s1 == "impossible" || s2 == "impossible")) {
        debug_output << "Expected: " << s1 << ", got: " << s2 << endl;
        return INCORRECT;
    }

    if (s1 != "impossible") {
        ll x, y;
        std::stringstream first_token(s2);
        if (!(first_token >> x) || !(cin >> y)) {
            debug_output << "Too little output" << endl;
            return INCORRECT;
        }

        if (!cin || x <= 0 || y <= 0) {
            debug_output << "Presentation Error" << endl;
            return INCORRECT;
        }

        if (std::numeric_limits<ll>::max() / x < y) {
            debug_output << "Area too large." << endl;
            return INCORRECT;
        }

        ll n;
        input >> n;
        vector<ll> cnt(n + 1);
        for (ll& i: cnt) input >> i;

        ll current_area = 0;
        for (int k = n; k >= 0; --k) {
            ll border_length = 1ll << k;
            current_area += border_length * border_length * cnt[k];
            ll a = (x / border_length) * border_length;
            ll b = (y / border_length) * border_length;
            if (a * b < current_area) {
                debug_output << "Incorrect dimensions, cannot fit all squares of size " << border_length << " and larger." << endl;
                return INCORRECT;
            }
        }

        if (current_area != x * y) {
            debug_output << "Area is " << x * y << ", should be " << current_area << "." << endl;
            return INCORRECT;
        }
    }

    char c;
    if (cin >> c) {
        debug_output << "Too much output." << endl;
        return INCORRECT;
    }

    return CORRECT;
}
