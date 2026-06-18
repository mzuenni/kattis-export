#include "validate.h"
#include "validator_logic.h"

using namespace std;
using namespace Verdicts;

int main(int argc, char** argv){
	using namespace OutputValidator;
	init(argc, argv);

	Integer targetArea = testIn.integer();
	// jury solution is checked in answer_validator!
	// performValidation(targetArea, juryAns, juryOut, FAIL);
	performValidation(targetArea, teamAns, juryOut, WA);
	juryOut << "OK" << AC;
}
