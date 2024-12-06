#include "validate.h"
using namespace std;

int main(int argc, char** argv) {
	InputValidator::init(argc, argv);
	using namespace InputValidator;

	Integer n = testIn.integer(1, 501, constraint["n"]);
	testIn.newline();

	set<pair<Integer, Integer>> pos;
	set<Integer> height;
	for (Integer i = 0; i < n; i++) {
		Integer x = testIn.integer(0, 10'001, constraint["x"]);
		testIn.space();
		Integer y = testIn.integer(0, 10'001, constraint["y"]);
		testIn.space();
		Integer h = testIn.integer(1, 10'001, constraint["h"]);
		testIn.newline();

		if (!pos.insert({x, y}).second) juryOut << "duplicate position: " << x << " " << y << WA;
		if (!height.insert(h).second) juryOut << "duplicate height: " << h << WA;
	}
	testIn.eof();
	return AC;
}
