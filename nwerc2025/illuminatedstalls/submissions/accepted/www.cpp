#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define all(x) begin(x), end(x)

const int inf = 2e9;
struct seg {
    int x1, y1, x2, y2;
    int length() const {
        return abs(x1-x2)+abs(y1-y2);
    }
    bool hor() const {
        return x1 != x2;
    }
    bool ver() const {
        return y1 != y2;
    }
    int idx() const {
        return x1 == x2 ? x1 : y1;
    }
};

int dis(const seg& a, const seg& b) {
    assert(a.hor() == b.hor());
    if (a.hor()) return abs(a.y1 - b.y1);
    return abs(a.x1 - b.x1);
}

bool intersect(seg a, seg b) {
    assert(a.hor() != b.hor());
    if (a.ver()) swap(a,b);
    if (b.x1 < a.x1 || b.x1 > a.x2) return 0;
    if (a.y1 < b.y1 || a.y1 > b.y2) return 0;
    return 1;
}
void yes() {
    cout << "yes\n";
}

void solve() {
    int n; cin >> n;
    vector<seg> sex(n);
    for (int i = 0; i < n; i++) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        if (pii{a,b} > pii{c,d}) swap(a,c), swap(b,d);
        sex[i] = {a,b,c,d};
    }
    sort(all(sex), [&](const seg& x, const seg& y){return x.length() < y.length();});

    {
        vi order = {1, 2, 3}; 
        do {
            vector<seg> l3 = {sex[n-order[0]], sex[n-order[1]], sex[n-order[2]]};
            if (l3[1].hor() != l3[2].hor()) continue;
            if (l3[1].idx() > l3[2].idx()) continue;

            if (l3[0].hor() == l3[1].hor()) continue;
            if (!(intersect(l3[0], l3[1]) && intersect(l3[0], l3[2]))) continue;


            int l = dis(l3[1], l3[2]);

            for (int j = max(0, n-6); j < n-3; j++) {
                int ll = sex[j].length();
                if (l3[0].hor()) {
                    if (l3[1].y2-l3[0].y1 >= l && l3[2].y2-l3[0].y1 >= l) {
                        int a = l3[1].x1, b = l3[2].x1;
                        for (int i = 0; i < n-3; i++) if (sex[i].hor() && sex[i].y1 == l3[0].y1+l && i != j) {
                            if (sex[i].x1 <= a) a = max(sex[i].x2, a);
                            if (sex[i].x2 >= b) b = min(sex[i].x1, b);
                        }
                        if (b - a <= ll) return yes();
                    }
                    if (l3[0].y1-l3[1].y1 >= l && l3[0].y1-l3[2].y1 >= l) {
                        int a = l3[1].x1, b = l3[2].x1;
                        for (int i = 0; i < n-3; i++) if (sex[i].hor() && sex[i].y1 == l3[0].y1-l && i != j) {
                            if (sex[i].x1 <= a) a = max(sex[i].x2, a);
                            if (sex[i].x2 >= b) b = min(sex[i].x1, b);
                        }
                        if (b - a <= ll) return yes();
                    }
                } else {
                    if (l3[1].x2-l3[0].x1 >= l && l3[2].x2-l3[0].x1 >= l) {
                        int a = l3[1].y1, b = l3[2].y1;
                        for (int i = 0; i < n-3; i++) if (sex[i].ver() && sex[i].x1 == l3[0].x1+l && i != j) {
                            if (sex[i].y1 <= a) a = max(sex[i].y2, a);
                            if (sex[i].y2 >= b) b = min(sex[i].y1, b);
                        }
                        if (b - a <= ll) return yes();
                    }
                    if (l3[0].x1-l3[1].x1 >= l && l3[0].x1-l3[2].x1 >= l) {
                        int a = l3[1].y1, b = l3[2].y1;
                        for (int i = 0; i < n-3; i++) if (sex[i].ver() && sex[i].x1 == l3[0].x1-l && i != j) {
                            if (sex[i].y1 <= a) a = max(sex[i].y2, a);
                            if (sex[i].y2 >= b) b = min(sex[i].y1, b);
                        }
                        if (b - a <= ll) return yes();
                    }
                }
            }
        } while (next_permutation(all(order)));
    }

    vi ver, hor;
    for (int i = 0; i < n; i++) {if (sex[i].hor()) hor.push_back(i); else ver.push_back(i);}
    map<int, vi> events;
    for (int i : hor) events[sex[i].x1].push_back(i+1);
    for (int i : hor) events[sex[i].x2+1].push_back(-i-1);
    sort(all(ver), [&](const auto& a, const auto& b){return sex[a].x1 < sex[b].x1;});
    vector<vi> intersections(n);
    map<int, int> active_heights;
    auto it = events.begin();
    int tot_intersections = 0;
    for (int i : ver) {
        while (it != events.end() && it->first <= sex[i].x1) {
            sort(all(it->second));
            for (int e : it->second) {
                if (e > 0) active_heights[sex[e-1].y1] = e-1;
                else active_heights.erase(sex[-e-1].y1);
            }
            it++;
        }
        auto it2 = active_heights.lower_bound(sex[i].y1);
        for (;it2 != active_heights.end() && it2->first <= sex[i].y2; it2++) {
            intersections[i].push_back(it2->second);
            intersections[it2->second].push_back(i);
            if (++tot_intersections > 2*n) return yes();
        }
    }

    for (int i = 0; i < n; i++) {
        for (int t = 0; t <= 1; t++) {
            stack<pii> stk;
            int ctr = 0;
            for (int j : intersections[i]) {
                int h;
                if (sex[i].hor()) h = (t == 0 ? sex[j].y2-sex[i].y1 : sex[i].y1-sex[j].y1);
                if (sex[i].ver()) h = (t == 0 ? sex[j].x2-sex[i].x1 : sex[i].x1-sex[j].x1);

                while (!stk.empty()) {
                    if (sex[j].idx() - sex[stk.top().second].idx() <= min(stk.top().first, h)) {
                        if (j < n-3 || stk.top().second < n-3 || i < n-3) return yes();
                    }
                    if (stk.top().first > h) break;
                    stk.pop();
                }
                stk.push({h, j});
            }
        }
    }

    cout << "no\n";
}

int main() {
    int t; cin >> t;
    while(t--) solve();
}