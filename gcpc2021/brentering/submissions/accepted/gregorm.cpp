// Author: Gregor Matl
#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string subject;
	cin >> subject;
	
	cout << subject.substr(0, subject.find_last_of("aeiou") + 1) << "ntry" << endl;
}
