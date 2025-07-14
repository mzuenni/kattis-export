#include <bits/stdc++.h>
using namespace std;

bool is_valid(int work_time, int break_time) {
	if (work_time > 600) return false;
	if (work_time > 540) return break_time >= 45;
	if (work_time > 360) return break_time >= 30;
	return true;
}

int main() {
	int t;
	cin >> t;
	for (int break_time = 0; break_time <= t; break_time++) {
		if (is_valid(t - break_time, break_time)) {
			cout << break_time << endl;
			return 0;
		}
	}
}
