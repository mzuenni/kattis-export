#include <bits/stdc++.h>
#define f(i, s, k, l) for (int i = s; i < k; i += l)
#define for0(i, k) f(i, 0, k, 1)

#define pl pair<long long, long long>
#define pb push_back

#define vl vector<long long>
#define vi vector<int>
#define sz(x) (ll)(x).size()

using namespace std;
using ll = long long;
using ld = long double;


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
    ll h, w;
    cin >> h >> w;
    vector<string> grid(h);
    ll n = 0;
    for0(i, h) {
        cin >> grid[i];
        for0(j, w) {
            if (grid[i][j] == '#') n++;
        }
    }
    for (ll k = llround(sqrt(n)); k >= 1; k--) {
        if (n % (k * k) != 0) continue;
        vector<string> temp = grid;
        bool poss = true;
        for(ll i = 0; i <= h - k && poss; i++) {
            for(ll j = 0; j <= w - k && poss; j++) {
                if (temp[i][j] == '#') {
                    for(ll a = 0; a < k && poss; a++) {
                        for(ll b = 0; b < k && poss; b++) {
                            if (temp[i + a][j + b] == '#') temp[i + a][j + b] = '.';
                            else poss = false;
                        }
                    }
                }
            }
        }
        for(ll i = 0; i < h && poss; i++) {
            for(ll j = 0; j < w && poss; j++) {
                if (temp[i][j] == '#') poss = false;
            }
        }
        if (poss) {
            cout << k << endl;
            return 0;
        }
    }
}