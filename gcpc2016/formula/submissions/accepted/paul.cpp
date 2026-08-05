#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)

int main() {
	double a[3][2];
	FOR(i,0,3) FOR(j,0,2) cin >> a[i][j];
	double rm; cin >> rm;
	
	double b[3];
	FOR(i,0,3) {
		double dx = a[i][0] - a[(i+1)%3][0];
		double dy = a[i][1] - a[(i+1)%3][1];
		b[i] = sqrt(dx*dx + dy*dy);
	}
	double s = (b[0]+b[1]+b[2])/2;
	double A = sqrt(s*(s-b[0])*(s-b[1])*(s-b[2]));
	double r = A/s;
	
	cout << fixed << setprecision(12) << 100*(r-rm)/rm << endl;
}

