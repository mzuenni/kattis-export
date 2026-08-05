#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vl;
#define sz(c) ll((c).size())
#define FOR(i,a,b) for (ll i = (a); i < (b); i++)

int main() {
	ll a, b, c, d; cin >> a >> b >> c >> d;
	vector<bool> res;
	while (a != 1 || b != 0 || c != 0 || d != 1) {
		if (b < a) a = a-b, c = c-d, res.push_back(0);
		else b = b-a, d = d-c, res.push_back(1);
	}
	reverse(begin(res),end(res));
	char x = 0;
	FOR(i,0,sz(res)) {
		cout << res[i];
	}
	cout << endl;
}


