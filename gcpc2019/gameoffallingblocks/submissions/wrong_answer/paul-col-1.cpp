#include <bits/stdc++.h>
using namespace std;

#define rotate asdf

map<char,int> width = {{'I',1},{'J',3},{'L',3},{'O',2},{'S',2},{'T',2},{'Z',2}};
map<char,int> rotate = {{'I',1},{'J',2},{'L',2},{'O',0},{'S',1},{'T',1},{'Z',1}};

int main() {
	char piece;
	int x = 0;
	while (cin >> piece) {
		if (piece == 'W') break;
		
		cout << rotate[piece] << " ";
		
		int nx = x + width[piece];

		if (nx <= 8 || nx == 10) {
			cout << x+1 << endl;
			x = nx;
		} else {
			cout << 1 << endl;
		}
	}
}

