#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)

long long x[128][2];
long double p;
int N;
double get_ratio(double s){
	long long A = 0, PARTS = 0;
	FOR (i, 1, N + 1)
		A += x[i-1][0] * x[i%N][1] - x[i%N][0] * x[i-1][1];
	FOR(i,0,N)
		FOR(j,1,4)
			PARTS += x[(i+j-1)%N][0] * x[(i+(j%3))%N][1] -
					 x[(i+j-1)%N][1] * x[(i+(j%3))%N][0];
	return 1.0 - PARTS/ (s * s * A);
}
int main() {
	cin >> p >> N;
	FOR(i,0,N)FOR(j,0,2)cin >> x[i][j];
	double result = 2.0;
	while(get_ratio(result) < p)result += 5e-5;
	printf("%.5lf\n", result);
	return 0;
}
