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



int main() { 
	ios_base::sync_with_stdio(false); 

	int T;
	cin >> T;
	FOR(t,0,T) {
		int n;
		cin >> n;
		int sum = 0, best1 = 0, best2 = 0, cur1 = 0, cur2 = 0;
		FOR(i,0,n) {
			ll x;
			cin >> x;
			sum += x;
			cur1 = max(x, cur1+x);
			best1 = max(best1, cur1);
			cur2 = min(x, cur2+x);
			best2 = min(best2, cur2);
		}
		cout << max(best1, sum-best2) << endl;
	}
}

