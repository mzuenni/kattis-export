#include <algorithm>
#include <iostream>

using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)

#define STRICTLY_CONVEX 1

long long x[128][2];
double p;
int N;
int main() {
	cin >> p >> N;
	FOR(i,0,N)FOR(j,0,2)cin >> x[i][j];
	long long dir = 0;
	FOR(i,0,N){
		long long cdir = 0;
		FOR(j,1,4){
			cdir += x[(i+j-1)%N][0] * x[(i+(j%3))%N][1] -
					 x[(i+j-1)%N][1] * x[(i+(j%3))%N][0];
		}
#if STRICTLY_CONVEX
		if(cdir == 0)
			return 0;
#endif
		if(dir == 0){
			dir = cdir;
		} else {
			if(cdir != 0 && ((cdir < 0) != (dir < 0)))
				return 0;
		}
	}
	return 42;
}
