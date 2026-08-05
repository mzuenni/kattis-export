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

int best[100][100];
int proc[100];
vi adj[100];
vector<set<int> > forb[100];


int main(){
	int n; cin >> n;
	FOR(i,0,n){
		int m; cin >> m >> proc[i];
		FOR(j,0,m){
			int s,x; cin >> s >> x;
			x--;
			set<int> f;
			FOR(k,0,s){
				int _x; cin >> _x;
				_x--; f.insert(_x);
			}
			adj[i].push_back(x);
			forb[i].push_back(f);
		}
	}
	
	FOR(i,0,n) FOR(j,0,n) best[i][j] = -oo;
	priority_queue<pair<int,pii> > q;
	q.push(make_pair(-proc[0],make_pair(0,-1)));
	while (sz(q)){
		pair<int,pii> sn = q.top();
		q.pop();
		int nn = sn.second.first;
		int last = sn.second.second;
		
		if (nn == n-1){
			cout << -sn.first << endl;
			return 0;
		}
		
		FOR(i,0,sz(adj[nn])) if (forb[nn][i].count(last) == 0){
			int nDist = sn.first - proc[adj[nn][i]];
			if (nDist > best[adj[nn][i]][nn]){
				best[adj[nn][i]][nn] = nDist;
				q.push(make_pair(nDist,make_pair(adj[nn][i],nn)));
			}
		}
	}
	cout << "impossible" << endl;
}
