#include <bits/stdc++.h>
using namespace std;

int dorandom(int x) {
	int limit = max(x-2, 1);
	return rand() % limit + 1;
}

int main() {
	srand(5);
	int x = 0;
	char piece;
	while(cin >> piece, piece != 'W') {
		if(piece == 'I') {
			cout << "1 " << ++x << endl;
		} else if(piece == 'J') {
			if(x <= 7) {
				cout << "2 " << x+1 << endl;
				x += 3;
			} else {
				cout << "3 " << dorandom(x) << endl;
			}
		} else if(piece == 'L') {
			if(x <= 7) {
				cout << "2 " << x+1 << endl;
				x += 3;
			} else {
				cout << "1 " << dorandom(x) << endl;
			}
		} else if(piece == 'O') {
			if(x <= 8) {
				cout << "0 " << x+1 << endl;
				x += 2;
			} else {
				cout << "0 " << dorandom(x) << endl;
			}
		} else if(piece == 'S') {
			if(x <= 8) {
				cout << "1 " << x+1 << endl;
				x += 2;
			} else {
				cout << "1 " << dorandom(x) << endl;
			}
		} else if(piece == 'T') {
			if(x <= 8) {
				if(x % 2) {
					cout << "2 " << x+1 << endl;
					x += 3;
				} else {
					cout << "3 " << x+1 << endl;
					x += 2;
				}
			} else {
				cout << "3 " << dorandom(x) << endl;
			}
		} else {
			if(x <= 8) {
				cout << "1 " << x+1 << endl;
				x += 2;
			} else {
				cout << "1 " << dorandom(x) << endl;
			}
		}
	}
}
