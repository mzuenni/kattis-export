#include "validation.h"

// Check the grammar of the input files.
// You should also check properties of the input.
// E.g., check that a graph is connected.

const int MAXN = 1e5, MAXB = 1e5;
const long long MAXW = 1e6, MAXR = 1e6, MAXD = 1e6;

int main(int argc, char *argv[]) {
    InputValidator v(argc, argv);
    int n = v.read_integer("n", 1, MAXN);
    v.space();
    int b = v.read_integer("b", 1, MAXB);
    v.space();
    long long r = v.read_integer("r", 1, MAXR);
    v.space();
    long long w = v.read_integer("w", 1, MAXW);
    v.newline();

    const auto ds = v.read_integers("ds", b, 1, MAXD);
    long long sum_ds = 0;
    for (auto& d : ds) sum_ds += d;
    assert(sum_ds <= MAXD);


    v.read_integers("ts", n, 1, b);
    return 0;
}
