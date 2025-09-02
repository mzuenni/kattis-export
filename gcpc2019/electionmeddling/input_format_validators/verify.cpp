#include <bits/stdc++.h>

#define FOR(i,a,b) for (int i = (a); i < (b); i++)

using namespace std;

int main(){
	int w,p; cin >> w >> p;
	FOR(i,0,w) {
		bool zero = true;
		FOR(j,0,p) {
			int x; cin >> x;
			zero &= !x;
		}
		if (zero){
			cerr << "Number of votes in ward "<< i+1 << "is zero" << endl;
			return 1;
		}
	}

	return 42;
}
