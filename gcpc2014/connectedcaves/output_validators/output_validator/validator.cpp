#include "validate.h"
#include "graph_val.h"
using namespace OutputValidator;

Integer parse(
	Integer t,
	Integer n,
	std::vector<Integer> vs,
	std::vector<std::map<Integer, Integer>> adj,
	InputStream& in,
	Verdict onError
) {
	Integer p = in.integer(0, 1000000001);
	Integer c = in.integer(1, n + 1);
	testIn.newline();

	auto cs = in.integers(c, 1, n + 1);
	Integer realP = 0;
	for (Integer& x : cs) {
		x--;
		realP += vs[x];
	}
	if (cs[0] != 0) juryOut << t+1 << ": path does not start at 1" << onError;
	for (Integer i = 1; i < c; i++) {
		if (adj[cs[i - 1]].find(cs[i]) == adj[cs[i - 1]].end()) juryOut << t+1 << ": path has invalid edge" << onError;
		realP -= adj[cs[i - 1]][cs[i]];
	}
	if (realP != p) juryOut << t+1 << ": P was computed wrong" << realP << " " << p << onError;
	return p;
}

void check(Integer t) {
	Integer n = testIn.integer(1, 20001);
	Integer e = testIn.integer(0, 100001);
	auto vs = testIn.integers(n, 0, 10001);

	std::vector<std::map<Integer, Integer>> adj(n);

	DiGraph g(1, n+1);
	for (Integer i = 0; i < e; i++) {
		Integer a = testIn.integer(1, n+1);
		testIn.space();
		Integer b = testIn.integer(1, n+1);
		testIn.space();
		Integer c = testIn.integer(0, 10001);
		testIn.newline();

		a--;
		b--;
		if (adj[a].find(b) == adj[a].end()) adj[a][b] = c;
		else adj[a][b] = std::min(adj[a][b], c);
	}

	Integer expected = parse(t, n, vs, adj, juryAns, FAIL);
	Integer got = parse(t, n, vs, adj, teamAns, WA);
	if (got > expected) juryOut << t+1 << ": team has better solution" << FAIL;
	if (got < expected) juryOut << t+1 << ": jury has better solution" << WA;
}

int main(int argc, char **argv) {
	OutputValidator::init(argc, argv);

	Integer t = testIn.integer(1, 11);
	for (Integer i = 0; i < t; i++) check(i);
	return AC;
}
