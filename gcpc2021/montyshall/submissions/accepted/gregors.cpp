#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

int main()
{
	double d,s,e; cin >> d >> s >> e;
	double k = max(0.0, 2 * s + e - d);
	double p = k/d + (d-k)/d * (d-s)/(d-k) * (s-k)/(d-s-e);
	cout << setprecision(10) << p << endl;
}
