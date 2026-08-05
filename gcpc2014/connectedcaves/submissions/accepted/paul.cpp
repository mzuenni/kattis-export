#include <list>
#include <map>
#include <stack>
#include <queue>
#include <set>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cfloat>
#include <numeric>
#include <iomanip>
#include <cassert>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <tuple>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int,int> pii;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORD(i,a,b) for (int i = int(b)-1; i >= (a); i--)
#define FORIT(i,c) for (auto i=(c).begin(); i!=(c).end(); i++)
#define mp make_pair
#define pb push_back
#define has(c,i) ((c).find(i) != (c).end())
#define DBG(...) ({ if(1) fprintf(stderr, __VA_ARGS__); })
#define DBGDO(X) ({ if(1) cerr << "DBGDO: " << (#X) << " = " << (X) << endl; })

const int maxN = 40000;
int N;

int indeg[maxN];
vector<pii> adj[maxN];
vi sorted;
int best[maxN];
int pred[maxN];

bool top_sort() { 
	fill_n(indeg, N, 0); 
	FOR(i, 0, N) FOR(j, 0, sz(adj[i])) indeg[adj[i][j].first]++;  
	stack<int> zero; 
	FOR(i, 0, N) if (indeg[i] == 0) zero.push(i); 
	sorted.clear(); 
	while (!zero.empty()) { 
		int n = zero.top();    
		zero.pop();   
		sorted.push_back(n); 
		FOR(i, 0, sz(adj[n])) { 
			if (--indeg[adj[n][i].first] == 0) zero.push(adj[n][i].first);
		}
	}
	return sz(sorted) == N;
}

int main() { 
	ios_base::sync_with_stdio(false); 
	
	int T;
	cin >> T;
	FOR(t,0,T) {
		int E;
		cin >> N >> E;
		N *= 2;
		FOR(i,0,N) adj[i].clear();
		FOR(i,0,N/2) {
			int v;
			cin >> v;
			adj[2*i].pb(mp(2*i+1,v));
		}
		FOR(i,0,E) {
			int a, b, c;
			cin >> a >> b >> c;
			a--; b--;
			adj[2*a+1].pb(mp(2*b,-c));
		}
		top_sort();

		fill_n(best, N, -1000000000);
		best[0] = 0;
		pred[0] = -1;
		int res = 0;
		int resLast = 0;
		FOR(i,0,N) {
			int from = sorted[i];
			for (const auto &p : adj[from]) {
				int to = p.first;
				if (best[from] + p.second > best[to]) {
					best[to] = best[from] + p.second;
					pred[to] = from;
					if (best[to] > res) {
						res = best[to];
						resLast = to;
					}
				}
			}
		}
		
		vi bestPath;
		while (resLast != -1) {
			if (resLast % 2 == 0) bestPath.pb(resLast);
			resLast = pred[resLast];
		}
		reverse(all(bestPath));
		cout << res << " " << bestPath.size() << endl;
		FOR(i,0,bestPath.size()) {
			if (i != 0) cout << " ";
			cout << (bestPath[i]/2 + 1);
		}
		cout << endl;
	}
}
