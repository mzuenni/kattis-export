#include <vector>
#include <set>
#include <iostream>
#include <ostream>
#include <algorithm>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

ll h, w;
vector<set<ll>> adj;

void addEdge(ll a, ll b) {
	if (a < 0 || b < 0) return;
	adj[a].insert(b);
	adj[b].insert(a);
}

void removeEdge(ll a, ll b) {
	if (a < 0 || b < 0) return;
	adj[a].erase(b);
	adj[b].erase(a);
}

ll id(ll x, ll y) {
	if (x < 0 || x >= w) return -1;
	if (y < 0 || y >= h) return -1;
	return y * w + x;
}
pair<ll, ll> rev(ll i) {return {i % w, i / w};}

vector<int> num;
int counter = 0;

void dfs(int v, int from = -1) {
	num[v] = ++counter;
	for (int to : adj[v]) {
		if (!num[to]) dfs(to, v);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> h >> w;
	vector<vector<bool>> ok(h, vector<bool>(w));
	auto free = [&](int x, int y)->bool{
		if (x < 0 || x >= w) return false;
		if (y < 0 || y >= h) return false;
		return ok[y][x];
	};

	adj.assign(h * w, {});
	for (ll y = 0; y < h; y++) {
		for (ll x = 0; x < w; x++) {
			char c;
			cin >> c;
			ok[y][x] = c == '.';
			if (free(x, y) && free(x - 1, y)) addEdge(id(x, y), id(x - 1, y));
			if (free(x, y) && free(x, y - 1)) addEdge(id(x, y), id(x, y - 1));
		}
	}

	num.assign(w*h, 0);
	dfs(id(w - 1, h - 1));

	vector<ll> in(w*h);
	vector<ll> pos(h*w);
	for (ll i = 0; i < w * h; i++) {
		cin >> in[i];
		in[i]--;
		if (in[i] < 0) in[i] += w*h;
		pos[in[i]] = i;
	}

	bool res = true;
	auto check = [&](ll i){
		if (i + 1 == w*h) return;
		if (in[i] != i) res = false;
	};
	for (ll y = 0; y < h; y++) {
		for (ll x = 0; x < w; x++) {
			if (!free(x, y)) continue;
			//bridges
			if (free(x, y) &&
				free(x - 1, y) &&
				(!free(x - 1, y - 1) || !free(x, y - 1)) &&
				(!free(x - 1, y + 1) || !free(x, y + 1))) {
				removeEdge(id(x, y), id(x - 1, y));//<
				if (num[id(x, y)] > num[id(x - 1, y)]) check(id(x, y));
				else check(id(x - 1, y));
			}
			if (free(x, y) &&
				free(x, y - 1) &&
				(!free(x - 1, y - 1) || !free(x - 1, y)) &&
				(!free(x + 1, y - 1) || !free(x + 1, y))) {
				removeEdge(id(x, y), id(x, y - 1));//^
				if (num[id(x, y)] > num[id(x, y - 1)]) check(id(x, y));
				else check(id(x, y - 1));
			}

			// articulation points
			if (!free(x - 1, y - 1) && !free(x + 1, y + 1)) {
				if (free(x, y + 1) &&
					free(x - 1, y) &&
					num[id(x, y)] < num[id(x, y + 1)] &&
					num[id(x, y)] < num[id(x - 1, y)]) {
					removeEdge(id(x, y), id(x, y + 1));
					removeEdge(id(x, y), id(x - 1, y));
				}
				if (free(x, y - 1) &&
					free(x + 1, y) &&
					num[id(x, y)] < num[id(x, y - 1)] &&
					num[id(x, y)] < num[id(x + 1, y)]) {
					removeEdge(id(x, y), id(x, y - 1));
					removeEdge(id(x, y), id(x + 1, y));
				}
			}
			if (!free(x - 1, y + 1) && !free(x + 1, y - 1)) {
				if (free(x, y - 1) &&
					free(x - 1, y) &&
					num[id(x, y)] < num[id(x, y - 1)] &&
					num[id(x, y)] < num[id(x - 1, y)]) {
					removeEdge(id(x, y), id(x, y - 1));
					removeEdge(id(x, y), id(x - 1, y));
				}
				if (free(x, y + 1) &&
					free(x + 1, y) &&
					num[id(x, y)] < num[id(x, y + 1)] &&
					num[id(x, y)] < num[id(x + 1, y)]) {
					removeEdge(id(x, y), id(x, y + 1));
					removeEdge(id(x, y), id(x + 1, y));
				}
			}
		}
	}

	vector<bool> seenDFS(h * w), seenParity(h * w);
	for (ll i = 0; i < w*h; i++) {
		if (seenDFS[i]) continue;
		vector<ll> positions;
		auto dfs = [&](auto&& self, ll x)->void{
			seenDFS[x] = true;
			positions.push_back(x);
			for (ll y : adj[x]) {
				if (seenDFS[y]) continue;
				self(self, y);
			}
		};
		dfs(dfs, i);
		sort(all(positions));

		vector<ll> values = positions; //expected values
		for (ll& p : values) p = in[p];

		sort(all(values));
		if (positions != values) {
			res = false;
			break;
		}

		ll cycles = 0;
		for (ll p : positions) {
			if (seenParity[p]) continue;
			cycles++;
			while (!seenParity[p]) {
				seenParity[p] = true;
				p = in[p];
			}
		}

		if (abs(cycles - sz(positions)) % 2 != 0) {
			res = false;
			break;
		}
	}

	cout << (res ? "" : "im") << "possible" << endl;
}
