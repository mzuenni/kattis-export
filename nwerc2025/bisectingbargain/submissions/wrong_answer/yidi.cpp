#include <bits/stdc++.h>
using namespace std;

#define tsolve int t; cin >> t; while(t--) solve
#define debug(x) cerr << __LINE__ << ": "#x" = " << (x) << endl
#define nl '\n'
#define all(x) ::begin(x), ::end(x)
#define sz(x) (int)::size(x)
using ll = long long;
using ld = long double;

vector<int> coins = {1, 2, 5, 10, 20, 50, 100, 200, 500};

void solve() {
	int n;
	cin >> n;
	int k = n;
	vector<int> res;
	while (k >= 1000) {
		for (int it=0; it<5; it++) res.push_back(200);
		k -= 1000;
	}
	for(int i = sz(coins)-1; i >= 0; i--){
		while(k >= coins[i]){
			res.push_back(coins[i]);
			k -= coins[i];
		}
	}
	vector<int> dp(n+1);
	dp[0] = 1;
	for(int x : res){
		for(int i = n; i >= x; i--){
			dp[i] |= dp[i-x];
		}
	}
	if(n % 2 == 0 && dp[n / 2] == 1){
		cout << "splittable\n";
	}
	else{
		// cout << "unsplittable\n";
		cout << sz(res) << "\n";
		for(int x : res) cout << x << " ";
		cout << "\n";
	}
}
 
int main() {
	cin.tie(0)->sync_with_stdio(false);
	cout << setprecision(16);
	solve();
}