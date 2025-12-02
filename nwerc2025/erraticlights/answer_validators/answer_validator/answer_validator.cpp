#include "validation.h"

int main(int argc, char *argv[]) {
    AnswerValidator v(argc, argv);
    v.read_float("answer", 0, 192.57247826247476041316986083984375L);
    v.newline();
}
