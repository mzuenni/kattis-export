#include "validate.h"
#include "graph_val.h"

int main(int argc, char **argv) {
	InputValidator::init(argc, argv);
	using namespace InputValidator;

	Integer n = testIn.integer(3, 100001, constraint["n"]);
	testIn.newline();

	Graph g(1, n+1);
	for (Integer i = 1; i < n; i++) {
		Integer a = testIn.integer(1, n+1, constraint["a"]);
		testIn.space();
		Integer b = testIn.integer(1, n+1, constraint["b"]);
		testIn.space();
		Integer w = testIn.integer(1, 1'000'001, constraint["w"]);
		testIn.newline();
		g.addEdge(a, b);
		if (!g.isForest()) juryOut << "not a tree: " << a << " " << b << WA;
	}
	if (!g.isTree()) juryOut << "not a tree" << WA;
	
	Integer m = testIn.integer(1, 500001, constraint["m"]);
	testIn.newline();
	for (Integer i = 0; i < m; i++) {
		Integer a = testIn.integer(1, n+1);
		testIn.space();
		Integer b = testIn.integer(1, n+1);
		testIn.newline();
		g.addEdge(a, b);
		if (a == b || g.hasMultiedge()) juryOut << "invalid bridge: " << a << " " << b << WA;
	}
	testIn.eof();

	return AC;
}
