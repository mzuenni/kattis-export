#include "validation.h"
using namespace std;

int main(int argc, char *argv[]) {
	InputValidator v(argc, argv);
	int n = v.read_integer("n", 1, 300);
	v.newline();

	set<pair<char,int>> cards;
	for (int i = 0; i < n; i++) {
		char op = v.read_string("op", 1, 1, "+*")[0];
		v.space();
		int x = v.read_integer("x", 1, 1e6);
		v.newline();
		cards.emplace(op, x);
	}

	v.check(ssize(cards) == n, "Cards must be distinct.");

	v.read_integer("start", 1, 1e6);
	v.newline();

	v.read_integer("seed", 0, (1LL << 32) - 1);
	v.newline();

	string mode = v.test_strings({"random", "smart", "prio"}, "mode");
    if (mode == "prio") {
        v.space();
        auto a = v.read_integers("a", 3, 0, 2, Unique); // this includes the newline()
    } else {
        v.newline();
    }
}
