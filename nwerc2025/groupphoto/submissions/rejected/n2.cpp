#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define sz(x) (int)size(x)
#define all(x) (x).begin(), (x).end()

// @EXPECTED_RESULTS@: TIME_LIMIT_EXCEEDED, RUN_TIME_ERROR

constexpr int inf = 1e9;

void pmax(int& x, int y){
	x = max(x, y);
}

int main(){
	cin.tie(0)->sync_with_stdio(false);
	int n;
	cin >> n;
	vector<int> a(n);
	for(int &e : a) cin >> e, e--;
	vector<vector<int>> dp(n+1, vector<int>(n+1));
	for(int i = 0; i < n; i++){
		for(int j = 0; i+j < n; j++){
			pmax(dp[i+1][j], dp[i][j] + (a[i] == i+j));
			pmax(dp[i][j+1], dp[i][j] + (a[n-1-j] == i+j));
		}
	}
	int ans = 0;
	for(int i = 0; i < n; i++){
		for(int x : dp[i]) ans = max(ans, x);
	}
	cout << n-ans << "\n";
}
