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
	vector<int> byMax(n);
	iota(all(byMax), 0);
	vector<int> byMin = byMax;
	sort(all(byMax), [&](int i, int j){
		return max(a[i]+1, b[i]) < max(a[j]+1, b[j]);
	});
	sort(all(byMin), [&](int i, int j){
		return min(a[i]-1, b[i]) > min(a[j]-1, b[j]);
	});
	vector<ll> inv(n, 1);
	for(int i = 2; i < n; i++){
		inv[i] = mod - mod / i * inv[mod % i] % mod;
	}
	vector<ll> xl(n), xr(n);
	vector<int> indl(n), indr(n), cnt(n);
	vector<vector<ll>> dp(n, vector<ll>(n));
	for(int d = 2; d < n; d++){
		for(int i = 0; i < n-d; i++){
			int j = i + d;
			{
				int &k = indl[i];
				while(k < n && max(a[byMax[k]]+1, b[byMax[k]]) <= a[j]){
					if(min(a[byMax[k]]-1, b[byMax[k]]) >= a[i]){
						xl[i] += dp[i][byMax[k]];
						cnt[i]++;
					}
					k++;
				}
			}
			{
				int &k = indr[j];
				while(k < n && min(a[byMin[k]]-1, b[byMin[k]]) >= a[i]){
					if(max(a[byMin[k]]+1, b[byMin[k]]) <= a[j]){
						xr[j] += dp[byMin[k]][j];
					}
					k++;
				}
			}
			dp[i][j] = (xl[i] + xr[j] + cnt[i]) % mod * inv[cnt[i]] % mod;
		}
	}
	cout << dp[0][n-1] << "\n";
}