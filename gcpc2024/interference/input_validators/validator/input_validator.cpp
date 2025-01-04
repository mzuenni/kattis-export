#include "validate.h"

int main(int argc, char **argv) {
    InputValidator::init(argc, argv);
    using namespace InputValidator;

    Integer n = testIn.integer(1, 4'001);
    testIn.space();
    Integer w = testIn.integer(1, 1'000'000'001);
    testIn.newline();

    for (Integer i = 0; i < n; i++) {
        std::string token = testIn.string(1, 2);
        if (token == "?") {
            testIn.space();
            testIn.integer(1, w + 1);
            testIn.newline();
        } else if (token == "!") {
            testIn.space();
            Integer p = testIn.integer(1, w + 1);
            testIn.space();
            Integer l = testIn.integer(1, 1'000'000'001);
            if (p + l > w + 1) juryOut << "wavelength outside range. Wavelength=" << p << "+" << l << ", range=" << w << WA;
            testIn.space();
            Integer a = testIn.integer(1, 1'000'000'001);
            testIn.newline();
        }
    }
    testIn.eof();
    return AC;
}
