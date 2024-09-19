#include "validation.h"

// Check the grammar of the input files.
// You should also check properties of the input.
// E.g., check that a graph is connected.

int h = 7;
int w = 24;

int main(int argc, char** argv) {
	InputValidator v(argc, argv);
	v.read_strings("s", h, w, w, "x.", Arbitrary, Newline);
	v.read_integer("d", 1, 7);
	v.space();
	v.read_integer("h", 1, 24);
	v.newline();
}
