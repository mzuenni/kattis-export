#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

int main(){
	cin.tie(0)->sync_with_stdio(false);
	int n, d;
	cin >> n >> d;
	vector<int> p(n);
	for(int i = 0; i < n; i++) cin >> p[i];
	for(int s = 0; s < n; s += 64){
		vector<int> cnt(n);
		vector<ull> dp(n, -1);
		ull ok = -1;
		for(int i = n-2; i >= 0; i--){
			if(i+d < n && s <= p[i+d] && p[i+d] < s+64) if(!cnt[p[i+d]]++) ok &= ~(1ull<<(p[i+d]-s));
			if(i+2*d < n && s <= p[i+2*d] && p[i+2*d] < s+64) if(!--cnt[p[i+2*d]]) ok |= 1ull << (p[i+2*d]-s);
			dp[i] = dp[i+1];
			if(s <= p[i] && p[i] < s+64) dp[i] &= ~(1ull<<(p[i]-s));
			dp[i] |= dp[min(n-1, i + 2*d)] & ok;
		}
		if(dp[0]){
			cout << s + __builtin_ctzll(dp[0]) << "\n";
			return 0;
		}
	}
}