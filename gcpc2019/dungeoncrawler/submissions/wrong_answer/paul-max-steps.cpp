#include <bits/stdc++.h>
using namespace std;

const int STEPS = 250'000;

int main() {
	int n; cin >> n;
	string line;
	for (int i = 0; i <= n; i++) getline(cin,line);
	
	for (int i = 0; i < STEPS; i++) {
		string name, edges;
		cin >> name >> edges;
		cout << "W " << edges[0] << endl;
	}
	cout << "R no" << endl;
}
