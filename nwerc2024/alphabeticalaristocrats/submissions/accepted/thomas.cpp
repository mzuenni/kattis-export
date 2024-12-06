// Author: Thomas Beuman

#include <iostream>
#include <map>
#include <regex>
#include <string>
using namespace std;

const int NMAX = 1000;
const int LENMAX = 50;

string Names[NMAX];
map<string,string> NameMap;

int main()
{
	int n;
	scanf("%d\n", &n);
	for (int i = 0; i < n; i++)
		getline(cin, Names[i]);
	regex rgx("[A-Z].+");
	for (int i = 0; i < n; i++) {
		smatch matches;
		regex_search(Names[i], matches, rgx);
		string toSort = *matches.begin();
		NameMap[toSort] = Names[i];
	}
	for (auto it = NameMap.begin(); it != NameMap.end(); it++)
		printf("%s\n", (it->second).c_str());
	return 0;
}
