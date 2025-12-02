#include "validation.h"

const long long MAXN = 100'000;
const long long MAXX = 1000;

int main(int argc, char *argv[]) {
    InputValidator v(argc, argv);

    auto n = v.read_integer("n", 2, MAXN);
    v.newline();
    for(int i=0; i<n; ++i) {
        auto a = v.read_integer("a", 1, MAXX);
        v.space();
        auto b = v.read_integer("b", 1, MAXX);
        v.newline();
    }

    return 0;
}
