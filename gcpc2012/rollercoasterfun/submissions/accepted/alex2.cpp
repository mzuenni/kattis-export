// @EXPECTED_RESULTS@: CORRECT
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
		if(b){
			// if fun is decreasing -> update while fun is positive
			for(int k = 0, fun = a; fun > 0; ++k){
				for(int ct = T; ct >= t; ct--)
					dp[ct] = max(dp[ct], dp[ct-t] + fun);
				fun -= (1 + 2*k) * b;
			}
		} else {
			for(int ct = t; ct <= T; ct++)
				dp[ct] = max(dp[ct], dp[ct-t] + a);
		}
	}
	cin >> Q;
	while(Q--){
		cin >> T;
		cout << dp[T] << endl;
	}
	return 0;
}
