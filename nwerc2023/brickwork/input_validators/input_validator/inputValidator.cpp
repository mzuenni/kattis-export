#include "validation.h"

int main(int argc, char *argv[]) {
    InputValidator v(argc, argv);
    int n = v.read_integer("n", 1, 300'000);
    v.space();
    int w = v.read_integer("w", 1, 300'000);
    v.newline();
    for (int i = 0; i < n; i++) {
        v.read_integer("b", 1, w);
        if (i + 1 < n) {
            v.space();
        } else {
            v.newline();
        }
    }
}
