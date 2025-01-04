#include "validation.h"

int main(int argc, char *argv[]) {
    InputValidator v(argc, argv);
    int h = v.read_integer("h", 1, 100);
    v.space();
    int w = v.read_integer("w", 1, 100);
    v.newline();
}
