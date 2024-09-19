#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define all(v) (v).begin(), (v).end()

void print(vi A) {
	for (ll i : A) {
		cout << i << " ";
	}
	cout << endl;
	cout << endl;
}

void run() {
	ll n, m;
	cin >> n >> m;
	vi reg(n, 0);
	vvi digits(1);
	vi pos(1, 0);
	vi pos_inv(1, 0);

	for (ll ci = 0; ci < m; ci++) {
		string c;
		ll a, b;
		cin >> c >> a >> b;
		a--; b--;
		if (c[0] == '?') {
			if (pos[reg[a]] > pos[reg[b]]) {
				cout << ">" << endl;
			} else if (pos[reg[a]] < pos[reg[b]]) {
				cout << "<" << endl;
			} else {
				cout << "=" << endl;
			}
		} else {
			ll k = digits.size();
			vii di = {{-pos[reg[b]], reg[b]}};
			for (ll i : digits[reg[a]]) {
				di.eb(-pos[i], i);
			}
			sort(all(di));
			vi d;
			for (ii p : di) {
				d.pb(p.y);
			}

			// Compute position of new number
			ll lower = 0; ll upper = k;
			bool duplicate = false;
			while (upper != lower) {
				ll middle = (lower + upper)/2;
				vi dm = digits[pos_inv[middle]];
				int comp_res = 0;
				for (ll i = 0; i < min(d.size(), dm.size()); i++) {
					if (pos[d[i]] > pos[dm[i]]) {
						comp_res = 1;
						break;
					} else if (pos[d[i]] < pos[dm[i]]) {
						comp_res = -1;
						break;
					}
				}
				if (comp_res == 0) {
					if (d.size() > dm.size()) {
						comp_res = 1;
					} else if (d.size() < dm.size()) {
						comp_res = -1;
					}
				}
				if (comp_res == 1) {
					lower = middle+1;
				} else if (comp_res == -1) {
					upper = middle;
				} else {
					lower = middle;
					upper = middle;
					duplicate = true;
				}
			}

			// Update all data
			if (duplicate) {
				reg[a] = pos_inv[lower];
			} else {
				reg[a] = k;
				digits.pb(d);
				pos.pb(lower);
				pos_inv.pb(0);
				pos_inv[lower] = k;
				for (ll i = 0; i < k; i++) {
					if (pos[i] >= lower) {
						pos[i]++;
						pos_inv[pos[i]] = i;
					}
				}
			}
		}
	}
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    run();
    return 0;
}
