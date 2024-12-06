#include "validation.h"

// Check the grammar of the input files.
// You should also check properties of the input.
// E.g., check that a graph is connected.

int main(int argc, char *argv[]) {
    InputValidator v(argc, argv);
    int n = v.read_integer("n", 1, 200'000);
    v.newline();
    v.read_integers("v", n, 1, n);
    return 0;
}
