#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;
using pt = complex<ll>;

ll cross(pt a, pt b) {return imag(conj(a) * b);}
ll cross(pt p, pt a, pt b) {return cross(a - p, b - p);}
ll sign(ll x) {return (0ll < x) - (x < 0ll);}

// this is the upper half
// ___________0..........
//
bool upper(pt p) {
	if (imag(p) < 0) return false;
	if (imag(p) > 0) return true;
	return real(p) < 0;
}

struct event {
	pt pos;
	bool polygon_above;
	ll diff;
	bool operator<(const event& o) const {
		if (cross(pos, o.pos) != 0) return cross(pos, o.pos) > 0; //cyclic compare
		if (polygon_above != o.polygon_above) return polygon_above < o.polygon_above;//polygon_above false comes first;
		return diff > o.diff;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n;
	cin >> n;
	vector<pt> in;
	for (ll i = 0; i < n; i++) {
		ll x, y;
		cin >> x >> y;
		in.push_back({2*x, 2*y});
	}
	pt center = (in[0] + in[n / 2]) / pt(2,0);
	for (auto& p : in) p -= center;
	in.push_back(in[0]);
	in.push_back(in[1]);

	//find initial active count
	ll active = 0;
	for (ll i = 1; i <= n; i++) {
		pt a = in[i - 1];
		pt b = in[i];
		if (upper(a) == upper(b)) continue;
		if (!upper(b)) swap(a, b);
		assert(upper(b));
		if (cross(b, a) < 0) active++;
	}

	//find corners where active count changes
	vector<event> events;
	for (ll i = 1; i <= n; i++) {
		pt a = in[i - 1];
		pt b = in[i];
		pt c = in[i + 1];
		if (!upper(b)) continue;
		//b is upper half
		ll sa = sign(cross(b, a));
		ll sc = sign(cross(b, c));
		ll diff = 0;
		if (sa == 0) sa = sc;
		else diff++;
		if (sc == 0) sc = sa;
		else diff++;
		if (sa != sc) continue;
		if (sa < 0) diff = -diff;
		bool above = sign(cross(b, a, c)) * sa < 0;
		events.push_back({b, above, diff});
	}
	sort(all(events));

	auto check = [&](pt pos){
		assert(active <= 1);
		pos += center;
		//cout << "possible" << endl;
		cout << real(center) << "/2 ";
		cout << imag(center) << "/2 ";
		cout << real(pos) << "/2 ";
		cout << imag(pos) << "/2" << endl;
		exit(0);
	};

	if (events.empty()) {
		check({1, 0});
	} else {
		{
			auto [pos, above, type] = events[0];
			events.push_back({-pos, above, type});
		}
		for (ll i = 0; i + 1 < sz(events); i++) {
			auto [pos, above, type] = events[i];
			active += type;
			if (active <= 1) {
				if (above) check((pos + events[i+1].pos)/pt(2, 0));//rotate by epsilon...
				else check(pos);
			}
		}
	}

	cout << "impossible" << endl;
}
