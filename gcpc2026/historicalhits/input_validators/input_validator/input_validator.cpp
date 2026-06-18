#include <map>
#include <vector>

#include "validation.h"

const ssize_t MAX_YEAR = 1e9;

int main(int argc, char *argv[]) {
  InputValidator v(argc, argv);
  const auto n = v.read_integer("n", 1, 3000);
  v.newline();

  std::map<long long, ssize_t> a;
  std::vector<long long> b;

  for (ssize_t i = 1; i <= n; ++i) {
    const auto ai = v.read_integer("ai", 1, MAX_YEAR, Unique);
    v.space();
    const auto bi = v.read_integer("bi", 1, MAX_YEAR);
    v.newline();

    a[ai] = i;
    b.push_back(bi);
  }

  for (ssize_t i = 1; i <= n; ++i) {
    if (const auto it = a.find(b[i - 1]); it != a.end()) {
      v.check(it->second == i, "Guessed year cannot equal correct year of other card.");
    }
  }
}
