#include <bits/stdc++.h>
using namespace std;

long long x[1000000], y[1000000];

int main () {
	int n; cin >> n;
	for (int i = 0; i < n; i++) cin >> x[i] >> y[i];

	long long a = 0, b = 0;
	for (int i = 1; i <= n; i++) {
		a += x[i%n]*y[i-1] - x[i-1]*y[i%n];
		b += __gcd(abs(x[i%n]-x[i-1]),abs(y[i%n]-y[i-1]));
	}
	
	cout << (abs(a)-b+2)/2 << endl;	
}
