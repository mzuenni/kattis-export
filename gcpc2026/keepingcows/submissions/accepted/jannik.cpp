#include <iostream>

using namespace std;

const char* aa[] = {
	"4 4\n#.#.\nO#O#\n#.#.\nO#O#\n", // 1
	"4 4\nO##.\n#.O#\n#.#.\nO#O#\n", // 2
	"4 4\nO##O\n#..#\n#.#.\nO#O#\n", // 3
	"","",
	"6 6\nO#O#O#\n#.#.#.\n#...O#\nO#.##.\n..#O#.\n..O#..\n", // 6
	"6 6\nO#O##O\n#.#..#\n#...O#\nO#.##.\n..#O#.\n..O#..\n", // 7
	"","","",
	"6 6\nO##O#O\n#..#.#\nO#...#\n#...#O\n#.#.O#\nO#O##.\n", // 11
};

int main()
{
	int a;
	cin >> a;
	if (a < 4 or a == 6 or a == 7 or a == 11) {
		cout << aa[a - 1];
		return 0;
	}
	int w, h, num_flipped;

	for (w = 3; w <= 50; w++)
		for (h = 2; h <= 50; h++)
			if (num_flipped = a - 4 * (w - 2) * (h - 2); num_flipped >= 0 and num_flipped <= h - 2)
				goto found;
	return 42;
found:;
	h *= 2, w *= 2;
	cout << h << ' ' << w << '\n';
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++)
			if ((j > 1 and (i == 1 or i == h - 2) and j % 2) or (j == 1 and i % 2))
				cout << 'O';
			else if (j == w - 1 - (i / 2 > num_flipped) and i > 1 and i < h - 2)
				cout << (i % 2 ? 'O' : '#');
			else if (j == 1 or i == 1 or (i == h - 2 and j > 0) or (j == 0 and i % 2) or ((i == 0 or i == h - 1) and j % 2) or (j > w - 3 and i % 2 and i < h - 2))
				cout << '#';
			else
				cout << '.';
		cout << '\n';
	}
}
