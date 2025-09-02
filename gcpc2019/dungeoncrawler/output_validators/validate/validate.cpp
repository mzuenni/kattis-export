#include <bits/stdc++.h>
#include "validate.h"
#include "graph.h"

using namespace std;

#define TEST judge_in
#define RESULT judge_ans
#define TOTEAM cout
#define FROMTEAM author_out

const int MAX_MOVES = 250000;

void genNames(int req) {
	string first = "aaaaaaaaaa";
	while (artifacts.size() < req) {
		artifacts.push_back(first);
		int k = first.size()-1;
		first[k] ++;
		while (first[k] > 'z') {
			first[k] = 'a';
			first[--k]++;
		}
	}
}

int main(int argc, char **argv) {
	init_io(argc,argv);
	
	srand(1332);
	string seperator;
	// we have this just to increase readability in testcases
	// and for special graphs
	TEST >> seperator;
	
	Graph gLevel;
	if (seperator == "--Level:infinite--") {
		int OVERSIZE = 1000000; // only 250*10^3 steps are allowed
		genNames(OVERSIZE);
		gLevel = Graph(OVERSIZE, 0);
		for (int i = 0; i < OVERSIZE; i++) {
			gLevel.adj[i][i%2] = (i + 1) % OVERSIZE;
			gLevel.adj[i][(i+1)%2] = (i - 1+OVERSIZE) % OVERSIZE;
		}
	} else {
		// Level in which the player finds himself
		// nodes, current position
		int n, c;
		TEST >> n >> c;
		genNames(n + 10);
		gLevel = Graph(n, c-1);
		for (int i = 0; i < n; i++) {
			int k;
			TEST >> k;
			for (int j = 0; j < k; j++) {
				char t;
				int m;
				TEST >> t >> m;
				gLevel.adj[i][t-'A'] = m-1;
			}
		}
	}
	gLevel.initS(); // setup internal data structures
	TEST >> seperator; // we have this just to increase readability in testcases
	
	int n;
	// existing fixed map presented to the user
	// we dont need this, we just forward it
	TEST >> n;
	TOTEAM << n << endl;
	for (int i = 0; i < n; i++) {
		int k;
		TEST >> k;
		TOTEAM << k;
		for (int j = 0; j < k; j++) {
			char t;
			int m;
			TEST >> t >> m;
			TOTEAM << " " << t << " " << m;
		}
		TOTEAM << endl;
	}
	TOTEAM.flush();
	// exactly end of test input
	assert(TEST);
	TEST >> seperator;
	assert(!TEST);
	
	char res;
	RESULT >> res; // res = {'N', 'U', 'A'} = No/Unique/Ambigious
	vector<int> mapping; // m[i] = j => i in level corresponds to j in map
	if (res == 'U') { // unique solution -> read the solution
		mapping.resize(n);
		for (int i = 0; i < n; i++) {
			RESULT >> mapping[i]; // careful 1-indexed
		}
	}
	// exactly end of answer
	assert(RESULT);
	RESULT >> seperator;
	assert(!RESULT);
	
	int moves = 0;
	judge_message("Expected answer is %c\n", res);
	while (true) {
		gLevel.printCurrent(TOTEAM);
		TOTEAM.flush();
		char response;
		if (!(FROMTEAM >> response)) {
			wrong_answer("Expected response char\n");
		}
		
		if (response == 'W') {
			moves++;
			if (moves > MAX_MOVES) {
				wrong_answer("Too many moves\n");
			}
			char move;
			if (!(FROMTEAM >> move)) {
				wrong_answer("Expected move char\n");
			}
			
			pair<int, string> v = gLevel.go(move);
			if (!v.first) {
				wrong_answer(v.second + "\n");
			}
		} else if (response == 'R') {
			string answer;
			if (!(FROMTEAM >> answer)) {
				wrong_answer("Expected answer string\n");
			}
			if (res == 'A') {
				if (answer == "ambiguous") {
					judge_message("Ambigious - Correct\n");
					break;
				} else {
					wrong_answer("Expected ambiguous, but got %s\n", answer.c_str());
				}
			} else if (res == 'N') {
				if (answer == "no") {
					judge_message("Not identical - Correct\n");
					break;
				} else {
					wrong_answer("Expected not identical, but got %s\n", answer.c_str());
				}
			} else { // expecting correct
				int curPosInMap_real = mapping[gLevel.current];
				int curPosInMap_team = -1;
				try {
					curPosInMap_team = stoi(answer);
				} catch (const invalid_argument & e) {
					wrong_answer("Expected unique at %d (is %d in level), but got %s\n", curPosInMap_real, gLevel.current+1, answer.c_str());
				} catch (const out_of_range & e) {
					wrong_answer("Expected unique at %d (is %d in level), but got %s\n", curPosInMap_real, gLevel.current+1, answer.c_str());
				}
				if (curPosInMap_team == curPosInMap_real) {
					judge_message("Unique - Correct. Used %d steps\n", moves);
					break;
				} else {
					wrong_answer("Expected unique at %d (is %d in level), but got %s\n", curPosInMap_real, gLevel.current+1, answer.c_str());
				}
			} 
		} else {
			wrong_answer("Not a valid response token\n");
		}
	}

	string junk;
	if (FROMTEAM >> junk) {
		wrong_answer("BUT received more output after the game ended.\n");
	}
	accept();
}
