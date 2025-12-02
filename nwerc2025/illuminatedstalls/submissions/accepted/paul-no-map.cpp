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

    map<int,int> active;
    for (auto [x, t, i]: events) {
        if (t == 0) {
            for (auto it = active.lower_bound(a[i].y1);
                    it != end(active) && it->first <= a[i].y2; it++) {
                adj[i].push_back(it->second);
                adj[it->second].push_back(i);
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
                        int len = x - px, py = y + (above ? len : -len);
                        if (h >= len) {
                            pair<int,int> p = make_pair(px, py), q = make_pair(x, py);
                            int l = -1, m = -1, bl = 0, bm = 0;
                            for (int ll: adj[k]) {
                                if (a[ll].y1 > py) break;
                                if (a[ll].y1 < py) continue;
                                l = ll, bl = a[l].x2 - px;
                            }
                            for (int mm: adj[j]) {
                                if (a[mm].y1 > py) break;
                                if (a[mm].y1 < py) continue;
                                m = mm, bm = x - a[m].x1;
                            }
                            if (longest_without({i, j, k, l, m}) >= len-bl-bm) return true;
                            if (longest_without({i, j, k, l}) >= len-bl) return true;
                            if (longest_without({i, j, k, m}) >= len-bm) return true;
                        }
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
