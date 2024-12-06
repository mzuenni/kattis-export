#include "validation.h"

int main(int argc, char *argv[]) {
    InputValidator v(argc, argv);
    int n = v.read_integer("n", 1, 60);
    v.newline();
    v.read_integers("p", n, 1, 10000);
}
