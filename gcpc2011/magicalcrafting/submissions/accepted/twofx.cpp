#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define eb emplace_back
#define all(a) begin(a), end(a)
#define has(a, b) (a.find(b) != a.end())
#define fora(i, n) for(int i = 0; i < n; i++)
#define forb(i, n) for(int i = 1; i <= n; i++)
#define forc(a, b) for(const auto &a : b)
#define ford(i, n) for(int i = n; i >= 0; i--)
#define maxval(t) numeric_limits<t>::max()
#define minval(t) numeric_limits<t>::min()
#define imin(a, b) a = min(a, b)
#define imax(a, b) a = max(a, b)
#define sz(x) (int)(x).size()

#define dbgs(x) #x << " = " << x
#define dbgs2(x, y) dbgs(x) << ", " << dbgs(y)
#define dbgs3(x, y, z) dbgs2(x, y) << ", " << dbgs(z)
#define dbgs4(w, x, y, z) dbgs3(w, x, y) << ", " << dbgs(z)

using ll = long long;

ll cyk[100][100][26];
constexpr ll inf = 1000000000000;

struct recipe {
	int a, b, c;
	ll cost;
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int C;
	cin >> C;
	fora(_, C) {
		int r, l;
		cin >> r >> l;
		cout << "CASE #" << (_ + 1) << '\n';
		vector<recipe> re(r);
		fora(i, r) {
			char a, b, c;
			ll co;
			cin >> a >> b >> c >> co;
			re[i] = recipe { a - 'A',  b - 'A', c - 'A', co };
		}
		fora(i, l) {
			int q;
			string s;
			cin >> q >> s;
			fora(i, 100) fora(j, 100) fora(k, 26) cyk[i][j][k] = inf;
			fora(i, q)
				cyk[q - 1][i][s[i] - 'a'] = 1;
			for (int i = q - 2; i >= 0; --i) {
				fora(j, i + 1) {
					forb(k, q - 1 - i) {
						int i1 = i + k, j1 = j, i2 = i + (q - i - k), j2 = j + (q - i - k);
						//cout << dbgs3(i, j, k) << ", " << dbgs4(i1, j1, i2, j2) << endl;

						forc(t, re) {
							if (cyk[i1][j1][t.b] == inf || cyk[i2][j2][t.c] == inf)
								continue;
							imin(cyk[i][j][t.a], cyk[i1][j1][t.b] + cyk[i2][j2][t.c] + t.cost);
							//cout << dbgs4(i, j, t.a, cyk[i][j][t.a] ) << endl;
						}
					}
				}
			}
			if (cyk[0][0][0] == inf)
				cout << "IMPOSSIBLE\n";
			else
				cout << "POSSIBLE WITH " << cyk[0][0][0] << " DIAMONDS\n";
		}
	}

}
