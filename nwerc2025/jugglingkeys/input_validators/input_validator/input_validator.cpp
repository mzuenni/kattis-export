#include "validation.h"
using namespace std;

const long long MAXN = 100'000;
const long long MAXQ = 100'000;
const long long MAXT = 1000'000'000;

int main(int argc, char *argv[]) {
    InputValidator v(argc, argv);

    int n = v.read_integer("n", 1, MAXN);
    v.space();
    int k = v.read_integer("k", 1, n);
    v.space();
    int q = v.read_integer("q", 1, MAXQ);
    v.newline();

    set<int> time_set;

    vector<vector<pair<int,int>>> trips(n, vector<pair<int,int>>());

    for(int i = 0; i < q; i++){
        int ni = v.read_integer("ni", 1, n);
        v.space();
        int t1 = v.read_integer("t1", 0, MAXT-1);
        v.space();
        int t2 = v.read_integer("t2", 1, MAXT);
        v.newline();
        assert(t1 < t2);
        time_set.insert(t1);
        time_set.insert(t2);
        trips[ni-1].push_back({t1, t2});
    }

    assert(time_set.size() == 2*q); // All times are distinct

    // Check that trips from one person are non-overlapping
    for(int i = 0; i < n; i++){
        sort(trips[i].begin(), trips[i].end());
        for(int j = 1; j < trips[i].size(); j++){
            assert(trips[i][j].first > trips[i][j-1].second);
        }
    }

    return 0;
}
