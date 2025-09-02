#include <bits/stdc++.h>
#include "validate.h"
using namespace std;

const string impossible = "impossible";
const long long addformod = 10000000000000;

int main(int argc, char **argv) {
	init_io(argc,argv);

	string res;
	judge_ans >> res;
	if(res == impossible) {
		string teamres;
		author_out >> teamres;
		if(teamres != impossible) {
			wrong_answer("WA: supposed to be impossible, team says otherwise");
		}
	} else {
		long long x[2], y[2], d[2];
		for(int i = 0; i < 2; i++) {
			judge_in >> x[i] >> y[i] >> d[i];
		}
		long long teamx, teamy;
		author_out >> teamx >> teamy;
		if(author_out.fail()) {
			wrong_answer("WA: team did not output two long long integers");
		}
		for(int i = 0; i < 2; i++) {
			if(abs(teamx - x[i]) + abs(teamy - y[i]) > d[i]
			|| (x[i] + y[i] + d[i] + addformod) % 2ll != (teamx + teamy + addformod) % 2ll) {
				wrong_answer("WA: bad coordinates");
			}
		}
	}

	string trailing;
	if(author_out >> trailing) {
		wrong_answer("WA: trailing output");
	}

	accept();
}
