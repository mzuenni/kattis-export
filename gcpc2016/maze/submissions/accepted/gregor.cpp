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
const double eps = 1e-1;
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

map<char,vi> nei[1000];

double old[1000];
double next_[1000];

int main(){
	int n,m; cin >> n >> m;
	FOR(i,0,m){
		int a,b; char c;
		cin >> a >> b >> c;
		a--;b--;
		nei[a][c].push_back(b);
		nei[b][c].push_back(a);
	}
	FOR(i,0,n) old[i] = 0.0;
	old[0] = 1.0;
	string s; cin >> s;
	FORIT(door,s){
		FOR(i,0,n) next_[i] = 0.0;
		next_[n-1] = old[n-1];
		FOR(i,0,n-1) if (sz(nei[i][*door])){
			FORIT(j,nei[i][*door])
				next_[*j] += old[i] / sz(nei[i][*door]);
		} else next_[i] += old[i];
		FOR(i,0,n) old[i] = next_[i];
	}
	cout << fixed << setprecision(20) << double(100*old[n-1]) << endl;
	return 0;
}
