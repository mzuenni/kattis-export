#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct point { i64 x, y; };

point operator+(point a, point b) { return {a.x+b.x, a.y+b.y}; }
point operator-(point a, point b) { return {a.x-b.x, a.y-b.y}; }

i64 cross(point a, point b) { return a.x*b.y - a.y*b.x; }
i64 turn(point a, point b, point c) { return cross(b-a, c-a); }

ostream &operator<<(ostream &out, point p) {
	return out << "(" << p.x << "," << p.y << ")";
}

ostream &operator<<(ostream &out, deque<point> v) {
	for (point p: v) out << p << " ";
	return out << endl;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	point a, b;
	cin >> a.x >> a.y >> b.x >> b.y;

	deque<point> lower, upper, res;
	lower.push_back(a);
	upper.push_back(a);

	auto add_gate = [&](i64 x, i64 ymin, i64 ymax) {
		lower.push_front({x,ymin});
		upper.push_front({x,ymax});

		while (int(lower.size()) >= 3 && turn(lower[0], lower[1], lower[2]) <= 0) {
			lower.erase(begin(lower)+1);
		}
		while (int(upper.size()) >= 3 && turn(upper[0], upper[1], upper[2]) >= 0) {
			upper.erase(begin(upper)+1);
		}
		
		while (turn(lower.back(), end(lower)[-2], end(upper)[-2]) <= 0) {
			res.push_back(lower.back());
			if (int(lower.size()) >= 3) {
				lower.pop_back();
				upper.back() = lower.back();
			} else if (int(upper.size()) >= 3) {
				upper.pop_back();
				lower.back() = upper.back();
			} else {
				break;
			}
		}
	};

	int n; cin >> n;
	while (n--) {
		i64 x, ymin, ymax;
		cin >> x >> ymin >> ymax;
		add_gate(x, ymin, ymax);		
	}
	
	add_gate(b.x, b.y, b.y);
	
	res.push_back(b);

	for (auto p: res) cout << p.x << " " << p.y << '\n';
}
