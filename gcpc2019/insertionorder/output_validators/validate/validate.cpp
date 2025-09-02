#include <bits/stdc++.h>
#include "validate.h"
using namespace std;

int find_depth(vector<int> perm) {
	int n = perm.size();
	
	map<int,int> h;
	h[0] = 0; h[n+1] = 0;

	int res = 0;
	for (int x: perm) {
		auto it = h.lower_bound(x);
		int hx = max(it->second, prev(it)->second) + 1;
		h[x] = hx;
		res = max(res, hx);
	}
	return res;
}

int main(int argc, char **argv) {
	init_io(argc,argv);
	
	int n, k;
	judge_in >> n >> k;
	
	string first_token;
	judge_ans >> first_token;

	if (first_token == "impossible") {
		author_out >> first_token;
		if (first_token != "impossible") {
			wrong_answer("Wrong answer: expected 'impossible'\n.");
		}
	} else {
		vector<int> perm(n);
		for (int i = 0; i < n; i++) {
			string str;
			if (!(author_out >> perm[i])) {
				author_out.clear();
				if (author_out >> str && str == "impossible") {
					wrong_answer("Wrong answer: received 'impossible', but a solution exists.\n");
				}
				wrong_answer("Wrong answer: expected an integer.\n");
			}
			if (perm[i] < 1 || perm[i] > n) {
				wrong_answer("Wrong answer: integer out of range: %d\n", perm[i]);
			}
		}
		
		vector<int> perm_copy = perm;
		sort(begin(perm_copy), end(perm_copy));
		if (unique(begin(perm_copy), end(perm_copy)) != end(perm_copy)) {
			wrong_answer("Wrong answer: not a permutation.\n");
		}

		int d = find_depth(perm);
		if (d != k) {
			wrong_answer("Wrong answer: the given permutation gives a tree of depth %d.\n", d);
		}
	}

	string junk;
	if (author_out >> junk) {
		wrong_answer("Wrong answer: found trailing output.\n");
	}

	accept();
}

