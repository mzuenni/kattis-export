#include <cassert>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

void no() {
	cout << "no\n";
	exit(0);
}

bool flip;
void output(string&& str) {
	cout << "yes" << endl;
	if (not flip) {
		cout << str;
		exit(0);
	}
	vector<string> lines = {""};
	for (char c : str)
		if (c == '\n') lines.emplace_back("");
		else lines.back() += c;
	if (lines.back().empty()) lines.pop_back();
	for (size_t j = 0; j < lines[0].size(); j++) {
		for (size_t i = 0; i < lines.size(); i++)
			cout << lines[i][j];
		cout << '\n';
	}
	exit(0);
}

void tile(ostream& out, int w, const vector<string>& s) {
	for (const auto& x : s) {
		for (int i = 0; i < w / x.size(); i++) out << x;
		out << '\n';
	}
}

const vector<string> five = {
	"NNNUU",
	"YWNNU",
	"YWWUU",
	"YYWWL",
	"YLLLL"
};

bool solve(ostream& out, int w, int h) {	
	if (h == 0) return true;
	if (h == 2) {
		if (w == 5) return false;
		out << "PP";
		for (int i = 0; i < w / 5 - 1; i++)
			out << (i % 2 ? "NNNY" : "NNYYYY");
		out << ((w / 5) % 2 ? "PPP" : "PP") << '\n';

		out << "PPP";
		for (int i = 0; i < w / 5 - 1; i++)
			out << (i % 2 ? "NNYYYY" : "NNNY");
		out << ((w / 5) % 2 ? "PP" : "PPP") << '\n';
	} else if (h == 3 or h == 7) {
		tile(out, w, {
			"UUFFP",
			"UFFPP",
			"UUFPP"
		});
		solve(out, w, h - 3);
	} else if (h == 4) {
		tile(out, w, {
			"LNVVV",
			"LNZZV",
			"LNNZV",
			"LLNZZ"
		});
	} else if (h == 6) {
		for (int j = 0; j < 6; j++) {
			for (int i = 0; i < w/5; i++) {
				if (i % 2 ? (j == 0) : (j == 5))
					out << "IIIII";
				else
					out << five[j - (i%2)];
			}
			out << '\n';
		}
	} else {
		tile(out, w, five);
		return solve(out, w, h - 5);
	}

	return true;
}

int main() {
	int h, w;
	cin >> h >> w;
	if ((h * w) % 5) no();
	flip = w % 5;
	if (flip) swap(w, h);
	assert(w % 5 == 0);

	if (h == 1) {
		if (w > 5) no();
		output("IIIII");
	}

	stringstream out;
	if (not solve(out, w, h))
		no();
	output(out.str());
}
