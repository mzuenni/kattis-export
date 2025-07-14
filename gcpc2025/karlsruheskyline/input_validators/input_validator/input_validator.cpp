#include "validation.h"

int main(int argc, char *argv[]) {
    InputValidator v(argc, argv);
    int n = v.read_integer("n", 2, 1000);
    v.space();
    v.read_integer("a", 1, n);
    v.space();
    v.read_integer("b", 1, n);
    v.newline();
}
