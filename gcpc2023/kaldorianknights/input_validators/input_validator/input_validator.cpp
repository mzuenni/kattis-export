#include "validate.h"
#include <algorithm>

const Integer NMAX = 1000000;
const Integer KMAX = 5000;

int main(int argc, char **argv) {
	InputValidator::init(argc, argv);
	using namespace InputValidator;

	Integer n = testIn.integer(1, NMAX+1);
	testIn.space();
	Integer k = testIn.integer(0, std::min(KMAX, n)+1);
	testIn.newline();

    Integer sum = 0; 
	for (Integer l = 0; l < k; l++) {
		Integer a = testIn.integer(1, n+1);
		testIn.newline();
        sum += a;
	}
    if(sum > n) juryOut << "sum of clan sizes larger n: " << sum << WA; 
	testIn.eof();
	return AC;
}
