#include <bits/stdc++.h>
using namespace std;

struct point { long long x, y; };
point rx(point p) { return {-p.x,p.y}; }
point ry(point p) { return {p.x,-p.y}; }

point solve(point a, long long r, point b, long long s) {
	if (r > s) return solve(b, s, a, r);
	if (a.x > b.x) return rx(solve(rx(a), r, rx(b), s));
	if (a.y > b.y) return ry(solve(ry(a), r, ry(b), s));
	
	long long dx = b.x-a.x;
	if (r < dx) return {a.x+r,a.y};
	return {b.x,a.y+r-dx};
}

int main() {
	point a, b;
	long long r, s;
	cin >> a.x >> a.y >> r >> b.x >> b.y >> s;
	
	long long dx = abs(b.x-a.x), dy = abs(b.y-a.y), gap = dx+dy-r-s;
	
	if (gap > 0 || gap%2 != 0) {
		cout << "impossible" << endl;
	} else {
		point c = solve(a,r,b,s);
		cout << c.x << " " << c.y << endl;
	}
}
