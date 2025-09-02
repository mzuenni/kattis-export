#include <bits/stdc++.h>
using namespace std;

bool ok(int n, int k, bool need_exact) {
	if (need_exact && n < k) return false;
	return k > 20 || n < (1 << k);
}

void rec(int n, int k, bool need_exact, int offset) {
	if (n == 0) return;
	
	for (int i = 1; i <= n; i++) {
		if (!ok(i-1,k-1,need_exact)) continue;
		if (!ok(n-i,k-1,false)) continue;
		cout << offset+i << " ";
		rec(i-1,k-1,need_exact,offset);
		rec(n-i,k-1,false,offset+i);
		return;
	}
	assert(0);
}

int main() {
	int n, k;
	cin >> n >> k;
	
	if (!ok(n,k,true)) {
		cout << "impossible" << endl;
		return 0;
	}
	
	rec(n,k,true,0);
	cout << endl;
}

