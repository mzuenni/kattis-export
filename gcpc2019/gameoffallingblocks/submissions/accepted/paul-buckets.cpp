#include <bits/stdc++.h>
using namespace std;

#define rotate asdf

map<char,int> width = {{'I',1},{'J',3},{'L',3},{'O',2},{'S',2},{'T',2},{'Z',2}};
map<char,int> rotate = {{'I',1},{'J',2},{'L',2},{'O',0},{'S',1},{'T',1},{'Z',1}};

int main() {
	char piece;
	int x = 1;
	while (cin >> piece) {
		if (piece == 'W') break;
		
		cout << rotate[piece] << " ";

		int c = -1;
		if (width[piece] == 1) c = 7;
		else if (width[piece] == 3) c = 8;
		else c = x, x = (x+2)%6;
		cout << c << endl;
	}
}

