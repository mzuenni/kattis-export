/**
 * This submission reduces the window of the possible path until there is none left.
 * Then adds the corner that is grazed to the path and restarts the process from there.
 */

#include <iostream>
#include <vector>


typedef struct Point {
	long long x;
	long long y;
} Point;

typedef struct Window {
	std::size_t upper;
	std::size_t lower;
} Window;

using Line = std::pair<Point, Point>;
using Path = std::vector<Point>;

void solve(Point start, Path &path, std::vector<Line> &lines, std::size_t index) {
	Window wndw{index, index};
	++index;
	while(index < lines.size()) {
		Line &l = lines[index];
		long long x_diff_line = l.first.x - start.x;
		long long y_diff_line_low = l.first.y - start.y, y_diff_line_top = l.second.y - start.y;
		Line &upper = lines[wndw.upper], &lower = lines[wndw.lower];
		long long x_diff_wndw_low = lower.first.x - start.x, y_diff_wndw_low = lower.first.y - start.y;
		long long x_diff_wndw_up = upper.first.x - start.x, y_diff_wndw_up = upper.second.y- start.y;

		// Graze upper window edge
		if(x_diff_wndw_up * y_diff_line_low > y_diff_wndw_up * x_diff_line) {
			path.push_back(upper.second);
			start = upper.second;
			index = wndw.upper + 2;
			wndw.upper = index - 1;
			wndw.lower = index - 1;
			continue;
		}

		// Graze lower window edge
		if(x_diff_wndw_low * y_diff_line_top < y_diff_wndw_low * x_diff_line) {
			path.push_back(lower.first);
			start = lower.first;
			index = wndw.lower + 2;
			wndw.upper = index - 1;
			wndw.lower = index - 1;
			continue;
		}

		// Graze no edge
		// Adjusting upper / lower window edge
		if(x_diff_wndw_up * y_diff_line_top <= y_diff_wndw_up * x_diff_line) {
			wndw.upper = index;
		}
		if(x_diff_wndw_low * y_diff_line_low >= y_diff_wndw_low * x_diff_line) {
			wndw.lower = index;
		}

		++index;
	}
}

int main() {
	Point start, end;
	std::size_t n;
	std::cin >> start.x >> start.y >> end.x >> end.y >> n;
	std::vector<Line> lines;
	std::vector<Point> path;
	lines.reserve(n + 1);
	path.reserve(n + 2);
	while(n--) {
		lines.emplace_back();
		Line &l = lines.back();
		std::cin >> l.first.x >> l.first.y >> l.second.y;
		l.second.x = l.first.x;
	}
	lines.emplace_back();
	lines.back() = {end, end};

	solve(start, path, lines, 0);

	std::cout << start.x << " " << start.y << std::endl;
	for(Point &p : path) {
		std::cout << p.x << " " << p.y << std::endl;
	}
	std::cout << end.x << " " << end.y << std::endl;

	return 0;
}
