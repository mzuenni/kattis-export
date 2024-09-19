#include "validation.h"
using namespace std;
using i64 = long long;

int main(int argc, char **argv) {
    ifstream in(argv[1]);
    OutputValidator v(argc, argv);

    vector<int> dice;
    for (int s: {4, 6, 8, 12, 20}) {
        int k; in >> k;
        while (k--) dice.push_back(s);
    }
    
    // find the size of the middle bucket
    int mid = dice.back();
    for (int i = 0; i+1 < int(dice.size()); i++) {
        mid -= dice[i]-1;
    }
    while (mid <= 0) mid += 2;

    vector<set<int>> buckets;
    int lo = dice.size(), hi = accumulate(begin(dice), end(dice), 0);
    while (hi-lo > mid) {
        buckets.push_back({lo++, hi--});
    }
    buckets.push_back({});
    while (lo <= hi) buckets.back().insert(lo++);
    reverse(begin(buckets), end(buckets));

    bool first = true;
    for (auto b: buckets) {
        while (!b.empty()) {
            if (first) first = false;
            else v.space();
            int x = v.read_integer("x", 1, 500);
            v.check(b.count(x), "invalid order");
            b.erase(x);
        }
    }
    v.newline();
}
