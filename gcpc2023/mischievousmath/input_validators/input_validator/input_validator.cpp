#include "validation.h"

int main(int argc, char** argv) {
    InputValidator v(argc, argv);
    v.read_integer("d", 1, 100);
    v.newline();
}
