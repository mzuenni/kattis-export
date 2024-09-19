#include "validate.h"

#include <iostream>
using namespace std;

const int N = 10000, Q = 7;
const std::regex TYPE_REGEX("[?!]", std::regex_constants::optimize);
const std::regex LOWER("[a-z]+", std::regex_constants::optimize);

bool guessedchars[26];

string evaluate(string x, string t, string s) {
	if(t == "?") {
		for(int i = 0; i < 26; ++i) {
			guessedchars[i] = false;
		}
		for(char c : s) {
			guessedchars[c - 'a'] = true;
		}
		vector<int> out;
		for(int i = 0; i < x.size(); ++i) {
			if(guessedchars[x[i] - 'a']) out.push_back(i+1);
		}
		string ans = "";
		ans += to_string(out.size());
		for(int i = 0; i < out.size(); ++i) {
			ans += " " + to_string(out[i]);
		}
		return ans;
	}
	if(t == "!") {
		if(x == s) return "correct";
		if(x != s) return "incorrect";
	}
}

int main(int argc, char **argv) {
	using namespace Interactor;
	Interactor::init(argc, argv);

	string x = testIn.string(1, N+1);
	
	int qc = 0;
	while (true) {
		string t = fromTeam.string(TYPE_REGEX);
		string s = fromTeam.string(LOWER, 1, N+1);

		++qc;

		string ans = evaluate(x, t, s);
		toTeam << ans << endl;
		
		if (ans == "correct") {
		        if(qc > Q) juryOut << "Wrong answer: Too many guesses: " << WA;
			fromTeam.eof();
			juryOut << "Queries used: " << qc << AC;
			break;
		}
	}
}
