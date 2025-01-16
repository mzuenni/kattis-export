#include "validation.h"
#include <vector>
using namespace std;
using i64 = long long;


const int MAX_N = 50000;
const int MAX_GAMES = 100000;

int d[7];

int main(int argc, char **argv) {
	ifstream in(argv[1]);
	InputValidator v(argc, argv);


	int n = v.read_integer("n", 1, MAX_N);
	v.newline();

	int matchcount = 0;

	// read daysizes
	for (int i = 0; i < 7; i++) {
		d[i] = v.read_integer("d_i", 1, MAX_GAMES);
		matchcount += d[i];
		if(i < 7 - 1) v.space();
	}
	v.check(matchcount <= MAX_GAMES, "too many matches");
	v.newline();

	// read predictions
	for (int p = 0; p < n; p++) {
		for(int i = 0; i < 7; i++){
			int pred = v.read_integer("p", -d[i], d[i]);
			v.check(pred != 0, "prediction can not be zero");
			if(i < 7 - 1) v.space();
		}
		v.newline();
	}

	for(int i = 5; i < 7; i++){
		int pred = v.read_integer("p", -d[i], d[i]);
		v.check(pred != 0, "prediction can not be zero");
		if(i < 7 - 1) v.space();
	}
	v.newline();
}

