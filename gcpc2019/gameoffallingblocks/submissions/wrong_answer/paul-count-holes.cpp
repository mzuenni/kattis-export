#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < int(b); i++)

const int H = 20, W = 10;

typedef bitset<H*W> bits;

bits bottom_row, rightmost_column;
bits piece[7][4];

const string id_pieces = "IJLOSTZ";
const vector<vector<string>> ascii_pieces =
	{{"####"}, {"###", "#.."}, {"###", "..#"}, {"##", "##"},
	 {"##.", ".##"}, {"###", ".#."}, {".##", "##."}};

vector<string> rotate(vector<string> a) {
	int m = a.size(), n = a[0].size();
	vector<string> b(n,string(m,' '));
	FOR(i,0,m) FOR(j,0,n) b[n-1-j][i] = a[i][j];
	return b;
}

bits place(bits state, int pc, int rot, int x) {
	bits prv = state;
	for (int y = H-1; y > 0; y--) {
		bits cur = piece[pc][rot] << ((y-1)*W+x);
		if ((state & cur).any()) return state | prv;
		prv = cur;
	}
	return state | prv;
}

int score(bits state) {
	int holes = -state.count();
	for (int x = 0; x < W; x++) {
		int y = H-1;
		while (y > 0 && !state[(y-1)*W+x]) y--;
		holes += y;
	}
	return holes;
}

int main() {
	FOR(x,0,W) bottom_row[x] = 1;
	FOR(y,0,H) rightmost_column[y*W+W-1] = 1;
	FOR(i,0,7) {
		auto a = ascii_pieces[i];
		FOR(dir,0,4) {
			FOR(y,0,a.size()) FOR(x,0,a[0].size()) {
				piece[i][dir][y*W+x] = a[y][x] == '#';
			}
			a = rotate(a);
		}
	}

	bits state;
	char c;
	while (cin >> c) {
		if (c == 'W') break;
		
		int pc = 0;
		while (id_pieces[pc] != c) pc++;
		
		int best = INT_MAX, best_rot = -1, best_x = -1;
		
		FOR(rot,0,4) FOR(x,0,W) {
			bits nstate = place(state, pc, rot, x);
			if (score(nstate) < best) {
				best = score(nstate), best_rot = rot, best_x = x;
			}
			if (((piece[pc][rot] << x) & rightmost_column).any()) break;
		}

		state = place(state, pc, best_rot, best_x);
		cout << best_rot << " " << best_x+1 << endl;

		FOR(y,0,H) {
			FOR(x,0,W) cerr << ".#"[state[(H-1-y)*W+x]];
			cerr << endl;
		}
	}
}
