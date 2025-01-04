#include "validation.h"

using i64 = int64_t;

constexpr i64 MAXN = 1e5;
constexpr i64 MAXL = 1e9;

int main(int argc, char *argv[]) {
    InputValidator v(argc, argv);
    i64 n = v.read_integer("n", 1, MAXN);
    v.space();
    i64 h = v.read_integer("h", 1, MAXL);
    v.newline();
    for (i64 i = 0; i < n; i++)
        v.read_integers("book_" + std::to_string(i), 3, 1, MAXL);
    return 0;
}
