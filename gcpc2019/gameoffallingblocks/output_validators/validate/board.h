#include <bits/stdc++.h>
#include "piece.h"
using namespace std;

const int H = 20, W = 10;

struct board {
	char B[H+1][W+2];
	
	board() {
		memset(B,'.',sizeof B);
		for (int r = 0; r < H; r++) {
			B[r][0] = B[r][W+1] = '|';
		}
	}
	
	bool completed_row() {
		for (int r = 0; r < H; r++) {
			bool ok = true;
			for (int c = 1; c <= W; c++) if (B[r][c] == '.') ok = false;
			if (ok) return true;
		}
		return false;
	}
	
	bool can_place(piece P, int r, int c, bool check_bounds) {
		for (auto b: P.blocks) {
			int i = r + b.x, j = c + b.y;
			if (i < 0 || i >= H || j < 1 || j > W) {
				if (check_bounds) return false;
			} else {
				if (B[i][j] != '.') return false;
			}
		}
		return true;
	}

	bool drop_piece(piece P, int rot, int c) {
		while (rot--) P.rotate();
		int r = H;
		while (r > 0 && can_place(P, r-1, c, false)) r--;
		
		bool res = can_place(P, r, c, true);

		for (auto b: P.blocks) {
			int i = r + b.x, j = c + b.y;
			if (i >= 0 && i <= H && j >= 0 && j <= W+1) {
				B[i][j] = P.id;
			}
		}
		
		return res;
	}

	string pretty_print() {
		string res;
		for (int r = H; r >= 0; r--) {
			bool any_piece = false;
			for (int c = 0; c <= W+1; c++) {
				if (B[r][c] != '.' && B[r][c] != '|') any_piece = true;
			}
			if (!any_piece) continue;
			string id = to_string(r+1) + " ";
			if (id.size() < 3) id = " " + id;
			res += id;
			for (int c = 0; c <= W+1; c++) {
				res.push_back(B[r][c]);
			}
			res.push_back('\n');
		}
		return res;
	}
};
