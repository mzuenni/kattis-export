#include "validation.h"

#include <iostream>
using namespace std;

int main(int argc, char **argv) {
	ifstream in(argv[1]);
	OutputValidator v(argc, argv);

	int h, w, n;
	in >> h >> w >> n;

	string chars(2*n, ' ');
	iota(begin(chars), begin(chars)+n, 'A');
	iota(begin(chars)+n, begin(chars)+2*n, 'a');

	if ((h*w) % n == 0) {
		auto grid = v.read_strings("grid", h, w, w, chars, Arbitrary, Newline);
		for (auto& line : grid) for (auto& c : line) c &= ~0x20;
		vector<int> count(n), imin(n,h), imax(n,-1), jmin(n,w), jmax(n,-1);
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				int k = grid[i][j]-'A';
				count[k]++;
				imin[k] = min(imin[k], i), imax[k] = max(imax[k], i);
				jmin[k] = min(jmin[k], j), jmax[k] = max(jmax[k], j);
			}
		}

		for (int k = 0; k < n; k++) {
			int box = (imax[k]-imin[k]+1) * (jmax[k]-jmin[k]+1);
			v.check(count[k] == box, "Region ", char('A'+k), " is not a rectangle.");
			v.check(n*box == h*w, "Region ", char('A'+k), " does not have the correct size.");
		}
	} else {
		v.test_string("impossible");
		v.newline();
	}
}
