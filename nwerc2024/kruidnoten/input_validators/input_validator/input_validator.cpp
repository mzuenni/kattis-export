#include "graph_val.h"
#include "validate.h"

int main(int argc, char *argv[]) {
    Integer maxn = 200'000;
    Integer maxm = 200'000;
    Integer maxk = 200'000;
    Integer maxw = 1'000'000;

    InputValidator::init(argc, argv);
	using namespace InputValidator;

    Integer n = testIn.integer(2, maxn + 1, constraint["n"]);
    testIn.space();
    Integer m = testIn.integer(1, maxm + 1, constraint["m"]);
    testIn.space();
    Integer k = testIn.integer(1, std::min(maxk + 1, n + 1), constraint["k"]);
    testIn.newline();
    Graph all(1, n + 1);

    for (int i = 0; i < m; i++) {
        Integer a = testIn.integer(1, n + 1, constraint["a"]);
        testIn.space();
        Integer b = testIn.integer(1, n + 1, constraint["b"]);
        testIn.space();
        testIn.integer(1, maxw + 1, constraint["l"]);
        testIn.newline();
        all.addEdge(a, b);
    }

    // check if simple and connected
    if (!all.isConnected()) juryOut << "graph is not connected" << WA;
    if (all.hasMultiedge()) juryOut << "no multi-edges allowed" << WA;
    if (all.hasSelfloop()) juryOut << "no selfloops allowed" << WA;

    std::set<Integer> s;
    for (int i = 0; i < k; i++) {
        Integer a = testIn.integer(1, n + 1, constraint["a2"]);
        s.insert(a);
        testIn.space();
        Real p = testIn.realStrict(0.0001l, 1.00000001l, 0, 5, constraint["p"]);
        // ugh
        if (p > 1.0 || p == 0.0) juryOut << "not a prob" << WA;
        testIn.newline();
    }
    if (s.size() != k) juryOut << "special vertices not distinct" << WA;

    testIn.eof();
    juryOut << AC;
}
