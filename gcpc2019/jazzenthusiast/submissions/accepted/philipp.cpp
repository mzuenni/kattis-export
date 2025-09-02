#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, c;
	cin >> n >> c;

	int seconds = -c * (n-1);
	while(n--) {
		int m, ss; char colon;
		cin >> m >> colon >> ss;
		seconds += 60*m + ss;
	}

	int minutes = seconds / 60;
	seconds %= 60;
	int hours = minutes / 60;
	minutes %= 60;

	cout << hours/10 << hours%10 << ':' << minutes/10 << minutes%10 << ':' << seconds/10 << seconds%10 << endl;
}
