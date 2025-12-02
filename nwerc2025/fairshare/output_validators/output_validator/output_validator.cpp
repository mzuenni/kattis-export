#include "validation.h"
#include <numeric>
#include <algorithm>
using namespace std;

bool works(vector<int>& pay, vector<int>& owe) {
    vector<int> ids(size(pay));
    iota(begin(ids), end(ids), 0);
    auto ans = *max_element(begin(ids), end(ids), [&](int i, int j) { return owe[i] - pay[i] < owe[j] - pay[j]; });
    auto total_bill = accumulate(begin(owe), end(owe), 0ll);
    auto total_paid = accumulate(begin(pay), end(pay), 0ll);
    return total_paid - pay[ans] + owe[ans] >= total_bill;
}

int main(int argc, char *argv[]) {
    std::ifstream in(argv[1]);
    std::ifstream ans(argv[2]);
    OutputValidator team(argc, argv);

    int n; in>>n;
    vector pay(n,0), owe(n,0);
    for(int i=0; i<n; ++i) in>>pay[i]>>owe[i];

    if(!works(pay, owe)) {
        team.test_string("impossible");
        team.newline();
        team.eof_and_AC();
    }

    auto team_i = team.read_integer("i",1,n)-1;
    team.newline();
    auto total_bill = accumulate(begin(owe), end(owe), 0ll);
    auto total_paid = accumulate(begin(pay), end(pay), 0ll);
    auto rem = total_bill - (total_paid - pay[team_i]);
    team.check(rem<=owe[team_i], "person pays more than their share");
}
