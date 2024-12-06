// Similar to the powerset construction, but only applied to substrings of
// the cyclic string repeating 0011. This constructs linearly many sets of
// linear size, for quadratic overall running time.
#include <array>
#include <iostream>
#include <numeric>
#include <queue>
#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;
using i64 = long long;

const int N = 3e5 + 5;
const i64 MOD = i64(1e18) + 3;
i64 p2[N];

int X = 0;
int mark[N];

int main() {
    p2[0] = 1;
    for (int n = 1; n < N; n++) {
        p2[n] = 2*p2[n-1] % MOD;
    }

    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int &x: a) cin >> x;

    vector<vector<int>> adj(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int res = 1e9;
    for (int k = 0; k < 4; k++) {
        vector<int> cur;
        for (int x = 0; x < n; x++) {
            if (a[x] != (k%4) / 2) cur.push_back(x);
        }

        unordered_set<i64> seen;
        for (int i = 1; ; i++) {
            if (cur.empty()) {
                res = min(res, i);
                break;
            }

            i64 hash = 0;
            for (int x: cur) hash = (hash + p2[x]) % MOD;

            if (seen.count(hash)) break;
            seen.insert(hash);

            vector<int> nxt;
            X++;
            for (int x: cur) for (int y: adj[x]) {
                if (a[y] == ((i+k) % 4) / 2) continue;
                if (mark[y] != X) {
                    mark[y] = X;
                    nxt.push_back(y);
                }
            }
            cur = nxt;
        }
    }
    if (res < 1e9) cout << res << '\n';
    else cout << "infinity" << '\n';
}
