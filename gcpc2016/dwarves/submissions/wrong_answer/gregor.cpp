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


map<string,bool> visi;
map<string,vs> nei;


bool dfs(string n){
	if (visi.count(n)) return visi[n];
	visi[n] = true;
	FORIT(i,nei[n]) if (dfs(*i)) return true;
	return false;
}



int main(){
	string _t;
	int d;
	cin >> d;
	
	FOR(i,0,d){
		string a,b,r; cin >> a >> r >> b;
		b = b.substr(0,sz(b)-1);
		if (r == ">") nei[a].push_back(b); else nei[b].push_back(a);
	}
	
	bool cyc = false;
	FORIT(s,nei) if (!visi.count(s->first)) cyc |= dfs(s->first);
	if (cyc) cout << "impossible" << endl; else cout << "possible" << endl;
}
