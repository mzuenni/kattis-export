#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

int main() {
    cin.tie(0)->sync_with_stdio(0);

    constexpr int N = 66;
    array<array<ll, N+1>, N+1> C = {};
    C[0][0] = 1;
    for (int i=0; i<N; i++) {
        for (int j=0; j<=i; j++) {
            C[i+1][j] += C[i][j];
            C[i+1][j+1] += C[i][j];
        }
    }

    int T;
    cin >> T;
    while (T--) {
        int n, m, k;
        cin >> n >> m >> k;
        string a;
        for (int i=0; i<n; i++) {
            string s;
            cin >> s;
            a += s;
        }

        if (C[n*m][count(all(a), '#')] % 2 == 1) {
            cout << "risky" << endl;
            continue;
        }

        auto _calc = [&](auto& self, string& s, int k, int l, int r, bool rev) -> ll {
            if (k == 0) return 0LL;

            ll ans = 0;
            if (!rev) while (s[l++] != '#') ans += C[r-l][k-1], rev = !rev;
            else while (s[--r] != '#') ans += C[r-l][k-1], rev = !rev;

            return ans + self(self, s, k-1, l, r, rev);
        };

        auto calc = [&](string s) {
            return _calc(_calc, s, count(all(s), '#'), 0, ssize(s), false);
        };

        ll x = calc(a) ^ 1;
        int y = -1, z = -1;
        vector<int> xs, other = {-1};
        for (int i=0, last=0, nxt=0; i<n*m; i++) {
            while (nxt < n*m-1 && (nxt < i || a[nxt] == '#')) nxt++;

            if (a[i] == '#') {
                for (auto j : {last, nxt}) {
                    swap(a[i], a[j]);
                    if (calc(a) == x) y = i, z = j;
                    swap(a[i], a[j]);
                }
            } else last = i;
        }
        cout << y/m + 1 << ' ' << y%m + 1 << '\n';
        cout << z/m + 1 << ' ' << z%m + 1 << '\n';
    }
}
