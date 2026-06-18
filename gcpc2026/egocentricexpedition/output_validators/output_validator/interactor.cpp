#include "validate.h"
using namespace std;

constexpr Real dlim = 50;
constexpr Integer xylim = 50;
constexpr Integer digits = 10;
constexpr Integer query_limit = 2;

using pt = complex<Real>;

Real lineIntersection(pt p0, pt p1, pt p2, pt p3) { // dist to p0
    Real a = cross(p1 - p0, p3 - p2);
    Real b = cross(p2 - p0, p3 - p2);
    // if (abs(a) < 0.7) return 1e18;
    return abs(b/a) * abs(p1 - p0);
}

pt rotCW(pt p) {
    return pt(imag(p), -real(p));
}


Real getDist(pt corner, pt dir) {
    // by statement the judges output can't be bigger than dlim
    Real res = dlim;
    for (pt c : {corner, rotCW(corner)}) {
        pt c2 = rotCW(c);
        if (cross(c2 - c, dir) != 0) { // not parallel
            res = min(res, lineIntersection(pt(0, 0), dir, c, c2));
        }
    }
    return res;
}

int main(int argc, char *argv[]) {
    Interactor::init(argc, argv);
    using namespace Interactor;

    Integer wrong = 0;
    Integer t = testIn.integer();

    toTeam << fixed << setprecision(digits);
    toTeam << t << endl;

    for (Integer i = 0; i < t; i++) {
        Real wx = testIn.real(-dlim, dlim);
        Real wy = testIn.real(-dlim, dlim);
        pt corner = {wx, wy};
        Integer expected = round(2 * norm(corner));

        for (int q_cnt = 1; ; q_cnt++) {
            string op = fromTeam.string(regex("\\?|!"));
            fromTeam.space();

            if (op == "?") {
                if (q_cnt > query_limit) {
                    juryOut << "Query limit exceeded at test " << i+1 << WA;
                }
                Integer x = fromTeam.integer(-xylim, xylim + 1);
                fromTeam.space();
                Integer y = fromTeam.integer(-xylim, xylim + 1);
                fromTeam.newline();
                if (abs(x) + abs(y) == 0) juryOut << "Direction is (0, 0)" << WA;

                toTeam << getDist(corner, pt(x, y)) << endl;
            } else {
                Integer ans = fromTeam.integer();
                fromTeam.newline();
                if (ans != expected) {
                    juryOut << "WA in query " << i+1 << ", expected: " << expected 
                            << " found: " << ans << endl; 
                    wrong++;
                }
                break;
            }
        }
    }
    fromTeam.eof();

    if (wrong != 0) juryOut << wrong << " out of " << t << " test cases wrong" << WA;
    juryOut << t << " cases correct" << AC;
}
 

