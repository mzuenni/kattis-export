// 
// 
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
const long long ool = 0x3f3f3f3f3f3f3f3fL;
const double eps = 1e-9;
const double PI = 2.0 * acos(0.0);


typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<string> vs;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORS(i,a,b,s) for (int i = (a); i < (b); i=i+(s))
#define FORD(i,a,b) for (int i = int(b)-1; i >= (a); i--)
#define FORIT(i,c) for (__typeof__((c).begin()) i = (c).begin(); i != (c).end(); i++)

ll w[100];
ll d[1000000];

int main(){
	ll N,K;
	cin >> N >> K;
	FOR(i,0,N) cin >> w[i];
	std::sort(&(w[0]), &(w[N]));
	
	FOR(i,0,w[0]) d[i] = ool;

	d[0]=0L;
	FOR(i,0,N)
	   FOR(j,0,w[0])
		if(d[j]!=ool){
		   int current=j;
		   while(true){
		      int next=(current+w[i])%w[0];
		      ll nextValue=d[current]+w[i];
		      if(d[next]<=nextValue)
			 break;
		      d[next]=nextValue;
		      current=next;
		   }
	        }
		

	if ( d[K%w[0]] <= K  && d[K%w[0]] != ool) cout << "possible" << endl;
	else cout << "impossible" << endl;
}
