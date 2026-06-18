#include "validate.h"
#include "validator_logic.h"
using namespace AnswerValidator;

int main(int argc, char *argv[]) {
	init(argc, argv);
	Integer targetArea = testIn.integer();
	performValidation(targetArea, ans, juryOut, WA);
	juryOut << AC;
}
