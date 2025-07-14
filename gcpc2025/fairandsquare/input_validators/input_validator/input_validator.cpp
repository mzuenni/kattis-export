#include "validation.h"

int main(int argc, char *argv[]) {
    InputValidator v(argc, argv);
    int h = v.read_integer("h", 1, 2500);
    v.space();
    int w = v.read_integer("w", 1, 2500);
    v.newline();

    bool non_empty = false;
    while (h--) {
        auto s = v.read_string("s", w, w, ".#");
        for (char c: s) if (c == '#') non_empty = true;
        v.newline();
    }

    v.check(non_empty, "must have at least one '#'");
}
