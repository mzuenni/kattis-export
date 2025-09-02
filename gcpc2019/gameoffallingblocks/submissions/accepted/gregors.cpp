#include <iostream>
#include <map>
#include <vector>
using namespace std;

map<char,int> piece = {{'I',0},{'J',1},{'L',2},{'O',3},{'S',4},{'T',5},{'Z',6}};;
vector<int> rot = {1,2,2,0,1,2,1};
vector<int> w = {1,3,3,2,2,3,2};

int main()
{
	int wastePos = 1;
	int pos = 1;
	while(true)
	{
		char c; cin >> c;
		if (c == 'W')
			break;
		int t = piece[c];
		cout << rot[t] << " ";
		if (pos + w[t] <= 11 && pos + w[t] != 10)
		{
			cout << pos << endl;
			pos += w[t];
		}
		else
		{
			if (wastePos + w[t] > pos)
				wastePos = 1;
			cout << wastePos << endl;
			wastePos += w[t];
		}
		cout << flush;
	}
}
