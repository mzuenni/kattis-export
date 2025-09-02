#include <iostream>
#include <algorithm>

using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)

pair<int,string> em[1000000];

int main(){
	int n,d,k; cin >> n >> d >> k;
	FOR(i,0,n) cin >> em[i].second >> em[i].first;
	sort(em,em+n);
	reverse(em,em+n);
	// determine kk
	int kk = 0, r = 0;
	while (kk < k && r < d)
		r += em[kk++].first;
	if (r < d) cout << "impossible" << endl;
	else {
		cout << kk << endl;
		FOR(i,0,kk) cout << em[i].second << ", YOU ARE FIRED!" << endl;
	}
	return 0;
}
