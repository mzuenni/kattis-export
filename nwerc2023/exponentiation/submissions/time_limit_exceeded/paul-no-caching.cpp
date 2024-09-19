#include <bits/stdc++.h>
using namespace std;

const int N = 2222;
int M = 1;
vector<int> expo[N];

int compare(int a, int b) {
	if (a == b) return 0;
	int m = size(expo[a]), n = size(expo[b]);
	for (int k = 0; k < min(m, n); k++) {
		int cur = compare(expo[a][k], expo[b][k]);
		if (cur != 0) return cur;
	}
	return m != n ? (m > n ? 1 : -1) : 0;
}

string remap(int c){
	if(c == -1)return "<";
	if(c == 0)return "=";
	return ">";
}

int main() {
	int n, m;
	cin >> n >> m;

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
