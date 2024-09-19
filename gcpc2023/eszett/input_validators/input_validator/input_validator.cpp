#include "validation.h"

int main(int argc, char** argv) {
    InputValidator v(argc, argv);

    std::string alphabet(26, '.');
    std::iota(std::begin(alphabet), std::end(alphabet), 'A');

    auto s = v.read_string("s", 1, 20, alphabet);
    v.newline();

    int count = 0;
    for (char c: s) count += c == 'S';
    v.check(count <= 3, "S may occur at most three times");
}
