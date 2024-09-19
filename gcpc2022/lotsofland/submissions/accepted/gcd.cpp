#include <bits/stdc++.h>
using namespace std;

int main() {
	int w, h, n;
	cin >> h >> w >> n;
	if(w * h % n) cout << "impossible" << endl;
	else{
		int ww = w / gcd(w, n);
		int hh = w * h / n / ww;
		for(int i=0; i<h; i++) {
			for(int j=0; j<w; j++){
				cout << char('A' + (i / hh) * (w / ww) + (j / ww));
			}
			cout << endl;
		}
	}
}