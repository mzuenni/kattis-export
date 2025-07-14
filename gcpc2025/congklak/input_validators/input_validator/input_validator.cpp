#include "validate.h"
using namespace std;

constexpr Integer MAXN = 1e5;
constexpr Integer MAXVAL = 1e12;

int main(int argc, char **argv) {
	InputValidator::init(argc, argv);
	using namespace InputValidator;

	Integer n = testIn.integer(1, MAXN+1);
	testIn.space();
	Integer t = testIn.integer(1, MAXVAL+1);
	testIn.newline();
	testIn.integers(0, MAXVAL+1, n);
	testIn.newline();
	testIn.eof();

	juryOut << "OK!" << AC;
}
