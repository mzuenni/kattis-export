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
		if (n[a[i] % a[0]] <= a[i]) continue;
		ll d = gcd(a[0],a[i]);
		ll p = 0, q = a[i] % a[0];
		for (ll t = 1; t < a[0]/d; t++) {
			for (ll r = 0; r < d; r++) {
				n[q+r] = min(n[q+r], n[p+r] + a[i]);
			}
			p = q, q = (q + a[i]) % a[0];
		}
		bool go = true;
		while (go) {
			go = false;
			for (ll r = 0; r < d; r++) {
				if (n[p+r] + a[i] < n[q+r]) {
					n[q+r] = n[p+r] + a[i];
					go = true;
				}
			}
			p = q; q = (q + a[i]) % a[0];
		}
		if (n[N % a[0]] <= N) break;
	}
	
	if (n[N % a[0]] <= N) cout << "possible" << endl;
	else cout << "impossible" << endl;

}
