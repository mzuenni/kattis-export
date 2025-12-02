#include <bits/stdc++.h>
using namespace std;

#define fora(i, n) for (int i = 0; i < n; ++i)

using ll = long long;

int idxof(const vector<ll> a, int l) {
	fora(i, (int)a.size()) {
		if (a[i] == l) return i;
	}
	return -1;
}

int main() {
	int n;
	cin >> n;
	vector<ll> a(n);
	fora(i, n) cin >> a[i];

	vector<pair<ll, ll>> ans;
	while (n > 5) {
		int idx = idxof(n - 1);
	}
}

