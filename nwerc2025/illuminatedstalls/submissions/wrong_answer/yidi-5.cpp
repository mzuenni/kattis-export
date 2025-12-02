#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

ll len(array<ll, 4>& x) {
    return abs(x[2] - x[0]) + abs(x[3] - x[1]);
}

bool solve(vector<array<ll, 4>> a) {
    int n = ssize(a);

    vector<int> len_sorted(n + 6);
    for (int i=0; i<n; i++) len_sorted[i] = len(a[i]);
    sort(all(len_sorted), greater<>());

    auto longest = [&](array<int, 5> b) {
        for (int& e : b) {
            if (e != -1) e = len(a[e]);
        }
        sort(all(b), greater<>());
        for (int i=0; i<6; i++) if (b[i] != len_sorted[i]) return len_sorted[i];
        return 0;
    };

    vector<array<ll, 5>> events;
    for (int i=0; i<n; i++) {
        auto [x1, y1, x2, y2] = a[i];
        if (x1 == x2) {
            events.push_back({x1, 1, y1, y2, i});
        } else {
            events.push_back({x1, 0, y1, -1, i});
            events.push_back({x2, 2, y1, -1, i});
        }
    }
    sort(all(events));

    vector<vector<int>> inters(n);
    int counter = 0;
    set<array<ll, 2>> act;
    for (auto [x, type, y1, y2, ind] : events) {
        if (type == 0) act.insert({y1, ind});
        if (type == 2) act.erase({y1, ind});
        if (type == 1) {
            for (auto it=act.lower_bound({y1, -1}); it!=act.end() && it->at(0) <= y2; it++) {
                inters[it->at(1)].push_back(ind);
                inters[ind].push_back(it->at(1));
                if (counter++ > 2*n) return true;
            }
        }
    }

    for (int rot=0; rot<4; rot++) {
        for (int i=0; i<n; i++) {
            auto [x1, y1, x2, y2] = a[i];
            if (y1 != y2) continue;
            sort(all(inters[i]), [&](int i, int j) { return a[i][0] < a[j][0]; });

            for (int j=0; j<ssize(inters[i]); j++) {
                auto [x3, _, __, y3] = a[inters[i][j]];
                for (int k=j+1; k<ssize(inters[i]); k++) {
                    auto [x4, ___, ____, y4] = a[inters[i][k]];
                    int dx = x4 - x3;
                    if (y3 - y1 < dx) break;
                    if (y4 - y1 < dx) continue;

                    // U shape with size dx found
                    int j2 = inters[i][j], k2 = inters[i][k];
                    int ind1 = -1, reach1 = 0;
                    int ind2 = -1, reach2 = 0;
                    for (int e : inters[j2]) {
                        if (a[e][1] == y1 + dx) ind1 = e, reach1 = a[e][2] - x3;
                    }
                    for (int e : inters[k2]) {
                        if (a[e][1] == y1 + dx) ind2 = e, reach2 = x4 - a[e][0];
                    }
                    
                    int mx = max({
                        //longest({i, j2, k2, ind1, -1}) + reach1,
                        longest({i, j2, k2, ind2, -1}) + reach2,
                        longest({i, j2, k2, ind1, ind2}) + reach1 + reach2
                    });
                    if (mx >= dx) return true;
                }
            }
        }

        for (auto& [x1, y1, x2, y2] : a) {
            tie(x1, y1, x2, y2) = tuple{y1, -x2, y2, -x1};
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
        cout << (solve(a) ? "yes\n" : "no\n");
    }
}
