#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)

const int N = 20;
int height, width, n;
int d[N][N];

int main() {
	cin >> height >> width >> n;
	vector<string> s(n);
	for (int i = 0; i < n; i++) {
		cin >> s[i];
		if (s[i].size() > width) {
			cout << "impossible" << endl;
			return 0;
		}
	}
	
	// eliminate substrings
	vector<string> ns;
	FOR(i,0,n) {
		bool ok = true;
		FOR(j,0,n) ok = ok && (i == j || s[j].find(s[i]) == string::npos);
		if (ok) ns.push_back(s[i]);
	}
	s = ns;
	n = s.size();

	// find distances
	FOR(i,0,n) FOR(j,0,n) if (i != j) {
		int si = s[i].size(), sj = s[j].size();
		FOR(k,0,min(si,sj))
			if (s[i].substr(si-k) == s[j].substr(0, k))
				d[i][j] = sj-k;
	}
	
	vector<string> a(height,string(width,'F'));
	vector<int> p(n);
	iota(begin(p),end(p),0);
	do {
		int r = 0, c = 0;
		
		FOR(j,0,s[p[0]].size()) a[r][c++] = s[p[0]][j];
		
		bool ok = true;
		FOR(i,1,n) {
			ok = false;
			c -= s[p[i]].size() - d[p[i-1]][p[i]];
			if (c + s[p[i]].size() > width) r++, c = 0;
			if (r >= height) break;
			
			FOR(j,0,s[p[i]].size()) a[r][c++] = s[p[i]][j];

			if (i == n-1) ok = true;
		}	
		if (ok) {
			FOR(i,0,height) cout << a[i] << endl;
			return 0;
		}
	} while (next_permutation(begin(p),end(p)));
	
	cout << "impossible" << endl;
}
