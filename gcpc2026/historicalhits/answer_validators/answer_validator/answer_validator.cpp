#include "validation.h"

const ssize_t MOD = 998244353;

int main(int argc, char *argv[]) {
  AnswerValidator v(argc, argv);
  v.read_integer("answer", 0, MOD - 1);
  v.newline();
}
