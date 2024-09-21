#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll lim = 10000*100;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> buy(lim), sell(lim);
	int buyers = 0;
	for (int i = 0; i < n; i++) {
		ld p;
		int b, s;
		cin >> p >> b >> s;
		int j = round(p*100);
		buy[j] += b;
		sell[j] += s;
		buyers += b;
	}
	int res = 0;
	int prize = -1;
	int sellers = 0;
	for (int i = 0; i < lim; i++) {
		sellers += sell[i];
		int curRes = i*min(sellers, buyers);
		if (curRes > res) {
			res = curRes;
			prize = i;
		}
		buyers -= buy[i];
	}
	if (prize < 0) {
		cout << "impossible" << endl;
	} else {
		cout << fixed << setprecision(2) << prize/100.0l << " " << res/100.0l << endl;
	}
}
