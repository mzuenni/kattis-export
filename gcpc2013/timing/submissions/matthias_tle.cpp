// @EXPECTED_RESULTS@: TIMELIMIT

#include <list>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cfloat>
#include <numeric>
#include <iomanip>
#include <cassert>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int, int> pii;

const int oo = 0x3f3f3f3f;
const double eps = 1e-6;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORD(i,a,b) for (int i = int(b)-1; i >= (a); i--)
#define FORIT(i,c) for(__typeof__((c).begin()) i=(c).begin(); i!=(c).end(); i++)
#define mp make_pair
#define pb push_back
#define DBG(...) { if(1) fprintf(stderr, __VA_ARGS__); }
#define DBGDO(X) { if(1) cerr << "DBGDO: " << (#X) << " = " << (X) << endl; }

#define MAX_N 10000

double starting [MAX_N];
double after_step [MAX_N];
double matrix [MAX_N][MAX_N];
bool linked [MAX_N][MAX_N];


int main (){
    int TC;
    cin >> TC;
    while(TC--){
        memset(matrix, 0, sizeof(matrix));
        memset(linked, 0, sizeof(linked));
        int N, t, l;
        cin >> N >> l >> t;
        FOR(i,0,N){
            cin >> starting[i];
        }    
        FOR(i,0,N){
            matrix[i][i]=1;
            linked[i][i]=true;
        }
        FOR(i,0,l){
            int s, t;
            double p;
            cin >> s >> t >> p;
            matrix[t][s]=p;
            matrix[s][s]-=p;
            linked[s][t]=true;
            linked[t][s]=true;
        }
    
        
        double *act=starting, *next=after_step, *tmp;
        
        FOR(m,0,t){
            FOR(i,0,N){ 
                next[i]=0;
            }
            FOR(i,0,N){
                FOR(j,0,N){
                    next[i]+=matrix[i][j]*act[j];
                }
            }
            
            tmp=act;
            act=next;
            next=tmp;
        }
        double *ending = act;
        double best=oo;
        FOR(i,0,N){
            double test=0;
            FOR(j,0,N){
                if(linked[j][i]) test += ending[j];
            }
            if(test<best) best=test;
        }
        printf("%.9lf\n", best);
    }
	return 0;
}