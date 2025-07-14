#include "validation.h"

// Check the grammar of the input files.
// You should also check properties of the input.
// E.g., check that a graph is connected.

const int maxn = 100000;

int main(int argc, char *argv[]) {
    InputValidator v(argc, argv);
    int n = v.read_integer("n", 2, maxn);
    v.space();
    int m = v.read_integer("m", 0, maxn);
    v.newline();
	
	std::set<std::pair<int, int>> E;

	for (int i = 0; i < m; i++) {
		int l = v.read_integer("l", 1, n);
		v.space();
		int r = v.read_integer("r", 1, n);
		v.newline();
		v.check(l != r, "Found a loop edge at node ", l, ".");
		v.check(E.count(std::make_pair(l, r)) == 0, "Edge (", l, ", ", r, ") occurs more than once.");
		E.insert(std::make_pair(l, r));
	}

	int a = v.read_integer("a", 1, n);
	v.space();
	int b = v.read_integer("b", 1, n);
	v.newline();
	v.check(a != b, "Starting points can not be equal (", a, ").");
}
