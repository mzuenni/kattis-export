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
typedef float ld;
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

#define MAXN 1000

ld d[MAXN];
vi adj[MAXN];
vector<ld> w[MAXN];

int main(){
		int n,m; cin >> n >> m;
		FOR(i,0,m){
				int x,y; ld v; cin >> x >> y >> v;
				x--,y--;
				adj[x].push_back(y);
				w[x].push_back(log(v));
		}


		FOR(i,0,n) d[i] = 0;
		FOR(i,0,n) FOR(j,0,n) FOR(k,0,sz(adj[j])) {
				if (d[j] + w[j][k] > d[adj[j][k]]){
						d[adj[j][k]] = d[j] + w[j][k];
						if (i == n-1){
								cout << "inadmissible" << endl;
								return 0;
						}
				}
		}

		cout << "admissible" << endl;
		return 0;
}
