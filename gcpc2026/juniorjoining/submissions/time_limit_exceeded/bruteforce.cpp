#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) (x).begin(), (x).end()
#define sz(x) int(size(x))

int main(){
	int n;
	cin >> n;
	vector<ll> l(2*n), r(2*n), c(2*n);
	for(int i = 0; i < 2*n; i++){
		cin >> l[i] >> r[i] >> c[i];
	}
	vector<int> ord(2*n);
	iota(all(ord), 0);
	ll ans = 0;
	do{
		ll val = 0;
		for(int i = 0; i < n; i++){
			int x = ord[2*i], y = ord[2*i+1];
			val += l[x] + r[y];
			if(c[x] == c[y]) val += c[x];
		}
		ans = max(ans, val);
	}while(next_permutation(all(ord)));
	cout << ans << "\n";
}