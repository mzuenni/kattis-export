#include "validate.h"
using namespace InputValidator;

using pt = std::pair<Integer, Integer>;

std::vector<pt> read_poly(Integer n) {
	std::vector<pt> poly(n);
	for (auto& [x,y] : poly) {
		x = testIn.integer(1, 1'000'000'001);
		testIn.space();
		y = testIn.integer(1, 1'000'000'001);
		testIn.newline();
	}
	return poly;
}

void check_poly(std::vector<pt> poly) {
	if (!isSimple(poly)) juryOut << "polygon is not simple" << WA;
	if (!isCCW(poly)) juryOut << "polygon is not counter-clockwise" << WA;

	Integer n = poly.size();
	poly.push_back(poly[0]);
	poly.push_back(poly[1]);
	for (Integer i = 0; i < n; i++) {
		if (poly[i] == poly[i+1]) juryOut << "consecutive points are equal " << i+1 << WA;
		if (cross(poly[i], poly[i+1], poly[i+2]) == 0) juryOut << "polygon is not strict " << i+2 << WA;
		if ((getX(poly[i]) == getX(poly[i+1])) ==
			(getY(poly[i]) == getY(poly[i+1]))) juryOut << "polygon is not rectilinear " << i+2 << WA;
	}
}

int main(int argc, char **argv) {
	init(argc, argv);

	Integer n = testIn.integer(4, 100'001);
	testIn.newline();

	check_poly(read_poly(n));
	testIn.eof();

	return AC;
}
