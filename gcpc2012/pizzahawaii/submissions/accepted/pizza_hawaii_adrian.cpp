// @EXPECTED_RESULTS@: CORRECT
#include <string>
#include <map>
#include <sstream>
#include <iostream>
using namespace std;

typedef long long LL;

int main() {
	string line;
	bool first = true;
	getline(cin,line); // skip number of testcases
	while(getline(cin, line)) {
		if (!first) cout << endl;
		else first = false;
		istringstream istr(line);
		int n;
		istr >> n;
		map<string, LL> language1, language2;
		for (int i=0; i<n; ++i) {
			getline(cin, line); // skip the pizza name
			getline(cin, line);
			istringstream istr2(line);
			int m;
			string word;
			istr2 >> m;
			for (int j=0; j<m; ++j) {
				istr2 >> word;
				language1[word] += 1LL<<i;
			}
			getline(cin, line);
			istringstream istr3(line);
			istr3 >> m;
			for (int j=0; j<m; ++j) {
				istr3 >> word;
				language2[word] |= 1LL<<i;
			}
		}
		for (map<string, LL>::iterator it=language1.begin(); it!=language1.end(); ++it)
			for (map<string, LL>::iterator it2=language2.begin(); it2!=language2.end(); ++it2) {
				if (it->second == it2->second)
					cout << "(" << it->first << ", " << it2->first << ")"	<< endl;
			}
	}
	return 0;
}
