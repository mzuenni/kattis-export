#include <cinttypes>
#include "visualizer_svg.h"
#include <complex>
using namespace std;
using Real = long double;

int main(int argc, char** argv) {
    Visualizer::init(argc, argv);
    using namespace Visualizer;

    Stroke stroke(BLACK, 0.1);
    stroke.linecap = Linecap::ROUND;
    stroke.linejoin = Linejoin::ROUND;

    Integer t;
    testIn >> t;

    if (t > 100) return 0;

    Integer offset = 0;
    const Integer offsetx = 50;

    for (int tt=0; tt<t; tt++) {
        Real x, y;
        testIn >> x >> y;

        complex<Real> p = {x, y};
        offset += (Integer)p.imag() + 2;

        for (int i=0; i<4; i++) {
            complex<Real> p2 = {-p.imag(), p.real()};
            Line line({p.real() + offsetx, -(p.imag() + offset)}, 
                      {p2.real() + offsetx, -(p2.imag() + offset)});
            line.stroke = stroke;
            image << line << endl;
            p = p2;
        }
        
        Circle mid = Circle({(Real)offsetx, -(Real)offset}, 0.5);
        mid.fill = Fill(Color((uint32_t)0xFF0000));
        image << mid << endl;

        offset += (Integer)p.imag() + 2;
    }

    image.origin -= {2, 2};
    image.dimension += {4, 4};

    stroke.width = 0.01;
    for (Integer i=0; i<=100; i++) {
        Line line({(Real)i, 0}, {(Real)i, -(Real)offset});
        line.stroke = stroke;
        image << line << endl;
    }
    for (Integer i=0; i<=offset; i++) {
        Line line({0, -(Real)i}, {(Real)100, -(Real)i});
        line.stroke = stroke;
        image << line << endl;
    }
}
