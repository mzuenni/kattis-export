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

vi adj[1000];

int rTime[1000];
int rCost[1000];


int minCost[1001][1000]; // time spend, current position


int main(){
	int X; cin >> X;
	int N,M,T; cin >> N >> M >> T;
	FOR(i,0,N) adj[i].clear();
	FOR(i,0,M){
		int a,b; cin >> a >> b;
		a--, b--;
		adj[b].push_back(a);
		adj[a].push_back(b);
	}
	FOR(i,0,N) cin >> rTime[i] >> rCost[i];
	FOR(i,0,N) minCost[0][i] = oo;
	minCost[0][0] = 0;
	if (rTime[0] > X){
		cout << "It is a trap." << endl;
		return 0;
	}
	X -= rTime[0];


	// run DP
	FOR(t,1,X+1) FORD(i,0,N) if (rTime[i] > t) minCost[t][i] = oo; else {
		// default: stay where you are
		minCost[t][i] = minCost[t - rTime[i]][i];
		//cout << "T " << t << " I " << i << " " << minCost[t][i] << endl;
		// where could I have come from
		FORIT(j,adj[i]) {
			//cout << "J " << *j << " " <<minCost[t-rTime[i]][*j] << endl; 
			if (t>=rTime[i]+T) minCost[t][i] = min(minCost[t][i], minCost[t-rTime[i]-T][*j]);
		}

		minCost[t][i] += rCost[i];
		//cout << "T " << t << " I " << i << " " << minCost[t][i] << endl;
	}

	if (minCost[X][0] < oo) cout << rCost[0] + minCost[X][0] << endl;
	else cout << "It is a trap." << endl;
}
