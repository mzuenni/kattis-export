#include "validation.h"

// One line with two integers n and k, the length of the name and the number of times to apply the function.
// One line with a string s, the current username.

int main(int argc, char** argv) {
    InputValidator v(argc, argv);
    int n = v.read_integer("n", 1, 100000);
    v.space();
    v.read_integer("k", 1, 1'000'000'000'000'000'000);
    v.newline();
    v.read_line("s", n, n, "abcdefghijklmnopqrstuvwxyz");
}
