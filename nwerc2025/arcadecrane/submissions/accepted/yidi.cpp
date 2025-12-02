#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int& e : a) cin >> e, e--;

    vector<array<int, 2>> ans;
    auto op = [&](int i, int j) {
        ans.push_back({i, j});
        vector<int> c;
        for (int it=0; it<3; it++) {
            c.push_back(a[i]);
            a.erase(a.begin() + i);
        }
        a.insert(a.begin() + j, all(c));
    };


    for (int i=n-1; i>=5; i--) {
        int j = find(all(a), i) - a.begin();
        if (j == i) continue;
        op(max(0, j-2), i-2);
        if (a[i] != i) i++;
    }

    a.resize(5);
    map<vector<int>, bool> vis;
    auto rec = [&](auto& self) {
        if (vis[a]) {
            return;
        }
        vis[a] = true;
        if (is_sorted(all(a))) {
            cout << ssize(ans) << '\n';
            for (auto [x, y] : ans) cout << x+1 << ' ' << y+1 << '\n';
        }

        for (int i=0; i<=2; i++) {
            for (int j=i+1; j<=2; j++) {
                auto olda = a;
                op(i, j);
                self(self);
                ans.pop_back();
                a = olda;
            }
        }
    };
    rec(rec);
}
