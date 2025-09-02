#include <bits/stdc++.h>
using namespace std;

struct block {
	int x, y; // the x-axis is pointing up, the y-axis is pointing right
};

struct piece {
	char id;
	vector<block> blocks;
	
	piece(char id, vector<string> v): id(id) {
		for (int i = 0; i < int(v.size()); i++) {
			for (int j = 0; j < int(v[i].size()); j++) {
				if (v[i][j] == '#') {
					blocks.push_back({int(v.size())-i-1,j});
				}
			}
		}
	}

	void rotate() { // clockwise rotation
		int xmin = 10, ymin = 10;
		for (auto &b: blocks) {
			b = {-b.y,b.x};
			xmin = min(xmin, b.x);
			ymin = min(ymin, b.y);
		}
		for (auto &b: blocks) {
			b.x -= xmin;
			b.y -= ymin;
		}	
	}
};

const vector<piece> tetrominoes = {
	piece('I', {"####"}),
	piece('J', {"#..","###"}),
	piece('L', {"..#","###"}),
	piece('O', {"##","##"}),
	piece('S', {".##","##."}),
	piece('T', {".#.","###"}),
	piece('Z', {"##.",".##"})
};
