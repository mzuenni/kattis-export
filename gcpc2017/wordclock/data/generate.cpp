#include <bits/stdc++.h>
using namespace std;

random_device rd;
uniform_int_distribution<char> dis('A','Z');

int rand_int(int n) {
	return uniform_int_distribution<int>(0,n-1)(rd);
}

string rand_str(int n, char cmax = 'Z') {
	string s(n,' ');
	for (char &c: s) {
		do c = dis(rd); while (c > cmax);
	}
	return s;
}

int main() {
	int n = 18, h = 4, w = 14;
	char cmax; cin >> cmax;
	cout << h << " " << w << " " << n << endl;
	vector<string> a(h);
	for (int i = 0; i < h; i++) a[i] = rand_str(w,cmax);
	
	vector<string> t;

	for (int i = 0; i < h; i++) {
		int k = (i+1)*n/h - i*n/h;
		
		for (int j = 0; j < k; j++) {
			int x = max(0,j*w/k - rand_int(3));
			int y = min(w, (j+1)*w/k + rand_int(3));
			t.push_back(a[i].substr(x,y-x));
		}
	}

	assert(t.size() == n);
	shuffle(begin(t), end(t), rd);
	for (int i = 0; i < n; i++) {
		cout << t[i] << " \n"[i+1==n];
	}
}
