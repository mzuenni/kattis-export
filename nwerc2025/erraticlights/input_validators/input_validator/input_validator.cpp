#include "validation.h"

int main(int argc, char *argv[]) {
    InputValidator v(argc, argv);
    int n = v.read_integer("n", 1, 100);
    v.newline();
    v.read_line("lights", n, n, "rgb");
}
