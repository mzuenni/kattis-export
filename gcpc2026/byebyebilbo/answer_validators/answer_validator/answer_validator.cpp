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
    ifstream in(argv[1]);
    AnswerValidator v(argc, argv);

    int n, k;
    in >> n >> k;
    vector<int> p(n);
    for (int i = 1; i < n; i++) {
        in >> p[i];
        p[i]--;
    }

    int m = v.read_integer("m", 1, n);
    v.newline();
    vector<int> s(n, 0);
    for (int i = 0; i < m; i++) {
        int u = v.read_integer("u", 1, n);
        u--;
        if (i + 1 < m)
            v.space();
        else
            v.newline();
        ASSERT(!s[u], "duplicate node in output");
        s[u] = 1;
    }
    vector<int> d(n);
    for (int i = 1; i < n; i++) {
        d[i] = !s[i] * (d[p[i]] + 1);
        ASSERT(d[i] < k, "distance to nearest parent has to be < k");
    }
}
