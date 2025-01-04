#include "validation.h"

int main(int argc, char *argv[]) {
    InputValidator v(argc, argv);
    v.read_string("s", 1, 500'000, "bdpq");
    v.newline();
    v.read_string("s", 1, 500'000, "hvr");
    v.newline();
}
