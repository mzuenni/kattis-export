#include "validation.h"

// Read one integer d, the diameter of the outer ring.

int main(int argc, char *argv[]) {
    InputValidator v(argc, argv);
    int n = v.read_integer("d", 1, 1e9);
    v.newline();
}
