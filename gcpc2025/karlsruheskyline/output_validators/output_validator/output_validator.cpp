#include "validate.h"
using namespace std;
using namespace OutputValidator;

int n, a, b;

int visibleFromLeft(vector<Integer> h) {
    int res = 0, hmax = 0;
    for (int hcur: h) {
        if (hcur > hmax) {
            hmax = hcur;
            res++;
        }
    }
    return res;
}

bool readAndCheck(InputStream &in, string_view who, Verdict onFail) {
    auto yesNo = in.string(regex("yes|no"));
    in.newline();
    if (yesNo == "yes") {
        auto h = in.integers(1, n+1, n);
        in.newline();
        if (!areDistinct(h)) juryOut << "Heights are not unique for " << who << "." << onFail;
        int vl = visibleFromLeft(h);
        if (vl != a) {
            juryOut << "Number of visible buildings from left for " << who
                << " is " << vl << ", but should be " << a << "." << onFail;
        }
        reverse(begin(h), end(h));
        int vr = visibleFromLeft(h);
        if (vr != b) {
            juryOut << "Number of visible buildings from right for " << who
                << " is " << vr << ", but should be " << b << "." << onFail;
        }
    }
    in.eof();
    return yesNo == "yes";
}

int main(int argc, char *argv[]) {
    init(argc, argv);

    n = testIn.integer();
    testIn.space();
    a = testIn.integer();
    testIn.space();
    b = testIn.integer();

    bool juryRes = readAndCheck(juryAns, "jury", FAIL);
    bool teamRes = readAndCheck(teamAns, "team", WA);

    if (teamRes && !juryRes) {
        juryOut << "Team found a solution, but jury did not!" << FAIL;
    }
    if (juryRes && !teamRes) {
        juryOut << "Jury found a solution, but team did not!" << WA;
    }
    juryOut << AC;
}
