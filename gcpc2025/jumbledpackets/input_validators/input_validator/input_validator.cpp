#include "validate.h"
using namespace std;

int main(int argc, char* argv[]) {
    InputValidator::init(argc, argv);
    using namespace InputValidator;

    testIn.expectString("Encode");
    testIn.newline();
    
    Integer n = testIn.integer(1, 100'001);
    testIn.newline();

    testIn.string(regex("[01]+"), n, n+1);
    testIn.newline();
    testIn.eof();
    juryOut << "OK!" << AC;
}
