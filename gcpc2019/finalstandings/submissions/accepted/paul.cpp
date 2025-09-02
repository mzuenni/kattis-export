#include <bits/stdc++.h>
using namespace std;

#define FOR(i,n) for (int i = 0; i < (n); i++)

vector<double> update(vector<double> p, double q) {
	vector<double> np(p.size()+1);
	FOR(i,p.size()) np[i] += p[i]*(1-q), np[i+1] += p[i]*q;
	return np;
}

int main() {
	int n, m; cin >> n >> m;
	n--;
	
	vector<double> s(n), d(m);
	FOR(i,n) cin >> s[i];
	FOR(i,m) cin >> d[i];
	
	vector<vector<double>> p(n,vector<double>(1,1));
	FOR(i,n) FOR(j,m) {
		char c; cin >> c;
		p[i] = update(p[i], c == '?' ? s[i]*d[j] : c == 'X');
	}
	
	int sum = 0;
	FOR(j,m) {
		char c; cin >> c;
		sum += c == 'X';
	}
	
	double res = 1;
	FOR(i,n) {
		double cur = 0;
		FOR(j,sum+1) cur += p[i][j];
		res *= cur;
	}
	cout << fixed << setprecision(20) << res << endl;
}
