#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int n, d;
	cin >> n >> d;
	vector<int> p(n);
	for (auto& x : p)
		cin >> x;
	for (int mex = 0;; mex++) {
		vector<bool> ok(n + d, true);
		int next = 1e9;
		for (int i = n; i-- > 0; ) {
			if (p[i] == mex)
				next = i;
			ok[i] = next >= i + d;
		}
		
		vector<bool> dp(n + 1);
		dp[n] = true;
		for (int i = n; i-- > 0; ) {
			if (p[i] != mex)
				dp[i] = dp[i + 1];
			dp[i] = dp[i] or (ok[i + d] and dp[min(n, i + 2*d)]);
		}
			
		if (not dp[0])
			continue;
		cout << mex << endl;
		break;
	}
}
