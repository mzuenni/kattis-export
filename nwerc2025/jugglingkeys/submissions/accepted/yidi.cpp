#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k, q;
    cin >> n >> k >> q;

    vector<array<int, 4>> events, events2;
    vector<array<int, 3>> a(q);
    for (int i=0; i<q; i++) {
        int l, r, ind;
        cin >> ind >> l >> r;
        a[i] = {l, r, ind};
        events.push_back({l, 1, ind, i});
        events.push_back({r, 0, ind, i});
    }
    sort(all(events));

    string s(q, '0');
    for (auto [x, type, ind, ind2] : events) {
        if (type == 0) {
            if (n == 0) {
                events2.push_back({a[ind2][0], 1});
                events2.push_back({a[ind2][1], 0});
                s[ind2] = '1';
            }
            n++;
        } else n--;
    }

    sort(all(events2));
    for (auto [x, type, _, __] : events2) {
        if (type == 1) {
            k--;
            if (k < 0) {
                cout << "IMPOSSIBLE\n";
                return 0;
            }
        } else k++;
    }

    cout << s << '\n';
}
