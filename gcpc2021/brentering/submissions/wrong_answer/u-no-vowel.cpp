#include <iostream>
#include <string>
using namespace std;

int main()
{
	string s; cin >> s;
	int p = s.find_last_of("aeio");
	cout << s.substr(0,p+1) << "ntry" << endl;
}

