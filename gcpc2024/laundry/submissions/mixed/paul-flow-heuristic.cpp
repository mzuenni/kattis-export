// @EXPECTED_RESULTS@: WRONG_ANSWER, TIME_LIMIT_EXCEEDED
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const i64 oo = 0x3f3f3f3f3f3f3f3f;

struct flow_network {
	struct edge { int to; i64 cap; };
	
	i64 n, s, t;
	vector<bool> mark;
	vector<int> ptr, dist;
	vector<vector<int>> adj;
	vector<edge> e;

	flow_network(int n, int s, int t): n(n), s(s), t(t), adj(n) { }

	void add_edge(int a, int b, i64 c) {
		adj[a].push_back(e.size());
		e.push_back({b,c});
		adj[b].push_back(e.size());
		e.push_back({a,0});
	}
	
	bool bfs() {
		dist.assign(n, n+1);
		queue<int> q;
		dist[s] = 0, q.push(s);
		while (!q.empty()) {
			int i = q.front(); q.pop();
			for (int j: adj[i]) if (e[j].cap) {
				if (dist[e[j].to] <= n) continue;
				dist[e[j].to] = dist[i]+1, q.push(e[j].to);
			}
		}
		return dist[t] <= n;
	}

	i64 dfs(int i, i64 cap) {
		if (!cap || i == t) return cap;
		for (; ptr[i] < int(adj[i].size()); ptr[i]++) {
			int j = adj[i][ptr[i]];
			if (dist[e[j].to] != dist[i]+1) continue;
			if (i64 c = dfs(e[j].to, min(cap,e[j].cap))) {
				e[j].cap -= c, e[j^1].cap += c;
				return c;
			}
		}
		return 0;
	}

	i64 max_flow() {
		i64 flow = 0;
		while (bfs()) {
			ptr.assign(n,0);
			while (i64 c = dfs(s,oo)) flow += c;
		}
		return flow;
	}
};

void solve() {
    i64 cap, a, b, c, ab, bc, ac, abc;
    cin >> cap >> a >> b >> c >> ab >> bc >> ac >> abc;

    auto f = [&](int x) { return (x+cap-1) / cap; };

    i64 base = f(a) + f(b) + f(c);
    i64 lo = base - 1;
    i64 hi = lo + 1 + f(ab) + f(bc) + f(ac) + f(abc);

    auto check = [&](i64 md) {
        for (int k = 0; k < 10; k++) {
            int x = rand() % (md-base+2), y = x;
            while (y == x) y = rand() % (md-base+2);
            if (x > y) swap(x, y);
            i64 ea = x, eb = y-1-x, ec = md-base+1-y;

            flow_network F(9, 0, 8);
            F.add_edge(0, 1, a);
            F.add_edge(0, 2, b);
            F.add_edge(0, 3, ab);
            F.add_edge(0, 4, c);
            F.add_edge(0, 5, ac);
            F.add_edge(0, 6, bc);
            F.add_edge(0, 7, abc);
            F.add_edge(3, 1, oo);
            F.add_edge(3, 2, oo);
            F.add_edge(5, 1, oo);
            F.add_edge(5, 4, oo);
            F.add_edge(6, 2, oo);
            F.add_edge(6, 4, oo);
            F.add_edge(7, 3, oo);
            F.add_edge(7, 5, oo);
            F.add_edge(7, 6, oo);
            F.add_edge(1, 8, cap * (f(a)+ea));
            F.add_edge(2, 8, cap * (f(b)+eb));
            F.add_edge(4, 8, cap * (f(c)+ec));

            if (F.max_flow() == a + b + c + ab + bc + ac + abc) return true;
        }
        return false;
    };

    while (hi-lo > 1) {
        i64 md = (lo+hi) / 2;
        (check(md) ? hi : lo) = md;
    }
    cout << hi << '\n';
}

int main() {
    srand(123);
    int tc; cin >> tc;
    while (tc--) solve();
}
