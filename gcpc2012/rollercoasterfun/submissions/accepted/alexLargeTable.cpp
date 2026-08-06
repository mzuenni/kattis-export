// @EXPECTED_RESULTS@: CORRECT

#include <iostream>
#include <vector>

const int MAXN = 100, MAXJ = 32, MAXT = 25001;
using namespace std;
int itemProfit[MAXJ * MAXN], itemSize[MAXJ * MAXN];
bool itemInfinity[MAXJ * MAXN];
int dp[MAXJ * MAXN][MAXT];

int rek(int id, int t, bool update){
	if(t < 0) return -1000000000;
	if(id == -1)return 0;
	if(update){
		if(itemInfinity[id])dp[id][t] = rek(id    , t - itemSize[id], false) + itemProfit[id];
		else 				dp[id][t] = rek(id - 1, t - itemSize[id], false) + itemProfit[id];
		dp[id][t] = max(dp[id][t], rek(id - 1, t, false));
	}
	return dp[id][t];
}
int main(){
	int N, T, J = 0;
	cin >> N;
	T = 25000;
	while(N-- > 0){
		int a, b, t;
		cin >> a >> b >> t;
		if(b > 0){
			for(int k = 0; true; ++k){
				int fun = a - b * k * k;
				if(fun < 0)break;
				itemProfit[J] = fun;
				itemSize[J] = t;
				itemInfinity[J++] = false;
			}
		} else {
			itemProfit[J] = a;
			itemSize[J] = t;
			itemInfinity[J++] = true;
		}
	}
	for(int i = 0; i < J; i++)for(int t = 0; t <= T; t++) dp[i][t] = -1;
	for(int i = 0; i < J; i++)
		for(int t = 0; t <= T; t++)rek(i, t, true);
	int Q;
	cin >> Q;
	while(Q-->0){
		cin >> T;
		cout << rek(J-1,T, false) << endl;
	}
	return 0;
}
