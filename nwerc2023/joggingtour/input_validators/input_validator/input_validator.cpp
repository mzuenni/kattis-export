#include "validation.h"

int main(int argc, char *argv[]) {
    InputValidator v(argc, argv);
    int n = v.read_integer("n", 2, 12);
    v.newline();

    for (int i = 0; i < n; i++) {
        v.read_integer("x", 0, 1e6);
        v.space();
        v.read_integer("y", 0, 1e6);
        v.newline();
    }
}
