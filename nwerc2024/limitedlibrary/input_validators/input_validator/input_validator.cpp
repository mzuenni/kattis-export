#include "validation.h"

int main(int argc, char** argv) {
    InputValidator v(argc, argv);
    int n = v.read_integer("n", 1, 100'000);
    v.space();
    int m = v.read_integer("m", 1, 100'000);
    v.space();
    int x = v.read_integer("x", 2, 1000);
    v.space();
    int y = v.read_integer("y", 1, x-1);
    v.newline();
    v.read_integers("a", n, 1, 1'000'000'000);
    v.read_integers("b", m, 1, 1'000'000'000);
}