#include <bits/stdc++.h>
using namespace std;

const int N = 2222, undefined = 0x42424242;
int M = 1;
vector<int> expo[N];

int comp[N][N];
int compare(int a, int b) {
	if (a == b) return 0;
	if (comp[a][b] != undefined) return comp[a][b];
	int m = size(expo[a]), n = size(expo[b]);
	for (int k = 0; k < min(m, n); k++) {
		int cur = compare(expo[a][k], expo[b][k]);
		if (cur != 0) return comp[a][b] = cur;
	}
	return comp[a][b] = (m != n ? (m > n ? 1 : -1) : 0);
}

string remap(int c){
	if(c == -1)return "<";
	if(c == 0)return "=";
	return ">";
}

int main() {
	int n, m;
	cin >> n >> m;
	memset(comp, 0x42, sizeof comp);

	vector<int> v(n);
	while (m--) {
		char c;
		int i, j;
		cin >> c >> i >> j;
		i--, j--;
		if (c == '!') {
			auto &w = expo[M];
			w = expo[v[i]];
			w.push_back(v[j]);
			sort(begin(w), end(w), [&](int a, int b) {
				return compare(a, b) > 0;
			});
			v[i] = M++;
		} else {
			cout << remap(compare(v[i], v[j])) << '\n';
		}
	}
}
