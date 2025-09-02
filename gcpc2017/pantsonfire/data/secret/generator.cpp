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

int N,C; // C <= 193

int base[193][193];

int dp[193][193];


bool isCyclic(){
		FOR(i,0,C) FOR(j,0,C) dp[i][j] = base[i][j];
		FOR(i,0,C) FOR(j,0,C) FOR(k,0,C) if (dp[i][j] && dp[j][k]) dp[i][k] = 1;
		FOR(i,0,C) if (dp[i][i]) return true;
		return false;	
}


string names[193];

int main(){
		int seed; cin >> seed;
		srand(seed);
		cin >> N >> C;

		cout << N << " " << 200 << endl;
		// generate country names
		FOR(i,0,C) names[i] = "aa";
		FOR(i,0,C) names[i][0] = 'a' + (i%26);
		FOR(i,0,C) names[i][1] = 'a' + (i/26);


		FOR(i,0,C) FOR(j,0,C) base[i][j] = 0;
		// generate a graph and ensure that it is not cyclic
		FOR(i,0,N){
				// guess one edge
				int a = rand() % C;
				int b = rand() % C;
				if (a == b || base[a][b]){
						i--;
						continue;
				}
				base[a][b] = 1;
				if (!isCyclic()){
						cout << names[a] << " are worse than " << names[b] << endl;
						continue;
				}
				i--;
				base[a][b] = 0;	
		}

		FOR(i,0,200){
				// guess one edge
				int a = rand() % C;
				int b = rand() % C;
				if (a == b || base[a][b]){
						i--;
						continue;
				}
				cout << names[a] << " are worse than " << names[b] << endl;
		}



}































