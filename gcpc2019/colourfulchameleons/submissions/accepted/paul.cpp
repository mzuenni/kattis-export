#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, c, y, a;
	cin >> n >> c >> y;

	vector<int> b;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		if (i+1 == c) a = x;
		else b.push_back(x);
	}
	
	for (int i = 1; i < n-1; i++) {
		if ((b[i]-b[0]) % (y+1) != 0) {
			cout << "impossible" << endl;
			return 0;
		}
	}
	
	int bmax = *max_element(begin(b),end(b));
	long long count = a + accumulate(begin(b),end(b),0LL) + bmax*1LL*(y+1-n);
	cout << bmax << " " << count << endl;
}
