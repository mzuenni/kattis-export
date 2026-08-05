/*
This is an implementation of the algorithm in:
Böcker/Lipták: A Fast and Simple Algorithm for the Money Changing Problem
http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.390.1418
Complexity: O(k*a[0]) (using the notation from the paper)
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll oo = 0x3f3f3f3f3f3f3f3f;

ll gcd(ll a, ll b) { return (b == 0) ? a : gcd(b, a%b); }

int main() {
	ll k, N; cin >> k >> N;
	vector<ll> a(k);
	for (ll i = 0; i < k; i++) cin >> a[i];

	vector<ll> n(a[0],oo);
	n[0] = 0;
	for (ll i = 1; i < k; i++) {
		ll d = gcd(a[0],a[i]);
		for (ll p = 0; p < d; p++) {
			ll nmin = oo;
			for (ll q = p; q < a[0]; q += d) nmin = min(nmin, n[q]);
			if (nmin == oo) continue;
			for (ll j = 1; j < a[0]/d; j++) {
				nmin += a[i];
				ll r = nmin % a[0];
				nmin = n[r] = min(nmin, n[r]);
			}
		}
	}
	
	if (n[N % a[0]] <= N) cout << "possible" << endl;
	else cout << "impossible" << endl;

}
