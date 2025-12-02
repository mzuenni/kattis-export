#include "validate.h"
using namespace InputValidator;

Integer K = 10;
Integer MAXN = 100;
Integer SLEN = 20;

int main(int argc, char *argv[]) {
    init(argc, argv);

    Integer n = testIn.integer(1, MAXN + 1, constraint["n"]);
    testIn.newline();
    for (Integer z = 0; z < n; z++) {
        testIn.strings(K, std::regex("[a-z]+"), 1, SLEN + 1, constraint["s"]);
        testIn.newline();
    }
    testIn.eof();
    return AC;
}
