#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define FOR(i,a,b) for (ll i = (a); i < (b); i++)
#define xx first
#define yy second

vl p;

ll Find(ll x) {
	if (p[x] == x) return x;
	return p[x] = Find(p[x]);
}

bool Union(ll x, ll y) {
	x = Find(x), y = Find(y);
	if (x == y) return false;
	if (rand() & 1) swap(x,y);
	p[x] = y;
	return true;
}

int main() {
	ll n, m, k; cin >> n >> m >> k;
	p.resize(n);
	FOR(i,0,n) p[i] = i;
	
	ll len = 0;
	vector<pair<ll,pll>> v(m);
	FOR(i,0,m) {
		ll a, b, c; cin >> a >> b >> c;
		a--, b--;
		if (i < k) len += c;
		v[i] = {c,{a,b}};
	}
	sort(begin(v),end(v));
	
	ll need = n-1;
	FOR(i,0,m) if (Union(v[i].yy.xx,v[i].yy.yy)) need--, len -= v[i].xx;
	
	if (need || len < 0) cout << "im";
	cout << "possible" << endl;
}

