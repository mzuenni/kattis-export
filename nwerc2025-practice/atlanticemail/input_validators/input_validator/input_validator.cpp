#include "validate.h"

inline const std::regex operationRegex("send|receive", REGEX_OPTIONS);
inline const std::regex lowerRegex("[a-z]*", REGEX_OPTIONS);
inline const std::regex bitsRegex("[01]*", REGEX_OPTIONS);
const int maxn = 10000;
int main(int argc, char **argv) {
	InputValidator::init(argc, argv);			// initialize streams, rng and parse arguments
	using namespace InputValidator;
	std::string operation = testIn.string(operationRegex);
	testIn.newline();
	if(operation=="send") {
		Integer n = testIn.integer(1,maxn+1); // halfopen
		testIn.newline();
		std::string s = testIn.string(lowerRegex,n,n+1); // halfopen
		testIn.newline();

	} else {
		for(int j=0;j<5;++j) {
			std::string b = testIn.string(1,maxn+11); // HALF-OPEN!
			testIn.newline();
		}
	}
	testIn.eof();
	return AC;
}
