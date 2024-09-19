#include "validate.h"
#include "graph_val.h"

int main(int argc, char **argv) {
	InputValidator::init(argc, argv);			// initialize streams, rng and parse arguments
	using namespace InputValidator;

	Integer n = testIn.integer(2, 200001);		// read nodes
	testIn.space();
	Integer m = testIn.integer(n-1, 1000001);		// read vertices
    testIn.space(); 
    Integer k = testIn.integer(2, n + 1); 
	testIn.newline();

    std::vector<Integer> w = testIn.integers(1, n + 1, k);  
    testIn.newline(); 
    if(!areDistinct(w)) juryOut << "not distinct" << std::endl; 

	Graph g(1, n+1);
	for (Integer i = 0; i < m; i++) {			// read edges
		Integer a = testIn.integer(1, n+1);
		testIn.space();
		Integer b = testIn.integer(1, n+1);
		testIn.newline();

		g.addEdge(a, b);
	}
	testIn.eof();

	//check stuff, this can also be done on the fly!
	if (g.hasSelfloop()) juryOut << "selfloop: " << g.hasSelfloop().value() << WA;
	if (g.hasMultiedge()) juryOut << "multiedge: " << g.hasMultiedge().value() << WA;
	if (!g.isConnected()) juryOut << "not connected!" << WA;

	return AC;
}
