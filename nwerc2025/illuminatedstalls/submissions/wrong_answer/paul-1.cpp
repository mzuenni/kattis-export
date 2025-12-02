#include <bits/stdc++.h>
using namespace std;

struct segment {
    int x1, y1, x2, y2;
};

bool solve() {
    int n; cin >> n;
    vector<segment> a(n);

    vector<pair<int,int>> by_length(n);
    vector<tuple<int,int,int>> events;
    for (int i = 0; i < n; i++) {
        auto &[x1, y1, x2, y2] = a[i];
        cin >> x1 >> y1 >> x2 >> y2;
        by_length[i] = make_pair(x2-x1 + y2-y1, i);
        if (x1 == x2) {
            events.emplace_back(x1, 0, i);
        } else {
            events.emplace_back(x1, -1, i);
            events.emplace_back(x2, 1, i);
        }
    }
    sort(begin(events), end(events));
    sort(begin(by_length), end(by_length), greater<>());

    auto longest_without = [&](vector<int> v) {
        for (auto [len, i]: by_length) {
            if (find(begin(v), end(v), i) == end(v)) return len;
        }
        return 0;
    };

    int crossings = 0;
    vector<vector<int>> adj(n);
    map<pair<int,int>,int> cross_xor;

    map<int,int> active;
    for (auto [x, t, i]: events) {
        if (t == 0) {
            for (auto it = active.lower_bound(a[i].y1);
                    it != end(active) && it->first <= a[i].y2; it++) {
                adj[i].push_back(it->second);
                adj[it->second].push_back(i);
                cross_xor[make_pair(x, it->first)] = i ^ (it->second);
                if (++crossings > 4*n) return true;
            }
        } else if (t == -1) {
            active[a[i].y1] = i;
        } else {
            active.erase(a[i].y1);
        }
    }

    for (int flip = 0; flip < 2; flip++) {
        for (int i = 0; i < n; i++) {
            if (a[i].x1 == a[i].x2) continue;
            int y = a[i].y1;
            for (int above = 0; above < 2; above++) {
                vector<pair<int,int>> stk;
                for (int j: adj[i]) {
                    int x = a[j].x1;
                    int h = above ? a[j].y2 - y : y - a[j].y1;
                    while (!stk.empty() && stk.back().first < x) stk.pop_back();
                    if (!stk.empty()) {
                        int k = stk.back().second, px = a[k].x1;
                        int len = x - px, py = y + (above ? len : -len), gap = len;
                        pair<int,int> p = make_pair(px, py), q = make_pair(x, py);
                        vector<int> v = {i, j, k};
                        if (cross_xor.count(p)) {
                            int l = k ^ cross_xor[p];
                            gap -= a[l].x2 - px;
                            v.push_back(l);
                        }
                        if (cross_xor.count(q)) {
                            int l = j ^ cross_xor[q];
                            gap -= x - a[l].x1;
                            v.push_back(l);
                        }
                        if (longest_without(v) >= gap) return true;
                    }
                    stk.emplace_back(h+x, j);
                }
            }
        }

        for (auto &[x1, y1, x2, y2]: a) {
            swap(x1, y1), swap(x2, y2);
        }
    }

    return false;
}

int main() {
    int tc; cin >> tc;
    while (tc--) {
        cout << (solve() ? "yes" : "no") << '\n';
    }
}
