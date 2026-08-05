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

vi nei[50000];
vi w[50000];
bool visi[50000];

int dfs(int i){
	if (visi[i]) return 0;
	visi[i] = true;
	int s = 0;
	FOR(j,0,sz(nei[i])) if (!visi[nei[i][j]]) s+= w[i][j] + dfs(nei[i][j]);
	return s;
}


int main(){
	int n,m,l,s=0; cin >> n >> m >> l;
	FOR(i,0,n) visi[i] = false;
	FOR(i,0,m){
		int x,y,d; cin >> x >> y >> d;
		x--,y--;
		nei[x].push_back(y); w[x].push_back(d);
		nei[y].push_back(x); w[y].push_back(d);
		if (i < l) s+=d;
	}
	if (s >= dfs(0)) cout << "possible" << endl; else cout << "impossible" << endl;
}
