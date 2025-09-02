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

double S[100];
double D[100];

double dp[101][101];

char team[100][100];

int main(){
	int t,p; cin >> t >> p;
	FOR(i,0,t-1) cin >> S[i];
	FOR(j,0,p) cin >> D[j];

	FOR(i,0,t) FOR(j,0,p) cin >> team[i][j];
	int sol = 0;
	FOR(j,0,p) if (team[t-1][j] == 'X') sol++;

	double win = 1;
	FOR(ct,0,t-1){
		dp[0][0] = 1;
		FOR(i,1,p+1) dp[0][i] = 0;

		FOR(i,1,p+1) FOR(s,0,p+1){
			if (team[ct][i-1] == 'X'){
				if (s) dp[i][s] = dp[i-1][s-1]; else dp[i][s] = 0;
			} else if(team[ct][i-1] == '-'){
				dp[i][s] = dp[i-1][s];
			} else {
				if (s){
					dp[i][s] = (1-S[ct]*D[i-1])*dp[i-1][s] + S[ct]*D[i-1]*dp[i-1][s-1];
				}
				else
					dp[i][s] = (1-S[ct]*D[i-1])*dp[i-1][s]; // not to solve
			}
		}

		double w = 0;
		FOR(i,sol+1,p+1) w += dp[p][i];
		win *= (1-w);
	}

	cout << win << endl;
}

















