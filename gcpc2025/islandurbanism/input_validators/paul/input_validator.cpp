#include "validation.h"
using namespace std;

const int NUM_VERTICES = 5000;
const int NUM_EDGES = 20'000;
const int NUM_TERMINALS_PER_VILLAGE = 7;

struct dsu { // Union/find data structure
	int n;
	vector<int> parent, size;

	dsu(int n): n(n), parent(n), size(n, 1) {
		iota(begin(parent), end(parent), 0);
	}
	
	int find(int x) {
		if (x == parent[x]) return x;
		return parent[x] = find(parent[x]);
	}

	bool unite(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) return false;
		
		if (size[x] < size[y]) swap(x,y);
        size[x] += size[y];
		parent[y] = x;
		return true;
	}
};

int main(int argc, char *argv[]) {
    InputValidator val(argc, argv);
    int n = val.read_integer("n", 3, NUM_VERTICES);
    val.space();
    int m = val.read_integer("m", n, NUM_EDGES);
    val.space();
    int v = val.read_integer("v", 3, n);
    val.space();
    int k = val.read_integer("k", 1, n);
    val.newline();

    auto u = val.read_integers("u", v, 1, n);
    val.check(accumulate(u.begin(), u.end(), 0LL) == n,
            "Village sizes must sum up to n");

    // Which village is a vertex in?
    auto where = [&](int a) {
        for (int i = 0; i < v; i++) {
            if (a <= u[i]) return i;
            a -= u[i];
        }
    };

    dsu D(n+1);
    set<pair<int,int>> edges, cross_edges;
    while (m--) {
        int a = val.read_integer("a", 1, n);
        val.space();
        int b = val.read_integer("b", 1, n);
        val.space();
        int c = val.read_integer("c", 1, 1e9);
        val.newline();

        val.check(a != b, "Self-loops are not allowed");
        if (a > b) swap(a, b);
        val.check(edges.emplace(a, b).second, "Multi-edges are not allowed");
        if (where(a) == where(b)) {
            D.unite(a, b);
        } else {
            cross_edges.emplace(a, b);
        }
    }

    for (int i = 0, a = 1; i < v; a += u[i++]) {
        auto e = i == 0 ? make_pair(1, n) : make_pair(a-1, a);
        val.check(edges.count(e), "Must have connection between villages ",
                i+1, " and ", (i+v-1)%v+1);
        val.check(D.size[D.find(a)] == u[i], "Village ", i+1, " is not connected");
    }
    val.check(int(cross_edges.size()) == v, "Number of edges between villages ",
            "must equal the number of villages");

    auto terminals = val.read_integers("t", k, 1, n, Unique);
    vector<int> count(v);
    for (int t: terminals) {
        count[where(t)]++;
    }
    for (int i = 0; i < v; i++) {
        val.check(count[i] <= NUM_TERMINALS_PER_VILLAGE, "Village ", i+1,
                "has too many terminals");
    }
}
