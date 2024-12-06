#include "validation.h"

// Check the grammar of the input files.
// You should also check properties of the input.
// E.g., check that a graph is connected.

int main(int argc, char* argv[]) {
	InputValidator v(argc, argv);
	int n = 5;

	std::set<std::pair<int, int>> coords;

	for(int i = 0; i < n; ++i) {
		int x = v.read_integer("x", 0, 1000);
		v.space();
		int y = v.read_integer("y", 0, 1000);
		v.newline();
		coords.insert({x, y});
	}
	v.check(coords.size() == n, "Coordinates must be unique");
}
