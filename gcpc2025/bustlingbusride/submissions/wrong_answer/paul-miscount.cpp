#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
using i64 = long long;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    int n, m, gap, onoff;
    cin >> n >> m >> gap >> onoff;
    vector<int> p(m), xs(n);
    for (int &x: p) cin >> x;
    for (size_t i = 1; i < m; i++) p[i] += p[i-1];
    for (int &x: xs) cin >> x, x = p[x-1];

    auto solve = [&](i64 T) {
        for (int i = 0, k = 0; i < n; k++) {
            i64 count = 0;
            ordered_set<int> stops;
            ordered_set<pair<int,int>> people;
            int j = i, xmax = 0;
            for (; j < n; j++) {
                xmax = max(xmax, xs[j]);
                count += stops.order_of_key(xs[j]);
                stops.insert(xs[j]).second;
                auto pr = make_pair(xs[j], j);
                count += people.size() - people.order_of_key(pr);
                people.insert(pr);
                count++;
                if (i64(k)*gap + 2*count*onoff + xmax > T) {
                    if (j == i) return false;
                    break;
                }
            }
            i = j;
        }
        return true;
    };
    
    i64 lo = 0, hi = 1e13;
    while (hi-lo > 1) {
        i64 md = (lo+hi) / 2;
        (solve(md) ? hi : lo) = md;
    }
    cout << hi << '\n';
}
