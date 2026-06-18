#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) (x).begin(), (x).end()

constexpr int inf = 1e9 + 5;
constexpr ll mod = 998244353;

int main(){
	int n;
	cin >> n;
	vector<pair<int, int>> v(n);
	for(auto &[a, b] : v) cin >> a >> b;
	v.emplace_back(-1, -1);
	v.emplace_back(inf, inf);
	n += 2;
	sort(all(v));
	vector<int> a(n), b(n);
	for(int i = 0; i < n; i++) tie(a[i], b[i]) = v[i];
	vector<ll> inv(n, 1);
	for(int i = 2; i < n; i++){
		inv[i] = mod - mod / i * inv[mod % i] % mod;
	}
	vector<vector<ll>> dp(n, vector<ll>(n));
	for(int d = 2; d < n; d++){
		for(int i = 0; i < n-d; i++){
			int j = i + d;
			int cnt = 0;
			for(int k = i+1; k < j; k++){
				if(a[i] <= b[k] && b[k] <= a[j]){
					dp[i][j] += dp[i][k] + dp[k][j] + 1;
					cnt++;
				}
			}
			dp[i][j] = dp[i][j] % mod * inv[cnt] % mod;
		}
	}
	cout << dp[0][n-1] << "\n";
}