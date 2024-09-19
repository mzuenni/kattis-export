#include "validation.h"

// An integer n, the length of one of the sides of the square.
// Two pairs of integers, the number of sideways and forwards steps you need to alternate between.

int main(int argc, char *argv[]) {
    InputValidator v(argc, argv);
    int n = v.read_integer("n", 3, 500);
    v.newline();

	v.read_integer("a", 1, n-1);
	v.space();
	v.read_integer("b", 1, n-1);
	v.newline();

	v.read_integer("c", 1, n-1);
	v.space();
	v.read_integer("d", 1, n-1);
	v.newline();
}
