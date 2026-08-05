// 
// 
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


#define MAXN 50001
#define MAXE 250001

struct edge { int x,y; ll d; };
bool operator <(const edge& e1, const edge& e2){ return (e1.d<e2.d); }
edge e[MAXE];
int u[MAXE];
int pa[MAXN];
int rk[MAXN];

int ufind(int i) { // returns component i belongs to
	if(pa[i]!=i) pa[i]=ufind(pa[i]);
	return pa[i];
}
int uunion(int a,int b) { // 1 if unified, 0 else
	a=ufind(a);
	b=ufind(b);
	if(a == b) return 0;
	if(rk[a]>rk[b])
		pa[b]=a;
	else
		pa[a]=b;
	if(rk[a]==rk[b]) rk[b]++;
	return 1;
}

ll kruskal(int n, int m) { // returns sum of weights
	sort(e, e+m);
	FOR(i,0,n) { // init union find
		pa[i]=i;
		rk[i]=0;
	}
	ll sum=0;
	FOR(i,0,m) {
		u[i] = uunion(e[i].x,e[i].y);
		if(u[i]) sum+=e[i].d;
	}
	return sum;
}

int main(){
	int n,m,l; cin >> n >> m >> l;
	FOR(i,0,m) cin >> e[i].x >> e[i].y >> e[i].d, e[i].x--, e[i].y--;
	ll s = 0;
	FOR(i,0,l) s += e[i].d;
	if (s >= kruskal(n,m)) cout << "possible" << endl; else cout << "impossible" << endl;
}
