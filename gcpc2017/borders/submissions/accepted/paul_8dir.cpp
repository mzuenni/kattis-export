#include <bits/stdc++.h>
using namespace std;

#define left lll
#define right rrr
#define FOR(i,a,b) for (int i = (a); i < (b); i++)

enum direction { up, upleft, left, downleft, down, downright, right, upright };
const int dx[] = {-1,-1,0,1,1,1,0,-1}, dy[] = {0,-1,-1,-1,0,1,1,1};

vector<pair<int,int>> res[2];
void add_point(int x, int y, direction d) {
	int dir = static_cast<int>(d);
	res[0].emplace_back(x+dx[dir], y+dy[dir]);
	res[1].emplace_back(x-dx[dir], y-dy[dir]);
}

int main() {
	int n; cin >> n;
	
	vector<array<int,3>> p(n);
	FOR(i,0,n) FOR(j,0,3) cin >> p[i][j];
	sort(begin(p),end(p));
	
	vector<int> x(n), y(n), c(n);
	FOR(i,0,n) x[i] = p[i][0], y[i] = p[i][1], c[i] = p[i][2];

	int xmin = INT_MAX, ymin = INT_MAX;
	int xmax = INT_MIN, ymax = INT_MIN;
	FOR(i,0,n) {
		x[i] *= 10, y[i] *= 10;
		xmin = min(xmin,x[i]), ymin = min(ymin,y[i]); 
		xmax = max(xmax,x[i]), ymax = max(ymax,y[i]); 
	}
	for (int i = 0; i < n; ) {
		int j = i;
		while (j < n && x[j] == x[i]) j++;
		
		if (i > 0) {
			add_point(x[i-1]+5, ymin-2, down);
			add_point(x[i-1]+5, ymin-4, downright);
			add_point(x[i], ymin-4, upright);
			add_point(x[i], ymin-2, up);
		}

		FOR(k,i,j) add_point(x[k] + 2*(c[k]-2), y[k], up);
		
		add_point(x[i], ymax+2, up);
		add_point(x[i], ymax+4, upright);
		add_point(x[i]+5, ymax+4, downright);
		add_point(x[i]+5, ymax+2, down);
		i = j;
	}
	add_point(xmax+5, ymin-7, downleft);
	add_point(xmin, ymin-7, upleft);
	add_point(xmin, ymin-2, up);

	FOR(i,0,2) {
		cout << res[i].size() << endl;
		for (auto p: res[i])
			cout << fixed << setprecision(1)
			     << p.first/10.0 << " "
				 << p.second/10.0 << endl;
	}
}
