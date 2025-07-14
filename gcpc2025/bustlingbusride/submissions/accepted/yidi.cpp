#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)


#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag,
                  tree_order_statistics_node_update>;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, b, delay, w;
    cin >> n >> b >> delay >> w;
    vector<int> a(b);
    for (int& e : a) cin >> e;
    for (size_t i = 1; i < b; i++) a[i] += a[i-1];
    vector<int> c(n);
    for (int& e : c) cin >> e, e = a[e-1];

    constexpr ll INF = 2e18;
    ll l = 0, r = INF;
    while (l+1 < r) {
        ll mid = (l+r) / 2;
        int ptr = 0;
        for (int bus=0; ptr<n; bus++) {
            ll t = (ll)bus*delay;
            if (t + 2*w + c[ptr] > mid) break;

            Tree<int> tree;
            Tree<pair<int, int>> tree2;
            int mx = 0;
            while (ptr < n) {
                mx = max(mx, c[ptr]);
                t += (tree.order_of_key(c[ptr])) * w * 2;
                if (tree.find(c[ptr]) == tree.end()) {
                    t += ((ll)tree2.size() - tree2.order_of_key({c[ptr], ptr})) * w * 2;
                    tree.insert(c[ptr]);
                }
                tree2.insert({c[ptr], ptr});
                t += 2*w;
                if (t + mx > mid) break;
                ptr++;
            }
        }
        if (ptr < n) l = mid;
        else r = mid;
    }
    cout << r << '\n';
}
