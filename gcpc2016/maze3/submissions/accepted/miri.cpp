#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;
using vvl = vector<vl>;
using pll = pair<ll,ll>;
using vb = vector<bool>;
const ll oo = 0x3f3f3f3f3f3f3f3fLL;
const double eps = 1e-9;
#define sz(c) ll((c).size())
#define all(c) begin(c),end(c)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define xx first
#define yy second
#define has(c,i) ((c).find(i) != end(c))
#define FOR(i,a,b) for (int i=(a); i<(b); i++)       
#define FORD(i,a,b) for (int i=int(b)-1; i>=(a); i--)
#define DBGDO(X) ({ if(1) cerr << "DBGDO: " << (#X) << " = " << (X) << endl; })

vl e[1010][26];
double prob[2][1010];

int main() { 
	ios::sync_with_stdio(false); 
	ll n, m;
	cin >> n >> m;
	FOR(i,0,m){
		ll a,b;
		char c;
		cin >> a >> b >> c;
		e[a-1][c - 'A'].pb(b-1);
		e[b-1][c - 'A'].pb(a-1);
	}
	string s;
	cin >> s;
	double sol = 0;
	FOR(i,0,n) FOR(j,0,2) prob[j][i] = 0;
	prob[1][0] = 1;
	FOR(k,0,sz(s)){
		ll g = s[k] - 'A';
		if(prob[(k+1)%2][n-1] > 0){
			sol += prob[(k+1)%2][n-1];
			prob[(k+1)%2][n-1] = 0;
		}
		FOR(i,0,n) prob[k%2][i] = 0;
		FOR(i,0,n){
			FOR(j,0,sz(e[i][g])){
				prob[k%2][e[i][g][j]] += prob[(k+1)%2][i]/sz(e[i][g]); 
			}
			if(sz(e[i][g]) == 0) prob[k%2][i] += prob[(k+1)%2][i];
		}
	}
	if(prob[(sz(s)-1)%2][n-1] > 0){
		sol += prob[(sz(s)-1)%2][n-1];
		prob[(sz(s)-1)%2][n-1] = 0;
	}
	cout << fixed << setprecision(12) << sol*100 << endl;
}
