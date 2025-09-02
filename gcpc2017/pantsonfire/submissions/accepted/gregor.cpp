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

#define MAXN 193

bool worse[MAXN][MAXN];

map<string,int> _m;

int get(string s){
		if (!_m.count(s)) _m[s] = sz(_m);
		return _m[s];
}

int main(){
		int N,M; cin >> N >> M;
		FOR(i,0,MAXN) FOR(j,0,MAXN) worse[i][j] = 0;
		FOR(i,0,N){
				string A,x,y,z,B;
				cin >> A >> x >> y >> z;
				cin >> B;
				worse[get(A)][get(B)] = 1;
		}
		// transitive hull
		FOR(i,0,MAXN) FOR(j,0,MAXN) FOR(k,0,MAXN) worse[j][k] |= worse[j][i] && worse[i][k];

		FOR(i,0,M){
				string A,x,y,z,B;
				cin >> A >> x >> y >> z;
				cin >> B;
				if (worse[get(A)][get(B)])
						cout << "Fact" << endl;
				else if (worse[get(B)][get(A)])
						cout << "Alternative Fact" << endl;
				else
						cout << "Pants on Fire" << endl;
		}
}


















