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

const int maxN = 50000;

vi adj1[maxN];
vi adj2[maxN];

bool loopFound;
bool trapped;

int reachable1[maxN];
bool reachable2[maxN];

void dfs1(int i) {
	reachable1[i] = 1;
	bool res = false;
	for (const auto &j : adj1[i]) {
		if (reachable1[j] == 1) loopFound = true;
        if (reachable1[j] == 0) dfs1(j);
	}
	reachable1[i] = 2;
}

void dfs2(int i) {
	reachable2[i] = true;
	for (const auto &j : adj2[i]) {
		if (!reachable2[j]) dfs2(j);
	}
}

int main() { 
	ios_base::sync_with_stdio(false); 
	
	int n;
	cin >> n;

	FOR(from,0,n-1) {
		int k;
		cin >> k;
		FOR(j,0,k) {
			int to;
			cin >> to;
			to--;
			adj1[from].pb(to);
			adj2[to].pb(from);
		}
	}
	
	
	dfs1(0);
	dfs2(n-1);
	FOR(i,0,n) trapped |= reachable1[i] && !reachable2[i];
	
	cout << ((trapped) ? "PRISON " : "PARDON ");
	cout << ((loopFound) ? "UNLIMITED" : "LIMITED");
	cout << endl;

}


