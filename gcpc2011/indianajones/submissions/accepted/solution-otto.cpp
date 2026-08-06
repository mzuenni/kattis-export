
//region template
//https://github.com/schmidtjonas/CPT/blob/master/template.cpp
#include <bits/stdc++.h>

#define GET_MACRO(_1,_2,_3,NAME,...) NAME
#define rep(...)        GET_MACRO(__VA_ARGS__, repn, rep0)(__VA_ARGS__)
#define rep0(i, b)      for(int i = 0; i < (b); ++i)
#define repn(i, a, b)   for(int i = (a); i < (b); ++i)
#define trav(a, b)      for(auto& a : b)
#define all(a)          (a).begin(),(a).end()
#define endl            '\n'
#define sz(x)           ((int)(x).size())
#define tests           int ___;cin>>___;while(___--)

using namespace std;
using ll = int64_t;
using ld = long double;
using ul = uint64_t;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using vpi = vector<pi>;

static constexpr int inf = (int)1e9 + 5;
static constexpr ll infl = (ll)1e18 + 5;
static mt19937 rng((uint32_t)chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
//endregion

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    tests {
        ll n, h; cin >> n >> h;
        vector<ll> ind(n, 0);
        vector<vector<ll>> s(n);
        rep(i, h) {
            ll a, b; cin >> a >> b;
            a--; b--;
            ind[b]++;
            s[a].push_back(b);
        }
        queue<ll> q;
        rep(i, n) {
            if (ind[i] == 0) q.push(i);
        }
        vector<ll> p;
        bool unique = true;
    find_next:
        if (p.size() != n) {
            if (q.size() == 0) {
                cout << "recheck hints"  << endl;
                continue;
            } else {
                if (q.size() > 1) {
                    unique = false;
                }
                ll v = q.front(); q.pop();
                p.push_back(v);
                trav(ne, s[v]) {
                    if (!--ind[ne]) {
                        q.push(ne);
                    }
                }
                goto find_next;
            }
        } else {
            if (unique) {
                trav(v, p) {
                    cout << (v == p[0] ? "" : " ") << v+1;
                }
                cout << endl;
            } else {
                cout << "missing hints" << endl;
            }
        }
    }

    return 0;
}

