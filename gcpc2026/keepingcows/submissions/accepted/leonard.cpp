#include <cassert>
#include <iostream>
#include <string>
#include <vector>

int main() {
	int a;
	std::cin >> a;

	const int n = 100;

	std::vector<std::string> grid(n, std::string(n, '.'));

	for (int i = 3; i < n - 2; i += 2) {
		grid[i][0] = grid[0][i] = grid[n - 1][i] = '#';
		grid[i][1] = grid[1][i] = grid[n - 2][i] = 'O';
	}

	for (int i = 2; i < n - 2; i += 2) {
		grid[i][1] = grid[1][i] = grid[n - 2][i] = '#';
	}

	int col = 2;

	while (a >= n - 4) {
		col += 1;
		a -= n - 4;
	}

	assert(a < n - 4);
	assert(col + 1 < n);

	for (int i = 2; i < n - 2; i += 2) {
		if (a % 2 == 1) {
			grid[i][col] = '#';
			grid[i][col + 1] = 'O';
			grid[i + 1][col + 1] = '#';
			a -= 1;
		}
		else if (a >= 2) {
			grid[i][col + 1] = 'O';
			grid[i + 1][col + 1] = '#';
			grid[i][col + 2] = '#';
			a -= 2;
		}
		else {
			grid[i][col] = 'O';
			grid[i + 1][col] = '#';
			grid[i][col + 1] = '#';
		}
	}

	std::cout << n << ' ' << n << '\n';

	for (int i = 0; i < n; ++i) {
		std::cout << grid[i] << '\n';
	}

	return 0;
}
