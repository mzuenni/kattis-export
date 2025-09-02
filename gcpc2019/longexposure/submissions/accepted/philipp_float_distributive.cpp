#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
#define xx first
#define yy second

const ll MAXCIRCLE = 50'000;

int main() {
	ll n;
	cin >> n;
	vector<pair<pll,pll>> rects;
	while(n--) {
		ll x, y, w, h;
		cin >> x >> y >> w >> h;
		vector<ll> xs, ys;
		xs.push_back(x), ys.push_back(y);
		if(x < 0 && x+w > 0) {
			xs.push_back(0);
		}
		if(y < 0 && y+h > 0) {
			ys.push_back(0);
		}
		xs.push_back(x+w), ys.push_back(y+h);
		for(ll i = 1; i < xs.size(); i++) {
			for(ll j = 1; j < ys.size(); j++) {
				rects.emplace_back(make_pair(xs[i-1], ys[j-1]), make_pair(xs[i], ys[j]));
			}
		}
	}
	// each rect is now in exactly one quadrant

	map<pll, multiset<pair<ll,bool>>> intervals;
	for(pair<pll,pll> rect : rects) {
		ll xfac = rect.xx.xx < 0 ? -1 : 1;
		ll yfac = rect.xx.yy < 0 ? -1 : 1;
		if(xfac == -1) {
			swap(rect.xx.xx, rect.yy.xx);
			rect.xx.xx *= -1, rect.yy.xx *= -1;
		}
		if(yfac == -1) {
			swap(rect.xx.yy, rect.yy.yy);
			rect.xx.yy *= -1, rect.yy.yy *= -1;
		}
		pll bl = {rect.xx.xx, rect.yy.yy-1};
		pll tr = {rect.xx.xx+1, rect.yy.yy};
		while(bl != tr) {
			pll diag;
			if(bl.yy > bl.xx) {
				diag.xx = 1;
			} else {
				diag.xx = bl.xx - bl.yy + 1;
			}
			diag.xx *= xfac;
			if(bl.xx > bl.yy) {
				diag.yy = 1;
			} else {
				diag.yy = bl.yy - bl.xx + 1;
			}
			diag.yy *= yfac;
			intervals[diag].emplace(bl.xx*bl.xx + bl.yy*bl.yy, false);
			intervals[diag].emplace(tr.xx*tr.xx + tr.yy*tr.yy, true);
			if(bl.yy > rect.xx.yy) {
				bl.yy--;
			} else {
				bl.xx++;
			}
			if(tr.xx < rect.yy.xx) {
				tr.xx++;
			} else {
				tr.yy--;
			}
		}
	}

	multiset<pair<ll,bool>> covered;
	for(auto& ps : intervals) {
		ll open = 0;
		for(pair<ll,bool> corner : ps.yy) {
			if(corner.yy) {
				open--;
				if(!open) {
					covered.emplace(corner.xx, true);
				}
			} else {
				if(!open) {
					covered.emplace(corner.xx, false);
				}
				open++;
			}
		}
	}

	auto it = covered.begin();
	long long black = 0, grey = 0;
	ll painted = 0, oldr2 = 0;
	for(ll radius = 1, req = 4; (radius < MAXCIRCLE || painted) && it != covered.end(); radius++, req += 8) {
		ll r2 = radius*radius;
		while(it != covered.end() && it->xx < r2) {
			long long area = it->xx - oldr2;
			if(it->yy) {
				if(painted == req) {
					black += area;
					oldr2 = it->xx;
				}
				painted--;
				if(painted == 0) {
					grey += area;
					oldr2 = it->xx;
				}
			} else {
				if(painted == 0) {
					// white surface ends
					oldr2 = it->xx;
				}
				painted++;
				if(painted == req) {
					grey += area;
					oldr2 = it->xx;
				}
			}
			it++;
		}
		if(painted) {
			long long area = r2 - oldr2;
			if(painted == req) {
				black += area;
			} else {
				grey += area;
			}
		}
		oldr2 = r2;
	}

	while(it != covered.end()) {
		if(it->yy) {
			painted--;
			if(!painted) {
				grey += it->xx - oldr2;
			}
		} else {
			if(!painted) {
				oldr2 = it->xx;
			}
			painted++;
		}
		it++;
	}
	float gres = grey * M_PI;
	float bres = black * M_PI;

	cout.precision(10);
	cout << fixed << bres << endl;
	cout << fixed << gres << endl;
}
