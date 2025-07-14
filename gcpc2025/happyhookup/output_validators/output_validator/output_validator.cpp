#include "validation.h"
using namespace std;

int n, m, a, b;
vector<vector<int>> g;

void dfs(int v, vector<bool> &vis) {
	assert (!vis[v]);
	vis[v] = true;
	for (int u: g[v]) if (!vis[u]) {
		dfs(u, vis);
	}
}

int main(int argc, char *argv[]) {
    ifstream in(argv[1]);
    ifstream ans(argv[2]);
    OutputValidator v(argc, argv);

	string jury_answer;
	ans >> jury_answer;

	auto answer = v.test_strings({"yes", "no"}, "answer");
	v.newline();
	v.check(answer == jury_answer, "Expected '", jury_answer, "', but got '", answer, "'.");

	if (answer == "yes") {
		in >> n >> m;
		g.resize(n);
		for (int i = 0; i < m; i++) {
			int x, y;
			in >> x >> y;
			x--; y--;
			g[x].push_back(y);
		}
		in >> a >> b;
		a--; b--;

		vector<bool> vis1(n), vis2(n);
		dfs(a, vis1);
		dfs(b, vis2);

		auto val = v.read_integer("meeting_point", 1, n);
		v.newline();

		v.check(vis1[val-1], "First person can not reach destination.");
		v.check(vis2[val-1], "Second person can not reach destination.");
	}
}
