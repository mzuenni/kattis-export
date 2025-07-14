#include "validate.h"
using namespace std;

constexpr Integer MAXN = 1e5;
constexpr Integer MAXX = 1e5;

using pt = complex<Integer>;

int main(int argc, char **argv) {
    InputValidator::init(argc, argv);
    using namespace InputValidator;

    Integer n = testIn.integer(4, MAXN+1);
    testIn.newline();

    vector<pt> poly(n);
    for (int i=0; i<n; i++) {
        Integer x = testIn.integer(-MAXX, MAXX+1);
        testIn.space();
        Integer y = testIn.integer(-MAXX, MAXX+1);
        testIn.newline();

        poly[i] = {x, y};
    }
    testIn.eof();

    if (!isConvex(poly)) juryOut << "polygon is not convex" << WA;

    poly.push_back(poly[0]);
    poly.push_back(poly[1]);
    for (int i=0; i<n; i++) {
        if (dot(poly[i+1] - poly[i], poly[i+2] - poly[i+1]) < 0) juryOut << "angle below 90 degrees at vertex " << i+2 << WA;
    }

    juryOut << "OK!" << AC;
}
