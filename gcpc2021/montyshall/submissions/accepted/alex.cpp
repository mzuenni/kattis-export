#include <algorithm>
#include <iomanip>
#include <iostream>

using namespace std;

int main() {
	long long d,s,e;
	cin >> d >> s >> e;
	long long overflow = max(2 * s + e - d, 0LL);
	long double in_overflow = ((long double) overflow) / ((long double) d);
	d -= overflow;
	s -= overflow;
	long double bad_first_select = ((long double) s) / ((long double) d);
	long double good_second_select = ((long double) s) / ((long double) (d - e - s));
	long double bad_select = bad_first_select + (1 - bad_first_select) * (1 - good_second_select);
	cout << setprecision(8) << fixed << 1 - ((1 - in_overflow) * bad_select) << endl;
}
