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

typedef __uint128_t num;

num m[2][2];

void rec(){
	if (m[0][0] == 1 && m[0][1] == 0 && m[1][0] == 0 && m[1][1] == 1) return;
	// get bits
	int c = 0;
	if (m[0][1] < m[0][0]) FOR(j,0,2) m[j][0] -= m [j][1]; else {
		FOR(j,0,2) m[j][1] -= m [j][0];
		c =  1;
	}
	rec();
	cout << c;
}

num read(num acc){
	char c; scanf("%c",&c);
	if (c < '0' || c > '9') return acc;
	num d = c - '0';
	return read(acc*10 + d);
}

int main(){
	FOR(i,0,2) FOR(j,0,2) m[i][j] = read(0);
	rec();
	cout << endl;
}
