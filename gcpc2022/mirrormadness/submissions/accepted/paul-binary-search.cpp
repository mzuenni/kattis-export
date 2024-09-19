#include <bits/stdc++.h>
using namespace std;

int sgn(int x) { return (x > 0) - (x < 0); }

int main() {
	int n, m;
	cin >> n >> m;
	
	int xmin = 1e9, xmax = -1e9, ymin = 1e9, ymax = -1e9;
	vector<pair<int,int>> a(n);
	for (int i = 0; i < n; i++) {
		int u, v;;
		cin >> u >> v;
		int x = u+v, y = u-v;
		a[i] = {x,y};
		xmin = min(xmin, x), xmax = max(xmax, x);
		ymin = min(ymin, y), ymax = max(ymax, y);
	}

	vector<set<int>> x2y((xmax-xmin)/2), y2x((ymax-ymin)/2);
	map<pair<int,int>, char> mir;

	for (int i = 0; i < n; i++) {
		auto [x1,y1] = a[i];
		auto [x2,y2] = a[(i+1)%n];
		int dx = sgn(x2-x1), dy = sgn(y2-y1);
		char c = dx == dy ? '/' : '\\';
		for (; x1 != x2 && y1 != y2; x1 += 2*dx, y1 += 2*dy) {
			int x = (x1+dx-xmin)/2, y = (y1+dy-ymin)/2;
			x2y[x].insert(y), y2x[y].insert(x);
			mir[make_pair(x,y)] = c;
		}
	}

	int u, v;
	cin >> u >> v;
	int x = (u+v-xmin)/2, y = (u-v-ymin)/2;
	int dir = 0;

	while (m--) {
		int nx = x, ny = y;
		if (dir == 0) nx = *next(y2x[y].find(x));
		if (dir == 1) ny = *next(x2y[x].find(y));
		if (dir == 2) nx = *prev(y2x[y].find(x));
		if (dir == 3) ny = *prev(x2y[x].find(y));
		x = nx, y = ny;
		char c = mir[make_pair(nx,ny)];
		dir = c == '/' ? (dir^1) : (3-dir);
		
		int xx = xmin+2*x+1, yy = ymin+2*y+1;
		cout << (xx+yy)/2 << ' ' << (xx-yy)/2 << '\n';
	}
}
