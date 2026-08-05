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

vl a[10010];
ll vis[10010];

bool dag(ll i, ll start){
	if(vis[i] == start) return false;
	if(vis[i] != -1) return true;
	vis[i] = start;
	FOR(j,0,sz(a[i])){
		if(!dag(a[i][j], start)) return false;
	}
	vis[i] = oo;
	return true;
}

int main() { 
	ios::sync_with_stdio(false); 
	ll n;
	cin >> n;
	map<string, ll> name;
	FOR(i,0,n){
		string n1, n2, c;
		cin >> n1 >> c >> n2;
		if(!has(name, n1)) name[n1] = sz(name);
		if(!has(name, n2)) name[n2] = sz(name);
		if(c == ">") a[name[n1]].pb(name[n2]);
		else a[name[n2]].pb(name[n1]);
	}
	FOR(i,0,10010) vis[i] = -1;
	FOR(i,0,10010){
		if(vis[i] == -1){
			if(!dag(i, i)){
				cout << "impossible" << endl;
				return 0;
			}
		}
	}
	cout << "possible" << endl;
}
