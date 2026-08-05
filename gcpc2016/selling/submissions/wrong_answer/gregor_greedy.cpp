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

pair<double,pii> p[10001];

int main(){
	int c,m; cin >> c >> m;
	FOR(i,0,m) FOR(j,0,c) {
		cin >> p[i*m+j].first;
		p[i*m+j].first /= (j+1);
		p[i*m+j].second.first = i;
		p[i*m+j].second.second = j+1;
	}
	sort(p,p+m*c);
	reverse(p,p+m*c);
	
	set<int> avail;
	FOR(i,0,m) avail.insert(i);
	
	int remC = c;
	int prof = 0;
	FOR(i,0,m*c) if (p[i].second.second <= remC && avail.count(p[i].second.first)) {
		prof += p[i].first * p[i].second.second;
		remC -= p[i].second.second;
		avail.erase(p[i].second.first);
	}
	cout << prof << endl;
}










