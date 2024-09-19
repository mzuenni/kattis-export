#include <bits/stdc++.h>
using namespace std;

int main() {
	int doors, select, open;
	cin >> doors >> select >> open;

	int rem = doors - select - open;

	double sel_prob = 1.0/doors;
	double rem_prob = double(doors-select)/doors/rem;
	
	double res = 0;
	while (select--) {
		if (rem-- > 0) res += rem_prob;
		else res += sel_prob;
	}
	cout << fixed << setprecision(20) << res << endl;
}
