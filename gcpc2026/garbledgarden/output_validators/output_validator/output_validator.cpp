#include "validate.h"
using namespace std;
using namespace OutputValidator;

int check_ans(InputStream& ans, vector<Integer> a, Verdict verdict) {
    int n = ssize(a);
    int op = ans.integer(0, n+1, constraint["k"]);
    ans.newline();

    for (int o=0; o<op; o++) {
        int k = ans.integer(1, n+1, constraint["m"]);
        ans.newline();
        vector<Integer> b = ans.integers(k, 1, n+1, constraint["p_i"], ' ');
        ans.newline();
        if (!areDistinct(b)) {
            juryOut << "Not all integers distinct in operation " << o+1 << verdict;
        }

        auto a2 = a;
        for (int i=0; i<k; i++) {
            a[b[i] - 1] = a2[b[(i+1)%k] - 1];
        }
    }
    ans.eof();
    if (!is_sorted(a.begin(), a.end())) {
        juryOut << "Array not sorted" << verdict;
    }
    return op;
}

int main(int argc, char **argv) {
    OutputValidator::init(argc, argv);

    Integer n = testIn.integer();
    vector<Integer> a = testIn.integers(n);

    Integer jury_ans = check_ans(juryAns, a, FAIL);
    Integer team_ans = check_ans(teamAns, a, WA);

    if (team_ans < jury_ans) {
        juryOut << "Team found better answer "
                << team_ans << " < " << jury_ans << " ???" << FAIL;
    }
    if (jury_ans < team_ans) {
        juryOut << "Jury found better answer " 
                << jury_ans << " < " << team_ans << WA;
    }

    juryOut << "Ok" << AC;
}
