#include <cinttypes>
#include <array>
#include "visualizer_svg.h"
using namespace std;

// test cases are visualized bottom to top because I'm lazy

int main(int argc, char** argv) {
    Visualizer::init(argc, argv);
    using namespace Visualizer;

    Stroke stroke(BLACK, 0.1);
    stroke.linecap = Linecap::ROUND;
    stroke.linejoin = Linejoin::ROUND;

    Integer t;
    testIn >> t;

    if (t > 100) return 0;

    Integer mxx = -1e18, mxy = -1e18;
    Integer offset = 0;

    for (int tt=0; tt<t; tt++) {
        Integer n;
        testIn >> n;
        if (n > 100) return 0;
        for (int i=0; i<n; i++) {
            Integer x1, y1, x2, y2;
            testIn >> x1 >> y1 >> x2 >> y2;
            y1 += offset, y2 += offset;
            Line line({(Real)x1, (Real)y1}, {(Real)x2, (Real)y2});
            line.stroke = stroke;
            image << line << endl;

            mxx = max(mxx, x2);
            mxy = max(mxy, y2);
        }

        offset = mxy + 2;

        Line line({-1, (Real)offset - 1}, {(Real)mxx + 1, (Real)offset - 1});
        Stroke stroke2(RED, 0.5);
        stroke2.linecap = Linecap::ROUND;
        stroke2.linejoin = Linejoin::ROUND;
        line.stroke = stroke2;
        image << line << endl;
    }
    image.origin -= {2, 2};
    image.dimension += {4, 4};

    if (mxx < 1e3) {
        stroke.width = 0.01;
        for (Integer i=0; i<=mxx+1; i++) {
            Line line({(Real)i, -1}, {(Real)i, (Real)mxy+1});
            line.stroke = stroke;
            image << line << endl;
        }
    }
    if (mxy < 1e3) {
        for (Integer i=0; i<=mxy+1; i++) {
            Line line({-1, (Real)i}, {(Real)mxx+1, (Real)i});
            line.stroke = stroke;
            image << line << endl;
        }
    }
}
