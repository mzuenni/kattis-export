#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
int H[N], L[N], R[N], ord[N], m;

void traverse(int i) {
	if (L[i]) traverse(L[i]);
	ord[i] = ++m;
	if (R[i]) traverse(R[i]);
}

int main() {
	int n, k;
	cin >> n >> k;
	if (k < 20 && n >= 1 << k) {
		cout << "impossible" << endl;
	} else {
		for (int i = 1; i <= k; i++) H[i] = L[i-1] = i;
		m = k;
		for (int i = 1; m < n; i++) if (H[i] < k) {
			if (L[i] == 0) L[i] = ++m, H[m] = H[i]+1;
			if (R[i] == 0) R[i] = ++m, H[m] = H[i]+1;
		}
		m = 0;
		traverse(1);
		for (int i = 1; i <= n; i++) cout << ord[i] << " \n"[i==n];
	}
}
