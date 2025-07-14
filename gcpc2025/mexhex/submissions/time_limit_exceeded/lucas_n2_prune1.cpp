#include <bits/stdc++.h>
using namespace std;

int main(){
	cin.tie(0)->sync_with_stdio(false);
	int n, d;
	cin >> n >> d;
	vector<vector<int>> a(n);
	for(int i = 0; i < n; i++){
		int p;
		cin >> p;
		a[p].push_back(i);
	}
	vector<bool> dp(n), has(n);
	for(int t = 0; t < n; t++){
		if(a[t].empty()){
			cout << t << "\n";
			break;
		}
		{
			bool impossible = false;
			int prv = -2*d;
			for(int x : a[t]){
				if(x - prv == d) impossible = true;
				prv = x;
			}
			if(impossible) continue;
		}
		fill(has.begin(), has.end(), false);
		for(int x : a[t]) has[x] = true;
		dp[n-1] = true;
		int cnt = 0;
		bool ok = true;
		for(int i = n-1; i >= 0; i--){
			if(i + d < n && has[i+d]) if(!cnt++) ok = false;
			if(i + 2*d < n && has[i+2*d]) if(!--cnt) ok = true;
			dp[i] = (!has[i] && dp[i+1]) || (ok && dp[min(n-1, i+2*d)]);
		}
		if(dp[0]){
			cout << t << "\n";
			break;
		}
	}
}