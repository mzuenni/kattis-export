#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) (x).begin(), (x).end()
#define sz(x) int(size(x))

constexpr int C = 1e6 + 1;

int byC[C];

int main(){
	int n;
	cin >> n;
	vector<ll> l(2*n), r(2*n), c(2*n);
	for(int i = 0; i < 2*n; i++){
		cin >> l[i] >> r[i] >> c[i];
	}
	vector<int> ord(2*n);
	iota(all(ord), 0);
	sort(all(ord), [&](int i, int j){return l[i]-r[i] > l[j]-r[j];});
	ll ans = 0;
	for(int i = 0; i < n; i++){
		int j = ord[i];
		ans += l[j];
		byC[c[j]]++;
	}
	for(int i = n; i < 2*n; i++){
		int j = ord[i];
		ans += r[j];
		if(byC[c[j]]) ans += c[j], byC[c[j]]--;
	}
	cout << ans << "\n";
}