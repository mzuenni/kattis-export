#include <bits/stdc++.h>
using namespace std;

struct point {
	double x, y;
	int c;

	void rotate(double alpha) {
		double _x = x, _y = y, s = cos(alpha), t = sin(alpha);
		x = s*_x - t*_y, y = t*_x + s*_y;
	}
};

int main() {
	random_device rd;
	double alpha = uniform_real_distribution<double>(0.0,2*M_PI)(rd);
	
	int n; cin >> n;
	
	vector<point> p(n);
	for (point &a: p) cin >> a.x >> a.y >> a.c, a.rotate(alpha);
	sort(begin(p),end(p),[&](const point &a, const point &b) { return a.x < b.x; });
	
	double X = 1000 * sqrt(2);
	
	vector<point> q1, q2;
	q1.push_back({-X,-X,0});
	q2.push_back({-X, X,0});
	
	for (int i = 0; i < n; i++) {
		double offset1, offset2;
		if (p[i].c == 1) offset1 = -1.0, offset2 = -0.5;
		if (p[i].c == 2) offset1 = -0.5, offset2 =  0.5;
		if (p[i].c == 3) offset1 =  0.5, offset2 =  1.0;
			
		q1.push_back({p[i].x, p[i].y+offset1, 0});
		q2.push_back({p[i].x, p[i].y+offset2, 0});
	}
	
	q1.push_back({X,-X,0});
	q2.push_back({X, X,0});
	
	cout << fixed << setprecision(4);
	cout << q1.size() << endl;
	for (point a: q1) a.rotate(-alpha), cout << a.x << " " << a.y << endl;
	cout << q2.size() << endl;
	for (point a: q2) a.rotate(-alpha), cout << a.x << " " << a.y << endl;
}
