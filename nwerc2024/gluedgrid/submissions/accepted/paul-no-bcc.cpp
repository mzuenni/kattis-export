#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;

struct dsu {
	int n;
	vector<int> p, h;

	dsu(int n): n(n), p(n), h(n) {
		iota(begin(p), end(p), 0);
	}
	
	int find(int x) {
		if (x == p[x]) return x;
		return p[x] = find(p[x]);
	}

	bool unite(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) return false;
		
		if (h[x] < h[y]) swap(x,y);
		if (h[x] == h[y]) h[x]++;
		p[y] = x;
		return true;
	}
};

bool solve() {
    int h, w;
    cin >> h >> w;

    vector<string> glue(h);
    for (string &s: glue) cin >> s;

    vector tile(h, vector<int>(w));
    for (auto &v: tile) for (int &x: v) cin >> x;

    if (h == 1 || w == 1) {
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (tile[i][j] != (i*w+j+1) % (h*w)) return false;
            }
        }
        return true;
    }

    vector dist(h, vector<int>(w, -1));
    queue<pair<int,int>> todo;
    dist[h-1][w-1] = 0;
    todo.emplace(h-1, w-1);
    while (!todo.empty()) {
        auto [i, j] = todo.front();
        todo.pop();
        for (int di = -1; di <= 1; di++) {
            for (int dj = -1; dj <= 1; dj++) {
                if (abs(di) + abs(dj) != 1) continue;
                int ni = i+di, nj = j+dj;
                if (ni < 0 || ni >= h || nj < 0 || nj >= w) continue;
                if (glue[ni][nj] == '#' || dist[ni][nj] != -1) continue;
                dist[ni][nj] = dist[i][j] + 1;
                todo.emplace(ni, nj);
            }
        }
    }

    auto is_block = [&](int i, int j) {
        for (int di = 0; di < 2; di++) {
            for (int dj = 0; dj < 2; dj++) {
                if (glue[i+di][j+dj] == '#') return false;
            }
        }
        return true;
    };

    dsu D((h-1)*(w-1));
    auto id = [&](int i, int j) { return i*(w-1) + j; };
    for (int i = 0; i < h-1; i++) {
        for (int j = 0; j < w-1; j++) {
            if (is_block(i, j)) {
                if (i < h-2 && is_block(i+1, j)) D.unite(id(i, j), id(i+1, j));
                if (j < w-2 && is_block(i, j+1)) D.unite(id(i, j), id(i, j+1));
            }
        }
    }

    pair<int,int> none(-1, -1);
    vector<pair<int,int>> keystone((h-1)*(w-1), none);
    for (int i = 0; i < h-1; i++) {
        for (int j = 0; j < w-1; j++) {
            if (is_block(i, j)) {
                for (int di = 0; di < 2; di++) {
                    for (int dj = 0; dj < 2; dj++) {
                        int c = D.find(id(i, j));
                        auto [bi, bj] = keystone[c];
                        if (bi == -1 || dist[i+di][j+dj] < dist[bi][bj]) {
                            keystone[c] = make_pair(i+di, j+dj);
                        }
                    }
                }
            }
        }
    }

    vector comp(h, vector<int>(w));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            comp[i][j] = i*w + j;
        }
    }

    for (int i = 0; i < h-1; i++) {
        for (int j = 0; j < w-1; j++) {
            if (is_block(i, j)) {
                for (int di = 0; di < 2; di++) {
                    for (int dj = 0; dj < 2; dj++) {
                        int c = D.find(id(i, j));
                        if (make_pair(i+di, j+dj) != keystone[c]) {
                            comp[i+di][j+dj] = h*w + c;
                        }
                    }
                }
            }
        }
    }

    vector<pair<int,int>> where(h*w);
    vector<vector<pair<int,int>>> comps(2*h*w);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            where[tile[i][j]] = make_pair(i, j);
            comps[comp[i][j]].emplace_back(i, j);
        }
    }

    vector mark(h, vector<int>(w));
    for (int c = 0; c < 2*h*w; c++) {
        int swaps = size(comps[c]);
        for (auto [i, j]: comps[c]) {
            if (!mark[i][j]) {
                swaps--;
                while (!mark[i][j]) {
                    mark[i][j] = 1;
                    tie(i, j) = where[(i*w+j+1) % (h*w)];
                    if (comp[i][j] != c) return false;
                }
            }
        }
        if (swaps % 2 != 0) return false;
    }
    return true;
}

int main() {
    cout << (solve() ? "possible" : "impossible") << '\n';
}

