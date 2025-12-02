#include "validation.h"

// Read one floating-point number as answer.

int main(int argc, char *argv[]) {
    AnswerValidator v(argc, argv);
    int answer = v.read_float("answer", M_PIl / 2 - 1 - 1e-15, 1e9L * M_PIl / 2 - 1e9 + 1e-6);
    v.newline();
}
