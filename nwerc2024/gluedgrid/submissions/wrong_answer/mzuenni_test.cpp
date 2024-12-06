#include <vector>
#include <iostream>
#include <ostream>
#include <algorithm>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

ll h, w;
vector<vector<ll>> adj;

void addEdge(ll a, ll b) {
	adj[a].push_back(b);
	adj[b].push_back(a);
}

ll id(ll x, ll y) {return y * w + x;}
pair<ll, ll> rev(ll i) {return {i % w, i / w};}

vector<int> num;
int counter;
vector<pair<int, int>> st;
vector<vector<pair<int, int>>> bcc;

int dfs(int v, int from = -1) {
	int me = num[v] = ++counter, top = me;
	for (int to : adj[v]) {
		if (to == from) continue;
		if (num[to]) {
			top = min(top, num[to]);
			if (num[to] < me) st.push_back({v, to});
		} else {
			int si = sz(st);
			int up = dfs(to, v);
			top = min(top, up);
			if (up > me) {
				bcc.emplace_back();
				bcc.back().push_back({v, to});
			}
			if (up <= me) st.push_back({v, to});
			if (up == me) {
				bcc.emplace_back(si + all(st));
				st.resize(si);
	}}}
	return top;
}

void find(int root) {
	counter = 0;
	num.assign(sz(adj), 0);
	st.clear();
	bcc.clear();
	dfs(root);
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> h >> w;
	vector<vector<bool>> ok(h, vector<bool>(w));
	adj.assign(h * w, {});
	for (ll y = 0; y < h; y++) {
		for (ll x = 0; x < w; x++) {
			char c;
			cin >> c;
			ok[y][x] = c == '.';
			if (ok[y][x] && x > 0 && ok[y][x - 1]) addEdge(id(x, y), id(x - 1, y));
			if (ok[y][x] && y > 0 && ok[y - 1][x]) addEdge(id(x, y), id(x, y - 1));
		}
	}
	vector<ll> in(w*h);
	vector<ll> pos(h*w);
	for (ll i = 0; i < w * h; i++) {
		cin >> in[i];
		in[i]--;
		if (in[i] < 0) in[i] += w*h;
		pos[in[i]] = i;
	}

	find(id(w - 1, h - 1));
	//reverse(all(bcc));
	bool res = true;
	vector<bool> seen(h * w);
	for (auto& v : bcc) {
		vector<ll> positions;
		for (auto [a, b] : v) {
			if (!seen[a]) positions.push_back(a);
			if (!seen[b]) positions.push_back(b);
		}
		sort(all(positions));
		positions.erase(unique(all(positions)), positions.end());

		vector<ll> values = positions; //expected values
		for (ll& p : values) p = in[p];

		sort(all(values));
		if (positions != values) {
			res = false;
			break;
		}

		ll cycles = 0;
		for (ll p : positions) {
			if (seen[p]) continue;
			cycles++;
			while (!seen[p]) {
				seen[p] = true;
				p = in[p];
			}
		}

		if (abs(cycles - sz(positions)) % 2 != 0) {
			res = false;
			break;
		}
	}

	//this stuff is actually guaranteed:
	seen.back() = true;
	for (ll i = 0; i < w * h; i++) {
		if (seen[i]) continue;
		res &= in[i] == i;
	}

	cout << (res ? "" : "im") << "possible" << endl;
}
