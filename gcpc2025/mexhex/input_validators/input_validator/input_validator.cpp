#include "validation.h"

int main(int argc, char *argv[]) {
  InputValidator v(argc, argv);
  const auto n = v.read_integer("n", 1, 100000);
  v.space();
  const auto d = v.read_integer("d", 1, n);
  v.newline();

  const auto a = v.read_integers("a", n, 0, n - 1);
}
