#include "validate.h"
using namespace InputValidator;

int main(int argc, char **argv) {
	InputValidator::init(argc, argv);

	Integer n = testIn.integer(5, 1'001, constraint["n"]);
	testIn.newline();

    auto perm = testIn.integers(n, 1, n+1);
    testIn.newline();

    if (!areDistinct(perm)) {
        juryOut << "not a permutation" << WA;
    }
    testIn.eof();

	juryOut << "ok" << AC;
}
