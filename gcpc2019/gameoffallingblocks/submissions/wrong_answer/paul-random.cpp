#include <bits/stdc++.h>
using namespace std;

int main() {
	char piece;
	while (cin >> piece) {
		if (piece == 'W') break;
		
		cout << rand()%4 << " " << 1 + rand()%8 << endl;
	}
}

