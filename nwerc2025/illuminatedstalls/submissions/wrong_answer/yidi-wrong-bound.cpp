#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

constexpr ll INF = 1e18;
ll len(array<ll, 4>& x) {
    return abs(x[2] - x[0]) + abs(x[3] - x[1]);
}

bool solve(vector<array<ll, 4>> a, ll l) {
    int n = ssize(a);

    vector<array<ll, 3>> horis;
    vector<array<ll, 5>> events;
    for (int i=0; i<n; i++) {
        auto [x1, y1, x2, y2] = a[i];
        if (x1 == x2) {
            events.push_back({x1, 1, y1, y2, i});
        } else {
            events.push_back({x1, 0, y1, -1, i});
            events.push_back({x2, 2, y1, -1, i});
            horis.push_back({y1, x1, x2});
        }
    }
    sort(all(events));
    sort(all(horis));

    vector<vector<array<ll, 2>>> inters(n);
    int counter = 0;
    auto add = [&](int hori, ll h, ll x) {
        inters[hori].push_back({h, x});
    };
    
    set<array<ll, 2>> act;
    for (auto [x, type, y1, y2, ind] : events) {
        if (type == 0) act.insert({y1, ind});
        if (type == 2) act.erase({y1, ind});
        if (type == 1) {
            for (auto it=act.lower_bound({y1, -1}); it!=act.end() && it->at(0) <= y2; it++) {
                add(it->at(1), y2 - it->at(0), x);
                if (++counter > 1*n) return true;
            }
        }
    }

    auto connect = [&](ll y, ll x1, ll x2) {
        if (x2 < x1) swap(x1, x2);
        ll needed = x2 - x1;
        auto it = upper_bound(all(horis), array{y, x1+1, -INF});
        if (it != horis.begin()) {
            it--;
            if (it->at(0) == y) needed -= max(0LL, it->at(2) - x1);
        }
        it = upper_bound(all(horis), array{y, x2, -INF});
        if (it != horis.begin()) {
            it--;
            if (it->at(0) == y && it->at(2) >= x2) needed -= max(0LL, x2 - it->at(1));
        }
        return needed;
    };

    for (int i=0; i<n; i++) {
        auto& vec = inters[i];
        sort(all(vec), greater<>());
        set<ll> s = {{-INF, INF}};
        for (auto [h, x] : vec) {
            auto it = s.insert(x).first;
            for (auto x2 : {*prev(it), *next(it)}) {
                ll d = abs(x2 - x);
                if (d <= h && connect(a[i][1] + d, x, x2) <= l) return true;
            }
        }
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<array<ll, 4>> a(n);
        for (auto& [x1, y1, x2, y2] : a) cin >> x1 >> y1 >> x2 >> y2;
        sort(all(a), [&](auto& x, auto& y) {
            return len(x) < len(y);
        });
        for (int i=1; i<=min(n, 6); i++) {
            auto b = a;
            ll l = len(a.end()[-i]);
            b.erase(b.end() - i);
            for (int rot=0; rot<4; rot++) {
                if (solve(b, l)) {
                    cout << "yes\n";
                    goto done;
                }
                for (auto& [x1, y1, x2, y2] : b) {
                    swap(x1, y1), swap(x2, y2);
                    y1 = -y1, y2 = -y2;
                    swap(y1, y2);
                    assert(x1 <= x2 && y1 <= y2);
                }
            }
        }
        cout << "no\n";
done:;
    }
}
