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

double c[3][2];
double l[3];

int main(){
	FOR(i,0,3) FOR(j,0,2) cin >> c[i][j];
	FOR(i,0,3) {
		double x = c[i][0] - c[(i+1)%3][0];
		double y = c[i][1] - c[(i+1)%3][1];
		l[i] = sqrt(x*x + y*y);
	}
	double s = (l[0]+l[1]+l[2])/2;
	double inner = l[0]*l[0] + l[1]*l[1] - l[2]*l[2];
	double A = 0.25 * sqrt(4*l[0]*l[0]*l[1]*l[1] - inner*inner);
	
	double r = A / s;
	
	double hand; cin >> hand;
	
	cout << fixed << setprecision(3) << 100 * (r-hand)/hand << endl;
}










