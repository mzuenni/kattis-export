#include <bits/stdc++.h>
#include "validate.h"
using namespace std;

int main(int argc, char **argv) {
	init_io(argc,argv);
	
	int height, width, n;
	judge_in >> height >> width >> n;
	
	string first_line;
	judge_ans >> first_line;
	
	bool ok = true;

	if (first_line == "impossible") {
		if (!(author_out >> first_line) || first_line != "impossible")
			wrong_answer("Wrong answer, expected \"impossible\"\n.");
	} else {
		vector<string> a(height);
		for (int i = 0; i < height; i++) {
			if (!(author_out >> a[i]))
				wrong_answer("Expected %d lines, but received %d.\n", height, i);
			if (a[i].size() != width)
				wrong_answer("On line %d: expected width %d, but received %d.\n", i, width, a[i].size());
			for (char c: a[i])
				if (c < 'A' || c > 'Z')
					wrong_answer("On line %d: illegal character: %c.\n", i, c);
		}
		
		string s;
		while (judge_in >> s) {
			bool found = any_of(begin(a), end(a), [&](string t) {
				return t.find(s) != string::npos;
			});
			if (!found) {
				ok = false;
				judge_message("Word \"%s\" does not occur in team's output.\n", s.c_str());
			}
		}
	}

	string junk;
	if (author_out >> junk)
		wrong_answer("Found trailing characters.\n");
	
	if (ok)
		accept();
	else
		wrong_answer("");
}

