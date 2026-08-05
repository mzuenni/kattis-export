//Author: Stefan Toman

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

double distance(vector<double> a, vector<double> b) {
	double r = 0;
	for(int i = 0; i < 3; i++) r += (a[i] - b[i])*(a[i] - b[i]);
	return sqrt(r);
}

int main() {
	int n, r = 0;
	double d;
	cin >> n >> d;
	vector< vector<double> > p(2, vector<double>(3));
	for(int i = 1; i >= 0; i--) for(int j = 0; j < 3; j++) cin >> p[i][j];
	for(int i = 0; i < n; i++) {
		vector<double> s(3), t(3), bob(3, 0.0);
		for(int j = 0; j < 3; j++) cin >> s[j];
		for(int j = 0; j < 3; j++) cin >> t[j];
		double sp=sqrt(t[0]*t[0]+t[1]*t[1]+t[2]*t[2]);
		for(int j = 0; j < 3; j++) t[j]/=sp;
		double lt = distance(bob, t);
		for(int j = 0; j < 3; j++) t[j] /= lt;
		double b0 = p[1][0]*p[0][1] - p[1][1]*p[0][0];
		double b1 = p[1][0]*p[0][2] - p[1][2]*p[0][0];
		double ts0 = (s[0]*p[0][1] - s[1]*p[0][0]) * b1;
		double ts1 = (s[0]*p[0][2] - s[2]*p[0][0]) * b0;
		double tl0 = (t[0]*p[0][1] - t[1]*p[0][0]) * b1;
		double tl1 = (t[0]*p[0][2] - t[2]*p[0][0]) * b0;
		double l = ts0 == ts1 ? 0 : (ts0 - ts1)/(tl0 - tl1);
		vector<double> intersection(3);
		for(int j = 0; j < 3; j++)  intersection[j] = s[j] - l*t[j];
		if(abs(distance(intersection, bob) - d) <= 0.05 && abs(l/sp - d) <= 0.05) r++;
	}
	cout << r << endl;
	return 0;
}
