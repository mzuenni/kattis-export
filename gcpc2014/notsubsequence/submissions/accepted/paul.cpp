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

const ll M = 1000000007;

int main() { 
	ios_base::sync_with_stdio(false); 
	
	int a[62];
	FOR(i,0,26) a[i] = 'a'+i;
	FOR(i,0,26) a[i+26] = 'A'+i;
	FOR(i,0,10) a[i+52] = '0'+i;
	
	int T;
    scanf("%d\n", &T);

	FOR(t,0,T) {
		
		int k;
		scanf("%d ", &k);

		int blockCount = 1;
		ll p = 1;
		int startOfBlock = 1;
		int last[256] = {};
		ll val[1000001];
		val[0] = 0;
		int foundInBlock = 0;
	
		char c;
		int i = 1;
		while (true) {
			c = getchar();
			if (c == '\n') break;
			val[i] = 0;
			FOR(j,0,k) val[i] += (last[a[j]] < startOfBlock) ? val[last[a[j]]] : p;
			val[i] %= M;
			if (last[c] < startOfBlock) foundInBlock++;
			last[c] = i;
			if (foundInBlock == k) {
				blockCount++;
				startOfBlock = i+1;
				foundInBlock = 0;
				p *= k;
				p %= M;
			}
			i++;
		}
		ll res = p*k;
		FOR(j,0,k) res -= (last[a[j]] < startOfBlock) ? val[last[a[j]]] : p;
		res %= M;
		if (res < 0) res += M;
		cout << blockCount << " " << res << endl;

	}

}

