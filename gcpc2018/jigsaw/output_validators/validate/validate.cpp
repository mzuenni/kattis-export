#include <bits/stdc++.h>
#include "validate.h"
using namespace std;

int main(int argc, char **argv) {
	init_io(argc,argv);
	
	int n;
	judge_in >> n;

	bool found = false;
	int H, W;
	if (judge_ans >> H >> W) {
		// a solution exists
		vector<vector<int>> judge_res(H,vector<int>(W));
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
				judge_ans >> judge_res[i][j];

		int h, w;
		if (!(author_out >> h >> w))
			wrong_answer("Expected two integers, height and width.\n");
		
		if (h < 1 || w < 1 || h * 1LL * w != n)
			wrong_answer("The given grid dimensions are invalid.\n");
		
		vector<vector<int>> author_res(h,vector<int>(w));
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				if (!(author_out >> author_res[i][j]))
					wrong_answer("Expected a grid with %d numbers, received only %d.\n", n, h*w+j);

		for (int rot = 0; rot < 4; rot++) {
			if (judge_res == author_res) found = true;

			vector<vector<int>> new_judge_res(W,vector<int>(H));
			for (int i = 0; i < H; i++)
				for (int j = 0; j < W; j++)
					new_judge_res[j][H-i-1] = judge_res[i][j];
			swap(H,W);
			judge_res = new_judge_res;
		}

		if (!found) judge_message("The given grid is not a valid solution.\n");
	} else {
		// no solution exists
		string s;
		if (!(author_out >> s))
			wrong_answer("Team output is empty.\n");
		transform(begin(s),end(s),begin(s), ::tolower);
		if (s != "impossible")
			wrong_answer("Expected \"impossible\", but found %s.\n", s.c_str());
		
		found = true;
	}
	string junk;
	if (author_out >> junk)
		wrong_answer("Found trailing junk.\n");

	if (found)
		accept();
	else
		wrong_answer("");
}

