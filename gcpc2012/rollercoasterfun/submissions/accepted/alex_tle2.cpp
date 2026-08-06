// @EXPECTED_RESULTS@: CORRECT
#include <list>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cfloat>
#include <numeric>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int, int> pii;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORD(i,a,b) for (int i = int(b)-1; i >= (a); i--)
#define FORIT(i,c) for (__typeof__((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define mp(a,b) make_pair(a,b)
#define pb(a) push_back(a)

const int MAXT = 25000;
const int MAXN = 110;
int dp[MAXT +  100], N, T, a, b, t, Q;
struct Rollercoaster{
	int a, b, t;
} inp[MAXN];
bool operator<(const Rollercoaster&r1, const Rollercoaster &r2){
	if(r1.a *r2.t != r2.a*r1.t)return r1.a*r2.t > r2.a*r1.t;
	if(r1.a != r2.a)return r1.a > r2.a;
	return r1.b < r2.b;
}
int main() {
	for(int i = 0; i <= MAXT; i++)dp[i] = 0;
	cin >> N;
	T = MAXT;
	FOR(i,0,N){
		cin >> inp[i].a >> inp[i].b >> inp[i].t;
	}
	sort(inp,inp+N);
	FOR(i,0,N){
		a = inp[i].a;
		b = inp[i].b;
		t = inp[i].t;
		bool change = 1;
		for(int k = 0, fun = a; fun > 0 && change; ++k){
			change = 0;
			for(int ct = T; ct >= t; ct--)if(dp[ct] < dp[ct-t] + fun){
				dp[ct] = dp[ct-t] + fun;
				change = 1;
			}
			fun -= (1 + 2*k) * b;
		}
	}
	cin >> Q;
	while(Q--){
		cin >> T;
		cout << dp[T] << endl;
	}
	return 0;
}
