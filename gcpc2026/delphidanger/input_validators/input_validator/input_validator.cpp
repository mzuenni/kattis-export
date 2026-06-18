#include "validation.h"
#include "constraints.h"
using namespace std;

void ASSERT(bool cond, string msg) {
    if (!cond) {
        cerr << msg << endl;
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    InputValidator iv(argc, argv);
    int n = iv.read_integer("n", 2, MAX_N);
    iv.space();
    int m = iv.read_integer("m", 1, MAX_M);
    iv.newline();
    set<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u = iv.read_integer("u_i", 1, n);
        iv.space();
        int v = iv.read_integer("v_i", 1, n);
        iv.space();
        ASSERT(u != v, "no self loops allowed");
        iv.read_integer("t_i", 0, MAX_T);
        iv.newline();
        if (u > v)
            swap(u, v);
        pair<int, int> e = make_pair(u, v);
        ASSERT(!edges.count(e), "no duplicate edges allowed");
        edges.insert(e);
    }
    return 0;
}
