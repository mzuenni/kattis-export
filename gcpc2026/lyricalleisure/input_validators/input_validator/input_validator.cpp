#include "validation.h"

// Check the grammar of the input files.
// You should also check properties of the input.
// E.g., check that a graph is connected.

int main(int argc, char *argv[]) {
    InputValidator v(argc, argv);
    int n = v.read_integer("n", 1, 5000);
    v.space();
    int k = v.read_integer("k", 1, n);
    v.newline();
    return 0;
}
