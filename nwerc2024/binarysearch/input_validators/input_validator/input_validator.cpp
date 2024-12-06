#include "graph_val.h"
#include "validate.h"

int main(int argc, char* argv[]) {
	Integer maxn = 300'000;
	Integer maxm = 300'000;

	InputValidator::init(argc, argv);
	using namespace InputValidator;

	Integer n = testIn.integer(1, maxn + 1, constraint["n"]);
	testIn.space();
	Integer m = testIn.integer(0, maxm + 1, constraint["m"]);
	testIn.newline();

	testIn.integers(0, 2, constraint["a"], n);
	testIn.newline();

	Graph all(1, n + 1);
	for(int i = 0; i < m; i++) {
		Integer a = testIn.integer(1, n + 1, constraint["u"]);
		testIn.space();
		Integer b = testIn.integer(1, n + 1, constraint["v"]);
		testIn.newline();
		all.addEdge(a, b);
	}

	// check if simple
	if(all.hasMultiedge()) juryOut << "no multi-edges allowed" << WA;
	if(all.hasSelfloop()) juryOut << "no selfloops allowed" << WA;

	testIn.eof();
	juryOut << AC;
}
