#include "validate.h"
#include "graph_val.h"
using namespace InputValidator;

void check(Integer t) {
	Integer n = testIn.integer(1, 20001);
	testIn.space();
	Integer e = testIn.integer(0, 100001);
	testIn.newline();

	testIn.integers(n, 0, 10001);
	testIn.newline();

	DiGraph g(1, n+1);
	for (Integer i = 0; i < e; i++) {
		Integer a = testIn.integer(1, n+1);
		testIn.space();
		Integer b = testIn.integer(1, n+1);
		testIn.space();
		Integer c = testIn.integer(0, 10001);
		testIn.newline();

		g.addEdge(a, b);
	}

	if (!g.isDAG()) juryOut << "testcase " << t << " not a dag" << WA;

	std::vector<Integer> todo = {1};
	std::vector<bool> seen(n+1);
	seen[1] = true;
	Integer count = 1;
	while  (!todo.empty()) {
		Integer c = todo.back();
		todo.pop_back();
		for (Integer x : g[c]) {
			if (seen[x]) continue;
			seen[x] = true;
			count++;
			todo.push_back(x);
		}
	}
	if (count != n) juryOut << "testcase " << t << " not all vertices reachable" << WA;
}

int main(int argc, char **argv) {
	InputValidator::init(argc, argv);

	Integer t = testIn.integer(1, 11);
	testIn.newline();
	for (Integer i = 0; i < t; i++) check(i);
	testIn.eof();
	return AC;
}
