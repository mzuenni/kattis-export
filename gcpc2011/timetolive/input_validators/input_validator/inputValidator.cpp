#include "validate.h"
#include "graph_val.h"
using namespace InputValidator;

void check(Integer t) {
	Integer n = testIn.integer(1, 100'001);
	testIn.newline();

	Graph g(0, n);
	for (Integer i = 1; i < n; i++) {
		Integer a = testIn.integer(0, n);
		testIn.space();
		Integer b = testIn.integer(0, n);
		testIn.newline();

		g.addEdge(a, b);
	}
	if (!g.isTree()) juryOut << t+1 << ": not a tree!" << WA;
}

int main(int argc, char **argv) {
	InputValidator::init(argc, argv);

	Integer c = testIn.integer(1, 100);
	testIn.newline();
	for (Integer i = 0; i < c; i++) check(i);
	testIn.eof();
	return AC;
}
