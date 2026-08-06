// @EXPECTED_RESULTS@: CORRECT
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const int MAXT = 25000;
int N, T, a, b, t, Q;
int main() {
	cin >> N;
	T = MAXT;
	vector<int> dp = vector<int>(T+1);
	while(N--){
		cin >> a >> b >> t;
		if(b){
			for(int k = 0; true; ++k){
				vector<int> ndp = vector<int>(T+1);
				int fun = a - b * k * k;
				if(fun < 0)break;
				for(int ct = 0; ct <= T; ct++){
					if(ct >= t)ndp[ct] = max(dp[ct], dp[ct - t] + fun);
					else ndp[ct] = dp[ct];
				}
				dp = ndp;
			}
		} else {
			vector<int> ndp = vector<int>(T+1);
			int fun = a;
			for(int ct = 0; ct <= T; ct++){
				if(ct >= t)ndp[ct] = max(dp[ct], ndp[ct - t] + fun);
				else ndp[ct] = dp[ct];
			}
			dp = ndp;
		}
	}
	cin >> Q;
	while(Q--){
		cin >> T;
		cout << dp[T] << endl;
	}
	return 0;
}
