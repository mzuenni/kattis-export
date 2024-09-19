#include "validation.h"

int main(int argc, char** argv) {
    InputValidator v(argc, argv);
    v.read_integer("n", 1, 1e9);
    v.newline();
}
