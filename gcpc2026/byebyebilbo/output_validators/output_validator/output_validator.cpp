#include "validate.h"
#include "constraints.h"
using namespace OutputValidator;
using namespace std;

int read_input(auto& in, int n, int k, const vector<Integer>& p, Verdict fail) {
    int m = in.integer(); in.newline();
    
    vector<int> s(n, 0);
    for (int i = 0; i < m; i++) {
        int u = in.integer(1, n + 1);
        if (i + 1 < m)
            in.space();
        u--;
        if (s[u]) {
            juryOut << "duplicate node in output" << fail;
        }
        s[u] = 1;
    }
    in.newline();
    in.eof();
    vector<int> d(n);
    if (!s[0]) {
        juryOut << "root has to be chosen" << fail;
    }
    for (int i = 1; i < n; i++) {
        d[i] = !s[i] * (d[p[i-1]-1] + 1);
        if (d[i] >= k) {
            juryOut << "distance to nearest parent has to be < k" << fail;
        }
    }
    return m;
}

int main(int argc, char *argv[]) {
    init(argc, argv);
    int n = testIn.integer();
    int k = testIn.integer();
    vector<Integer> p = testIn.integers(n - 1);
    int jury_m = read_input(juryAns, n, k, p, FAIL);
    int team_m = read_input(teamAns, n, k, p, WA);

    if (team_m < jury_m) {
        juryOut << "Team found better answer " << team_m << " < " << jury_m << FAIL;
    } else if (team_m > jury_m) {
        juryOut << "Jury found better answer " << team_m << " > " << jury_m << WA;
    } else {
        juryOut << "Ok" << AC;
    }
}
