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

const int maxN = 100;
const int maxM = 100;
int N, M;
vi adj[maxN];
int pred[maxM];
bool mark[maxM];
bool exh[maxN][maxM];

bool find_match(int n) {  
	if (n == -1) return true;  
	for (const auto &to : adj[n]) {    
		if (mark[to]) continue;  
		mark[to] = true; 
		if (find_match(pred[to])) {   
			pred[to] = n; 
			return true;   
		} 
	}
	return false;
}

int max_matching() { 
	fill_n(pred, M, -1); 
	int matching = 0;
	FOR(i, 0, N) {   
		fill_n(mark, M, false); 
		if (find_match(i)) matching++; 
	}
	return matching;
}

int main() { 
	ios_base::sync_with_stdio(false); 
	
	int T;
	cin >> T;

	FOR(t,0,T) {
		int k;
		cin >> N >> M >> k;
		FOR(i,0,maxN) FOR(j,0,maxM) exh[i][j] = false;
								
		FOR(i,0,maxN) adj[i].clear();
		FOR(i,0,k) {
			double xx, yy;
			cin >> xx >> yy;
			int x = floor(xx), y = floor(yy);
			if (!exh[x][y]) {
				adj[x].pb(y);
				exh[x][y] = true;
			}
		}
		cout << max_matching() << endl;
	}

}


