#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	cout << fixed << setprecision(10);

	double d, s, e;
	cin >> d >> s >> e;
	double always_select = max(0.0, 2 * s + e - d);

	// probability to win with both choices
	double p_default = always_select / d;

	d -= always_select;
	s -= always_select;

	// probability to win with only the first choice
	double p_first = s / d;

	// probability to win with only the second choice
	double p_second = s / (d - s - e);

	cout << p_default + (1.0 - p_default) * (1.0 - p_first) * p_second << '\n';
}
