#include <iostream>
#include <vector>

const int R = 59;
const int C = 43;

const std::vector<std::vector<std::pair<int, int>>> strategies = {
	{{2, 1}, {3, 1}, {2, 2}, {2, 3}, {3, 3}},
	{{3, 1}, {2, 1}, {2, 2}, {1, 3}, {3, 3}},
	{{3, 1}, {2, 1}, {1, 3}, {2, 2}, {1, 2}},
	{{2, 1}, {3, 1}, {1, 3}, {1, 2}, {3, 2}, {4, 3}, {2, 3}, {1, 4}, {4, 1}},
};

std::pair<int, int> move(int x, int y) {
	std::cout << R + 1 - x << ' ' << C + 1 - y << std::endl;
	int resx, resy;
	std::cin >> resx >> resy;
	if (resx == 0) exit(0);
	return {R + 1 - resx, C + 1 - resy};
}

void play(int strategy, bool flip) {
	std::pair<int, int> pre(-1, -1);
	for (auto cell : strategies[strategy]) {
		if (flip) std::swap(cell.first, cell.second);
		if (pre != cell) pre = move(cell.first, cell.second);
	}
}

int main() {
	auto [x, y] = move(1, 1);
	if (x == 1 || y >= 4) play(0, false);
	else if (x >= 4 || y == 1) play(0, true);
	else if (x == 2 && y == 3) play(1, false);
	else if (x == 3 && y == 2) play(1, true);
	else if (x == 3 && y == 3) play(2, true);
	else if (x == 2 && y == 2) play(3, false);
	return 0;
}
