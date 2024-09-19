#include <bits/stdc++.h>
using namespace std;

const int nax = 1e5 + 5;
int n, t[4*nax]; // root vertex = 1

int sum(int v, int TL, int TR, int L, int R) {
	if (L > R) 
		return 0;
	if (L == TL && R == TR) {
		return t[v];
	}
	int TM = (TL+TR)/2;
	return sum(v*2, TL, TM, L, min(R, TM)) + sum(v*2+1, TM+1, TR, max(L, TM+1), R);
}

void upd(int v, int TL, int TR, int idx, int val) {
	if (TL == TR) {
		t[v] = val;
	} else {
		int TM = (TL + TR) / 2;
		if (idx <= TM)
			upd(v*2, TL, TM, idx, val);
		else
			upd(v*2+1, TM+1, TR, idx, val);
		t[v] = t[v*2] + t[v*2+1];
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, q;
	cin >> n >> q;
	for (int i = 0; i < q; i++) {
		char t; cin >> t;
		if (t == '-') {
			int a; cin >> a; a--;
			upd(1, 0, n-1, a, 1);
		} else if (t == '+') {
			int a; cin >> a; a--;
			upd(1, 0, n-1, a, 0);
		} else {
			int a, b;
			cin >> a >> b;
			a--; b--;
			if (a > b) swap(a, b);

			// count blocked segments
			int between = sum(1, 0, n-1, a, b);
			int before = sum(1, 0, n-1, 0, a);
			int after = sum(1, 0, n-1, b, n-1);
			if (between > 0 && (before > 0 || after > 0))
				cout << "impossible" << endl;
			else
				cout << "possible" << endl;
		}
	}
	return 0;
}
