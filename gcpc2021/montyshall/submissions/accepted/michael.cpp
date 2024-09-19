#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ld d, s, e;
	cin >> d >> s >> e;

	ld change = min(s, d-s-e);
	ld keep = s-change;

	ld p = keep/d;
	ld pp = 1-s/d;
	ld changed = change/(d-s-e);

	cout << fixed << setprecision(10) << p+pp*changed << endl;
}
