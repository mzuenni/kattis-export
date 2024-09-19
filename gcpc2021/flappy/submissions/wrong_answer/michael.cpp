#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;
using pt = complex<ll>;

// Kreuzprodukt, 0, falls kollinear.
ll cross(pt a, pt b) {return imag(conj(a) * b);}
ll cross(pt p, pt a, pt b) {return cross(a - p, b - p);}

pt readPt() {
	ll x, y;
	cin >> x >> y;
	return {x, y};
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<pt> path = {readPt()};
	pt e = readPt();
	ll n;
	cin >> n;

	
	vector<pt> todoL, todoU;
	ll lower = 0;
	ll upper = 0;

	auto update = [&](ll i){
		if (cross(path.back(), todoL[lower], todoU[i]) < 0) {
			path.push_back(todoL[lower]);
			lower++;
			upper = lower;
			return true;
		} else if (cross(path.back(), todoU[upper], todoL[i]) > 0) {
			path.push_back(todoU[upper]);
			upper++;
			lower = upper;
			return true;
		} else {
			if (cross(path.back(), todoL[lower], todoL[i]) >= 0) lower = i;
			if (cross(path.back(), todoU[upper], todoU[i]) <= 0) upper = i;
			return false;
		}
	};

	auto add = [&](pt l, pt u) {
		todoL.push_back(l);
		todoU.push_back(u);
		if (sz(todoL) > 1) {
			update(sz(todoL)-1);
		}
	};

	for (ll i = 0; i < n; i++) {
		ll x, y1, y2;
		cin >> x >> y1 >> y2;
		add({x, y1}, {x, y2});
	}
	add(e, e);
	path.push_back(e);
	for (auto e : path) {
		cout << e.real() << " " << e.imag() << endl;
	}

}
