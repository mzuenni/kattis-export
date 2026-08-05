#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;
float a, before, sLow = 2, sHigh = 1000, sMid, removed, p[3][2];
long long N, c[100][2];

float rem(int cur) {
	for (int i = 0; i < 2; i++) {
		p[0][i] = c[cur][i];
		p[1][i] = p[0][i] + (c[(cur+1)%N][i] - p[0][i]) / sMid;
		p[2][i] = p[0][i] + (c[(cur+N-1)%N][i] - p[0][i]) / sMid;
	}
	return fabsl((p[1][0]-p[0][0]) * (p[2][1]-p[0][1]) - (p[2][0]-p[0][0])*(p[1][1]-p[0][1])) / 2.0;
}

int main() {
	cin >> a >> N;
	for (int i = 0; i < N; i++) cin >> c[i][0] >> c[i][1];
	for (int i = 1; i <= N; i++) before += (c[i-1][0]*c[i%N][1] - c[i%N][0]*c[i-1][1]);
	before = fabsl(before)/2.;
	for (int i = 0; i < 100; i++) {
		sMid = (sLow + sHigh) / 2.;
		removed = 0;
		for (int j = 0; j < N; j++) removed += rem(j);
		if ((before - removed) / before < a) sLow = sMid;
		else sHigh = sMid;
	}
	cout << setprecision(20) << sMid << endl;
	return 0;
}
