// @EXPECTED_RESULTS@: TIMELIMIT
#include <iostream>
#include <cmath>

using namespace std;

const int MAXT = 25000;
int dp[MAXT +  100], N, T, a, b, t, Q;
int main() {
	for(int i = 0; i <= MAXT; i++)dp[i] = 0;
	cin >> N;
	T = MAXT;
	while(N--){
		cin >> a >> b >> t;
		bool change = 1;
		for(int k = 0, fun = a; fun > 0 && change; ++k){
			change = 0;
			for(int ct = T; ct >= t; ct--)if(dp[ct] < dp[ct-t] + fun){
				dp[ct] = dp[ct-t] + fun;
				change = 1;
			}
			fun -= (1 + 2*k) * b;
		}
	}
	cin >> Q;
	while(Q--){
		cin >> T;
		cout << dp[T] << endl;
	}
	return 0;
}
