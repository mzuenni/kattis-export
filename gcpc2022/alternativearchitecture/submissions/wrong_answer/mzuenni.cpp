#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

ll res = 0;

ll gcd(ll a, ll b) {return b == 0 ? a : gcd(b, a % b);}

void check(ll i, ll j, ll b) {
	//ll d = gcd(i, j);
	//i /= d;
	//j /= d;
	ll x = b*b/(i*i+j*j);
	if (x*(i*i+j*j) == b*b) {
		res += (i == j || i == 0 || j == 0) ? 1 : 2;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll a, b;
	cin >> a >> b;
	if (b < a) swap(a, b);
	for (ll i = 0; 2*i*i <= a*a; i++) {
		//i^2+j^2=a^2
		ll j = sqrt(a*a-i*i);
		if (i*i + j*j == a*a) {
			check(i, j, b);
			if (i != j) check(j, i, b);
		}
	}
	if (a == b) res /= 2;
	cout << res << endl;
}
