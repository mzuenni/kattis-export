#include <iostream>

#define FOR(i,a,b) for(int i = (a); i < (b); i++)

using namespace std;

int main(){
	int n; cin >> n;
	int x = 1;
	FOR(i,0,n) x *= 8;
	cout << x << endl;
}
