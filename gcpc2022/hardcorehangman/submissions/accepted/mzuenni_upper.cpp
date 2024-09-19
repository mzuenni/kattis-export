#include <bits/stdc++.h>
#include <fstream>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

vector<ll> query(const string& s) {
	cout << "? " << s << endl;
	ll n;
	cin >> n;
	vector<ll> res(n);
	for (ll i = 0; i < n; i++) {
		ll x;
		cin >> x;
		res[i] = x - 1;
	}
	return res;
}

int main() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
	string tmp;
	for (char c = 'A'; c <= 'Z'; c++) tmp += c;
	vector<ll> res(sz(query(tmp)));
	for (ll i = 0; i < 5; i++) {
		tmp = "";
		for (ll c = 0; c < 26; c++) {
			if (((c >> i) & 1) != 0) {
				tmp += (char)('A' + c);
			}
		}
		auto ans = query(tmp);
		for (ll x : ans) {
			res[x] |= 1 << i;
		}
	}
	cout << "! ";
	for (ll x : res) {
		cout << (char)(x + 'A');
	}
	cout << endl;
} 
