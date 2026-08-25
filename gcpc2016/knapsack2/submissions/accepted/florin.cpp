#include <iostream>
#include <algorithm>
#include <climits>
#include <set>

#define MAX_N 105
#define MAX_G 1000005

using namespace std;

typedef pair<long long, int> plli;

int main () {
    long long N, K, g[MAX_N], d[MAX_G];

    cin >> N >> K;
    for (int i = 0; i < N; ++i) cin >> g[i];
    for (int i = 0; i < g[0]; ++i) d[i] = LLONG_MAX;
    

    set<plli> q;
    q.insert (make_pair(0, 0));
    d[0] = 0;
    while (!q.empty()) {
        plli node = *q.begin();
        q.erase (q.begin());
        
        if (node.first != d[node.second])
            continue;
        for (int i = 1; i < N; ++i) {
            int target = (node.second + g[i]) % g[0];
            if (d[target] > node.first + g[i]) {
                d[target] = node.first + g[i];
                
                q.insert (make_pair(node.first + g[i], target));
            }
        }
    }

    if (d[K%g[0]] <= K)
        cout << "possible\n";
    else
        cout << "impossible\n";

    return 0;
}