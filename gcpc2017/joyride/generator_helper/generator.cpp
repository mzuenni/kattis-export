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




int main(){
	int seed; cin >> seed;
	srand(seed);
	
	int X; cin >> X;
	int N,M,T; cin >> N >> M >> T;

	cout << X << endl;
	cout << N << " " << M << " " << T << endl;
	set<pii> es;
	FOR(i,0,M) {
		int x[2];
		do {
			x[0] = rand() % N;
			x[1] = rand() % N;
		} while (x[0] == x[1] || es.count(make_pair(x[0],x[1])));
		es.insert(make_pair(x[0],x[1]));
		cout << x[0] << " " << x[1] << endl;
	}
	
	FOR(i,0,N)
		cout << (rand() % (max(X/15,10)))+1 << " " << (rand() % (max(X/15,10)))+1 << endl;


}









