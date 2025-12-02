#include <iostream>
#include <numeric>
#include <math.h>
using ll = long long;
using namespace std;

ll n;

double f(ll x) {
	double chord = 2*sin(M_PI * double(x)/double(n));
	return n / gcd(n, x) * chord;
}

int main() {
	cin >> n;
	ll x = 0;
	for (ll b = (1LL << 34); b; b /= 2) {
		if (x+b > n/2) continue;
		if (f(x+b) - f(x+b-1) > 0) x += b;
	}
	cout << x << endl;
}
