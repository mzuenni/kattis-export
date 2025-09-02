#include <bits/stdc++.h>
#include "validate.h"
#include "board.h"

using namespace std;

board B;

// If set to true, the first seven pieces will be distinct,
// the next seven will be distinct, and so on.
bool use_bag_rng = true;

void print_and_wa(const std::string &msg, ...) {
	judge_message("%s", B.pretty_print().c_str());
	va_list pvar;
	va_start(pvar, msg);
	vreport_feedback(FILENAME_JUDGE_MESSAGE, msg, pvar);
	exit(EXITCODE_WA);
}

pair<int,int> read_placement() {
	int rot, col;
	if (!(author_out >> rot >> col)) {
		print_and_wa("Wrong answer: expected two integers.\n");
	}
	
	if (rot < 0 || rot > 3) {
		print_and_wa("Wrong answer: rotation out of range: %d\n", rot);
	}
	
	// Do not check if position is out of range yet; we will check this when we
	// try to place the piece in order to show more informative output.
	
	return {rot,col};
}

int main(int argc, char **argv) {
	init_io(argc,argv);
	
	int seed;
	judge_in >> seed;
	srand(seed);

	judge_in >> use_bag_rng;

	vector<piece> pieces;

	while (true) {
		if (pieces.empty() || !use_bag_rng) {
			pieces = tetrominoes;
			random_shuffle(begin(pieces), end(pieces));
		}

		piece P = pieces.back();
		pieces.pop_back();
		cout << P.id << endl;
		
		int rot, col;
		tie(rot,col) = read_placement();
		
		if (!B.drop_piece(P, rot, col)) {
			print_and_wa("Wrong answer: invalid placement.\n");
		}

		if (B.completed_row()) {
			break;
		}
	}
	
	// write 'W' to signal the end of the game
	cout << 'W' << endl;

	string junk;
	if (author_out >> junk) {
		print_and_wa("Wrong answer: received more output after the game ended.\n");
	}
	
	judge_message("%sCorrect!\n", B.pretty_print().c_str());
	accept();
}
