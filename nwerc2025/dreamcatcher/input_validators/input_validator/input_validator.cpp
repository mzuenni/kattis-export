#include "validation.h"

int main(int argc, char *argv[]) {
    InputValidator v(argc, argv);
    v.read_integer("n", 3, 1'000'000'000);
    v.newline();
    return 0;
}
