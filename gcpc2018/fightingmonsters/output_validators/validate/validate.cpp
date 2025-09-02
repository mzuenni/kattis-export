#include <bits/stdc++.h>
#include "validate.h"
using namespace std;

int main(int argc, char **argv) {
	init_io(argc,argv);
	
	int n; judge_in >> n;
	vector<int> v(n);
	for (int i = 0; i < n; i++) {
		judge_in >> v[i];
	}

	if (judge_ans.peek() == 'i') {
		string s;
		if (!(author_out >> s) || s != "impossible") {
			wrong_answer("Wrong answer: expected 'impossible'.\n");
		}
	} else {
		int i, j;
		if (!(author_out >> i >> j)) {
			wrong_answer("Wrong answer: expected two indices.\n");
		}
		if (i < 1 || i > n || j < 1 || j > n) {
			wrong_answer("Wrong answer: index out of range.\n");
		}
		if (i == j) {
			wrong_answer("Wrong answer: the two indices are equal.\n");
		}
		
		i--, j--;

		bool ok = false;
		for (int a = 1, b = 1; b <= 1e7; a += b, swap(a,b)) {
			ok = ok || (v[i] == a && v[j] == b);
		}
		if (!ok) {
			wrong_answer("Wrong answer: the fight does not lead to the desired result.\n");
		}
	}
	
	string junk;
	if (author_out >> junk) {
		wrong_answer("Wrong answer: found trailing junk.\n");
	}

	accept();
}
