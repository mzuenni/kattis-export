#include<iostream>

using namespace std;

int main()
{
    for(int i = 0; i < 7; ++i) {
	cout << "? " << (char) ('a' + i) << endl;
	int n;
	cin >> n;
	for(int i = 0; i < n; ++i) {
	    int a;
	    cin >> a;
	}
    }
}
