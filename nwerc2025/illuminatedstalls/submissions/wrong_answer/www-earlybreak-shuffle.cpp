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

const int mxn = 2e5;
int HY[mxn], HX1[mxn], HX2[mxn];
int VX[mxn], VY1[mxn], VY2[mxn];
bitset<mxn> Hbig3, Vbig3;
pii stkT[mxn], stkB[mxn];
auto t0 = chrono::high_resolution_clock::now();
mt19937 rng(t0.time_since_epoch().count());
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
    
    int h = 0, v = 0;
    {
        vector<array<int, 4>> hor_v, ver_v;
        for (int i = 0; i < n; i++) {
            if (sex[i].hor()) {
                hor_v.push_back({sex[i].y1, sex[i].x1, sex[i].x2, i});
            } else {
                ver_v.push_back({sex[i].x1, sex[i].y1, sex[i].y2, i});
            }
        }
        sort(all(hor_v)); h = hor_v.size();
        sort(all(ver_v)); v = ver_v.size();
        for (int i = 0; i < h; i++) {
            HY[i]  = hor_v[i][0];
            HX1[i] = hor_v[i][1];
            HX2[i] = hor_v[i][2];
            Hbig3[i] = (hor_v[i][3] >= n-3);
        }
        for (int i = 0; i < v; i++) {
            VX[i]  = ver_v[i][0];
            VY1[i] = ver_v[i][1];
            VY2[i] = ver_v[i][2];
            Vbig3[i] = (ver_v[i][3] >= n-3);
        }
    }
    vi ord(h);
    iota(all(ord),0);
    shuffle(all(ord),rng);

    for (int i : ord) {
        int s = lower_bound(begin(VX), begin(VX)+v, HX1[i])-begin(VX);
        int ptrT = 0, ptrB = 0;
        if((chrono::high_resolution_clock::now()-t0).count()*1e-9>4) break;
        for (int j = s; j < v && VX[j] <= HX2[i]; j++) {
            int hT = VY2[j]-HY[i];
            int hB = HY[i]-VY1[j];
            if (hT < 0 || hB < 0) continue;
            if (hT > 0) {
                while (ptrT != 0) {
                    if (min(abs(stkT[ptrT-1].first), hT) >= VX[j]-stkT[ptrT-1].second) {
                        if (stkT[ptrT-1].first > 0 || !Hbig3[i] || !Vbig3[j]) return yes();
                    }
                    if (abs(stkT[ptrT-1].first) > hT) break;
                    ptrT--;
                }
                stkT[ptrT++] = {(Vbig3[j] ? -hT : hT), VX[j]};
            }
            if (hB > 0) {
                while (ptrB != 0) {
                    if (min(abs(stkB[ptrB-1].first), hB) >= VX[j]-stkB[ptrB-1].second) {
                        if (stkB[ptrB-1].first > 0 || !Hbig3[i] || !Vbig3[j]) return yes();
                    }
                    if (abs(stkB[ptrB-1].first) > hB) break;
                    ptrB--;
                }
                stkB[ptrB++] = {(Vbig3[j] ? -hB : hB), VX[j]};
            }
        }
    }
    ord.resize(v);
    iota(all(ord),0);
    shuffle(all(ord),rng);

    for (int i : ord) {
        int s = lower_bound(begin(HY), begin(HY)+h, VY1[i])-begin(HY);
        int ptrT = 0, ptrB = 0;
        if((chrono::high_resolution_clock::now()-t0).count()*1e-9>7.9) break;
        for (int j = s; j < h && HY[j] <= VY2[i]; j++) {
            int hT = HX2[j]-VX[i];
            int hB = VX[i]-HX1[j];
            if (hT < 0 || hB < 0) continue;
            if (hT > 0) {
                while (ptrT != 0) {
                    if (min(abs(stkT[ptrT-1].first), hT) >= HY[j]-stkT[ptrT-1].second) {
                        if (stkT[ptrT-1].first > 0 || !Vbig3[i] || !Hbig3[j]) return yes();
                    }
                    if (abs(stkT[ptrT-1].first) > hT) break;
                    ptrT--;
                }
                stkT[ptrT++] = {(Hbig3[j] ? -hT : hT), HY[j]};
            }
            if (hB > 0) {
                while (ptrB != 0) {
                    if (min(abs(stkB[ptrB-1].first), hB) >= HY[j]-stkB[ptrB-1].second) {
                        if (stkB[ptrB-1].first > 0 || !Vbig3[i] || !Hbig3[j]) return yes();
                    }
                    if (abs(stkB[ptrB-1].first) > hB) break;
                    ptrB--;
                }
                stkB[ptrB++] = {(Hbig3[j] ? -hB : hB), HY[j]};
            }
        }
    }
    
    cout << "no\n";
}

int main() {
    int t; cin >> t;
    while(t--) solve();
}