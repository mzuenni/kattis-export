#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORD(i,a,b) for (int i = (b)-1; i >= (a); i--)

struct rectangle {
	int xmin, xmax, ymin, ymax;
};

void compress(vector<int> &i2x, map<int,int> &x2i) {
	sort(begin(i2x), end(i2x));
	i2x.erase(unique(begin(i2x), end(i2x)), end(i2x));
	for (int i = 0; i < (int)i2x.size(); i++) x2i[i2x[i]] = i;
}

const int N = 2010;
int a[N][N];

int main() {
	int n; cin >> n;
	
	// collect and compress all coordinates:
	vector<int> i2x = {0}, j2y = {0};
	map<int,int> x2i, y2j;
	
	vector<rectangle> rects(n);
	for (auto &r: rects) {
		int xmin, ymin, w, h;
		cin >> xmin >> ymin >> w >> h;
		r = {xmin, xmin+w, ymin, ymin+h};
		i2x.push_back(r.xmin);
		i2x.push_back(r.xmax);
		j2y.push_back(r.ymin);
		j2y.push_back(r.ymax);
	}
	
	compress(i2x,x2i), compress(j2y,y2j);
	
	// use prefix sums to find outline of figure
	for (auto &r: rects) {
		int imin = x2i[r.xmin], imax = x2i[r.xmax];
		int jmin = y2j[r.ymin], jmax = y2j[r.ymax];
		
		a[imin][jmin]++, a[imax][jmax]++;
		a[imin][jmax]--, a[imax][jmin]--;
	}
	
	FORD(i,0,N-1) FOR(j,0,N) a[i][j] += a[i+1][j];
	FOR(i,0,N) FORD(j,0,N-1) a[i][j] += a[i][j+1];
	FOR(i,0,N) FOR(j,0,N) a[i][j] = !!a[i][j];
	
	// Every edge of the figure gives an interval of radii
	// for which the final color must be gray, the union
	// of these intervals is exactly the gray area.
	
	// find the union of intervals with a line sweep
	vector<pair<double,int>> events;
	FOR(i,0,N-1) FOR(j,0,N) if (a[i][j] != a[i+1][j]) {
		int x = i2x[i], y1 = j2y[j-1], y2 = j2y[j];
		double r1 = hypot(x,y1), r2 = hypot(x,y2);
		if (r1 > r2) swap(r1,r2);
		events.emplace_back(r1,1);
		events.emplace_back(r2,-1);
	}

	FOR(i,0,N) FOR(j,0,N-1) if (a[i][j] != a[i][j+1]) {
		int x1 = i2x[i-1], x2 = i2x[i], y = j2y[j];
		double r1 = hypot(x1,y), r2 = hypot(x2,y);
		if (r1 > r2) swap(r1,r2);
		events.emplace_back(r1,1);
		events.emplace_back(r2,-1);
	}
	
	sort(begin(events), end(events));
	
	// to check whether the remaining parts are white or
	// black, it suffices to sample at a single point
	auto is_black = [&](double r) {
		int i = lower_bound(begin(i2x),end(i2x),r)-begin(i2x);
		return a[i][y2j[0]];
	};

	int depth = 0;
	double rprev = 0;
	double black = 0, gray = 0;
	for (auto ev: events) {
		double rcur = ev.first;
		double ring = M_PI * (rcur*rcur - rprev*rprev);
		if (depth > 0) gray += ring;
		else if (is_black((rprev+rcur)/2)) black += ring;
		rprev = rcur;
		depth += ev.second;
	}
	cout << fixed << setprecision(20) << black << endl << gray << endl;
}
