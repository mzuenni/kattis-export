#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 1000;

int main() {
	vector<pair<int, int>> p(5);
	int res = 0;
	for (int i = 0; i < 5; i++) cin >> p[i].first >> p[i].second;

	auto move_points = [&](vector<pair<int, int>> &p) {
		sort(p.begin(), p.end());
		int nxt = 0;
		while (nxt < 5 && p[nxt] == p[0]) nxt++;
		if (nxt < 5 && p[0].first < p[nxt].first) {
			res += p[nxt].first - p[0].first;
			for (int i = 0; i < nxt; i++)
				p[i].first = p[nxt].first;
		}
		int prev = 4;
		while (prev >= 0 && p[prev] == p[4]) prev--;
		if (prev >= 0 && p[4].first > p[prev].first) {
			res += p[4].first - p[prev].first;
			for (int i = 4; i > prev; i--)
				p[i].first = p[prev].first;
		}
		return p[4].first - p[0].first;
	};

	auto has_interior = [&](vector<pair<int, int>> &p) {
		int lox = N+1, hix = -1, loy = N+1, hiy = -1;
		for (int i = 0; i < 5; i++) {
			lox = min(lox, p[i].first);
			hix = max(hix, p[i].first);
			loy = min(loy, p[i].second);
			hiy = max(hiy, p[i].second);
		}
		for (int i = 0; i < 5; i++) {
			if (p[i].first > lox && p[i].first < hix && p[i].second > loy && p[i].second < hiy) {
				return true;
			}
		}
		return false;
	};

	move_points(p);
	for (int i = 0; i < 5; i++) swap(p[i].first, p[i].second);
	move_points(p);
	for (int i = 0; i < 5; i++) swap(p[i].first, p[i].second);
	int dx = move_points(p);
	for (int i = 0; i < 5; i++) swap(p[i].first, p[i].second);
	int dy = move_points(p);
	res += 2*(dx + dy);
	if (has_interior(p)) res += min(dx, dy);

	cout << res << '\n';

	return 0;
}
