#include "validation.h"

int main(int argc, char *argv[]) {
    InputValidator v(argc, argv);
    int h = v.read_integer("h", 3, 100);
    v.space();
    int w = v.read_integer("w", 3, 100);
    v.space();
    int k = v.read_integer("k", 1, h*w-2);
    v.space();
    int i = v.read_integer("i", 1, h*w-k-1);
    v.space();
    int t = v.read_integer("t", h*w-k-i, h*w-k-i);
    v.newline();
}
