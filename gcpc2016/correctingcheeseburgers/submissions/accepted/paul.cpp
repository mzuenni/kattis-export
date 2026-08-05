#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vl;
#define sz(c) ll((c).size())
#define FOR(i,a,b) for (ll i = (a); i < (b); i++)
#define has(c,i) ((c).find(i) != end(c))

ll n;
const ll seg[2][4] = {{2,0,3,1},{1,3,0,2}};

vl permute(const vl &p, array<ll,5> bnds, ll dir) {
	vl q; q.reserve(n);
	FOR(k,0,4) FOR(i,bnds[seg[dir][k]],bnds[seg[dir][k]+1]) q.push_back(p[i]);
	return q;
}

int main() {
	cin >> n;
	vl p[2] = {vl(n),vl(n)};
	FOR(i,0,n) cin >> p[0][i], p[0][i]--, p[1][i] = i;
	if (p[0] == p[1]) { cout << 0 << endl; return 0; }

	map<vl,ll> d[2];
	queue<pair<ll,vl>> q;
	FOR(k,0,2) d[k][p[k]] = 0, q.emplace(k,p[k]);
	
	while (sz(q)) {
		ll i; vl p;
		tie(i,p) = q.front(); q.pop();
		FOR(a,0,n+1) FOR(b,a,n+1) FOR(c,b,n+1) {
			vl np = permute(p,{0,a,b,c,n},i);
			if (has(d[i],np)) continue;
			if (has(d[!i],np)) {
				cout << d[!i][np] + d[i][p] + 1 << endl;
				return 0;
			}
			d[i][np] = d[i][p] + 1, q.emplace(i,np);
		}
	}
}

