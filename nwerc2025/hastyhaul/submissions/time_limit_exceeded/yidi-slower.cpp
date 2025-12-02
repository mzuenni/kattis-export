#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

int main() {
    cin.tie(0)->sync_with_stdio(0);

    constexpr int N = 100;
    array<array<ll, N>, N> C = {};
    C[0][0] = 1;
    for (int i=0; i<N-1; i++) {
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
            cout << "risky\n";
            continue;
        }

        auto calc = [&](auto& self, string s) -> ll {
            int n = ssize(s);
            int k = count(all(s), '#');
            if (k == 0) return 0LL;

            int i = s.find('#');
            s.erase(s.begin(), s.begin() + i + 1);

            ll ans = 0;
            for (int j=0; j<i; j++) ans += C[n-1-j][k-1];

            if (i % 2 == 1) reverse(all(s));
            return ans + self(self, s);
        };

        ll x = calc(calc, a) ^ 1;
        int y = -1, z = -1;
        for (int i=0; i<n*m; i++) if (a[i] == '#') {
            for (int j=0; j<n*m; j++) if (a[j] == '.') {
                swap(a[i], a[j]);
                if (calc(calc, a) == x) y = i, z = j;
                swap(a[i], a[j]);
            }
        }
        cout << y/m + 1 << ' ' << y%m + 1 << '\n';
        cout << z/m + 1 << ' ' << z%m + 1 << '\n';
    }
}
