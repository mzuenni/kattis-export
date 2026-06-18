#include "validation.h"
#include "constraints.h"

int main(int argc, char *argv[]) {
    InputValidator v(argc, argv);
    int n = v.read_integer("n", 2, MAX_N);
    v.space();
    v.read_integer("k", 1, n);
    v.newline();

    for (int i = 2; i <= n; i++) {
        v.read_integer("p_i", 1, i-1);
        if (i < n)
            v.space();
    }
    v.newline();
}
