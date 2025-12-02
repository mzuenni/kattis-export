#include "validate.h"
using namespace AnswerValidator;

int main(int argc, char **argv) {
	AnswerValidator::init(argc, argv);

    Integer t = testIn.integer();

    for (int i=0; i<t; i++) {
        ans.string(std::regex("yes|no"));
        ans.newline();
    }

    ans.eof();
	juryOut << AC;
}
