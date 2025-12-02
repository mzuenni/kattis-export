#include <cinttypes>
#include <array>
#include "visualizer_svg.h"
using namespace std;

int main(int argc, char** argv) {
	Visualizer::init(argc, argv);
	using namespace Visualizer;

	Stroke stroke(BLACK, 0.1);
	stroke.linecap = Linecap::ROUND;
	stroke.linejoin = Linejoin::ROUND;

	Fill ef(LIGHTGRAY);
	Fill fill(BLACK);

	Integer n;
	testIn >> n;

	if (n > 100) {
		return 0;
	}

	image.dimension = { (Real)(n + 2), (Real)(2 * (n + 2)) };
	image.origin = { 0, (Real)(- n - 2) };

	for (Integer i = 0; i <= n; ++i) {
		for (Integer j = 0; j <= n; ++j) {
			Ellipse e((Real)(1 + i), (Real)(j - n - 1), 0.05, 0.05);
			e.fill = ef;
			image << e << endl;
		}
	}

	for (Integer i = 0; i < n; ++i) {
		Integer a;
		testIn >> a;

		Rectangle rect((Real)(i + 1), 1, 1, (Real)a);
		rect.fill = fill;

		image << rect << endl;

		Integer l = i + 1;
		Integer r = a - i - 1;

		if (r >= 0) {
			Line li((Real)(1 + r), (Real)(-l), (Real)(1 + r), (Real)(-l - 1));
			li.stroke = stroke;
			image << li << endl;
		}

		l = a - n + i;
		r = n - i;
		if (l >= 0) {
			Line li((Real)r, (Real)(-1 - l), (Real)(1 + r), Real(-1 - l));
			li.stroke = stroke;
			image << li << endl;
		}
	}
}
