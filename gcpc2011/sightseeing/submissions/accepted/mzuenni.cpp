#include <bits/stdc++.h>
using namespace std;

#define fora(i, n) for (int i = 0; i < n; ++i)
#define forb(i, n) for (int i = 1; i<= n; ++i)
#define forc(i, n) for (const auto &i : n)
#define mp make_pair
#define eb emplace_back
#define pb push_back
#define sz(x) (int)(x).size()

using ll = long long;
using ld = long double;
using vi = vector<int>;

ll out[2][2][100007], in[2][2][100007];
int pred[2][2][100007];
constexpr ll inf = 1000000000000000000;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int C;
	cin >> C;
	fora(_, C) {
		int N;
		ll T;
		cin >> N >> T;
		fora(i, 100007) fora(j, 2) fora(k, 2) {
			out[j][k][i] = inf; in[j][k][i] = inf;
		}
		
		out[0][0][0] = 0;
		out[1][1][0] = 0;
		
		ll ps = 0;
		forb(b, N) {
			ll p;
			ll d[2][2];
			cin >> p >> d[0][1] >> d[0][0] >> d[1][1] >> d[1][0];
			ps += p;
			fora(k, 2) fora(s, 2) fora(t, 2) {
				if (out[k][s][b - 1] + d[s][t] < out[k][t][b]) {
					out[k][t][b] = out[k][s][b - 1] + d[s][t];
					pred[k][t][b] = s;
				}
			}
		}
		
		ll c = 0;
		if (out[1][1][N] < out[0][0][N])
			c = 1;
		
		if (out[c][c][N] + ps > T) {
			cout << "IMPOSSIBLE\n";
			continue;
		}
		
		string result(N, 'A');
		ll cur = c;	
		for (int i = N; i > 0; --i) {
			result[i % N] = (cur == 0) ? 'B' : 'F';
			cur = pred[c][cur][i];
		}
		cout << result << '\n';
		
		//cout << out[c][c][N] << endl;
		
	}
}
