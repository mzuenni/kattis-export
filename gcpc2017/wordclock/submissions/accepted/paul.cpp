#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)

const int N = 20;
int height, width, n;
int d[N][N];
pair<int,int> dp[1 << N][N];
int pred[1 << N][N];

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
	
	// travelling salesman DP
	memset(dp, 0x3f, sizeof dp);
	FOR(i,0,n) dp[1 << i][i] = make_pair(0, s[i].size());
	
	FOR(mask,0,1 << n) FOR(i,0,n) if (mask & (1 << i))
		FOR(j,0,n) if ((mask & (1 << j)) == 0) {
			pair<int,int> p = dp[mask][i];
			p.second += d[i][j];
			if (p.second > width)
				p.first++, p.second = s[j].size();
			if (p >= dp[mask ^ (1 << j)][j]) continue;
			dp[mask ^ (1 << j)][j] = p;
			pred[mask ^ (1 << j)][j] = i;
		}
	
	// reconstruct
	int mask = (1 << n) - 1, i = -1;
	FOR(j,0,n) if (dp[mask][j].first < height) i = j;
	
	if (i == -1) {
		cout << "impossible" << endl;
		return 0;
	}
	
	vector<string> a(height,string(width,'X'));
	while (mask) {
		int r, c;
		tie(r, c) = dp[mask][i];
		
		FOR(j,0,s[i].size())
			a[r][c-s[i].size()+j] = s[i][j];

		int nmask = mask ^ (1 << i);
		i = pred[mask][i];
		mask = nmask;
	}
	
	FOR(i,0,height) cout << a[i] << endl;
}
