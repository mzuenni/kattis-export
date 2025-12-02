#include "validate.h"

inline const std::regex CHAR_REGEX("[.#]*", REGEX_OPTIONS);

int main(int argc, char** argv) {
	InputValidator::init(argc, argv); // initialize streams, rng and parse arguments
	using namespace InputValidator;

	Integer t = testIn.integer(1, 10'001, constraint["t"]);
	testIn.newline();
	for(Integer i = 0; i < t; i++) {
		Integer h = testIn.integer(1, 9, constraint["h"]);
		testIn.space();
		Integer w = testIn.integer(1, 9, constraint["w"]);
		testIn.space();
		Integer k = testIn.integer(1, h * w, constraint["k"]);
		testIn.newline();

		bool free = false;
		bool used = false;
		int count = 0;
		for(Integer j = 0; j < h; j++) {
			std::string s = testIn.string(CHAR_REGEX, w, w + 1);
			testIn.newline();
			for(char c : s) {
				count += c == '#';
				free |= c == '.';
				used |= c != '.';
			}
		}
		if(!free) juryOut << "no free cell in testcase: " << i + 1 << WA;
		if(!used) juryOut << "all cells are free in testcase: " << i + 1 << WA;
		if(count != k)
			juryOut << "number of blocked cells (" << count << ") does not match k (" << k
			        << ") in testcase: " << i + 1 << WA;
	}
	testIn.eof();
	return AC;
}
