#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cfloat>
#include <climits>
#include <numeric>
#include <iomanip>

using namespace std;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const double PI = 2.0 * acos(0.0);


typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<string> vs;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORS(i,a,b,s) for (int i = (a); i < (b); i=i+(s))
#define FORD(i,a,b) for (int i = int(b)-1; i >= (a); i--)
#define FORIT(i,c) for (__typeof__((c).begin()) i = (c).begin(); i != (c).end(); i++)

ll pows[11];
int N;

ll shuff(ll v, ll la, ll lb, ll lc){
	ll ld = N-la-lb-lc;
	ll va = (v / pows[N-la]) % pows[la];
	ll vb = (v / pows[N-la-lb]) % pows[lb];
	ll vc = (v / pows[N-la-lb-lc]) % pows[lc];
	ll vd = v % pows[ld];

	return (vc * pows[lb+ld+la]) + (va * pows[lb+ld]) + (vd * pows[lb]) + vb;
}

ll backshuff(ll v, ll la, ll lb, ll lc){
	ll ld = N-la-lb-lc;
	ll vb = v % pows[lb];
	ll vd = (v / pows[lb]) % pows[ld];
	ll va = (v / pows[lb+ld]) % pows[la];
	ll vc = (v / pows[lb+ld+la]) % pows[lc];

	return (va * pows[lb+lc+ld]) + (vb * pows[lc+ld]) + (vc * pows[ld]) + vd;
}

map<ll,int> visi;

int bfs(ll s, ll g, bool dir){
	queue<pair<ll,int> > q;
	if (dir) {
		q.push(make_pair(s,0));
		visi[s] = 0;
	} else {
		q.push(make_pair(g,0));
		visi[g] = -10;
	}
	
	while (sz(q)){
		pair<ll,int> v = q.front(); q.pop();
		//cout << v.first << " " << v.second << endl;
		if (dir && v.first == g) return v.second;
		// gen succ
		FOR(la,0,N) FOR(lb,0,N-la) FOR(lc,0,N-la-lb){
			ll sv = dir ? shuff(v.first,la,lb,lc) : backshuff(v.first,la,lb,lc);
			if (dir && sv == g) return v.second + 1;
			if (visi.count(sv) == 0){
				visi[sv] = (dir?1:-1) * (v.second + 1);
				if (v.second + 1 < 3) q.push(make_pair(sv,v.second+1));
			} else if (!dir && visi[sv] >= 0) return visi[sv] + v.second + 1;
		}
	}
	return -1;
}



int main(){
	cin >> N;
	ll s = 0, g = 0;
	pows[0] = 1;
	FOR(i,0,N){
		ll x; cin >> x; x--;
		pows[i+1] = pows[i] * 10;
		s = 10*s + x;
		g = 10*g + i;
	}
	visi.clear();
	int r1 = bfs(s,g,true);
	if (r1 != -1) { cout << r1 << endl; return 0; }
	int r2 = bfs(s,g,false);
	if (r2 != -1) cout << r2 << endl; else cout << 7 << endl;
	return 0;
}




















