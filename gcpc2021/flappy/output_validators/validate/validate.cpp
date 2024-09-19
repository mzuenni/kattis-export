#include "validate.h"
#include <string>
#include <vector>

const int MAX_C = 1000000000;

struct Point {
	long long x, y;
	bool read(std::istream& in) {
		auto read_coordinate = [&](long long& to) {
			in >> to;
			if (to < -MAX_C || to > MAX_C)
				wrong_answer("Number exeeded %d", MAX_C);
			return !in.fail();
		};
		return read_coordinate(x) && read_coordinate(y);
	}
	friend bool operator==(const Point& a, const Point& b) {
		return a.x == b.x && a.y == b.y;
	}
};

long long cross(const Point& a, const Point& b, const Point& c) {
	Point ab{ b.x - a.x, b.y - a.y }, ac{ c.x - a.x, c.y - a.y };
	return ab.x*ac.y - ab.y*ac.x;
}

// reads up to max points from stream + filters colinear points
// exists with WA if points are not sorted by x-coordinate, if coordinates
// exceed limit or the input hasn't reached it's end after max points
std::vector<Point> read(std::istream& in, int max) {
	std::vector<Point> points;
	for (Point t; max > 0 && t.read(in); max--) {
		if (!points.empty() && points.back() == t)
			continue; // having duplicate points is technically allowed
		if (!points.empty() && points.back().x >= t.x)
			wrong_answer("Output is not sorted by x-coordinates, which cannot be minimum possible");
		while (points.size() > 1 && !cross(points.end()[-2], points.back(), t))
			points.pop_back();
		points.push_back(t);
	}
	std::string trailing;
	if (in >> trailing)
		wrong_answer("Trailing output/possibly more points than permitted");
	return points;
}

int main(int argc, char **argv) 
{
	init_io(argc,argv);
	int n;
	Point tmp;
	tmp.read(judge_in); // s
	tmp.read(judge_in); // t
	judge_in >> n;
	// answer is unique up to colinear points
	if (read(judge_ans, n+2) != read(author_out, n+2))
		wrong_answer("Output doesn't match expected line");
	accept();
}
