#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdint>
using namespace std;

struct event {
	uint64_t idx;
	uint64_t time;
	bool leaving;
};

bool operator<(const event &l, const event &r) {
	return l.time < r.time;
}

int main() {
	uint64_t n, k, q;
	cin >> n >> k >> q;

	vector<event> events(2 * q);
	for (uint64_t i = 0; i < q; ++i) {
		uint64_t ni, li, ri;
		cin >> ni >> li >> ri;
		events[2 * i] = event { i, li, true };
		events[2 * i + 1] = event { i, ri, false };
	}

	sort(events.begin(), events.end());

	vector<bool> needs_key(q);

	uint64_t in_apartment = n;
	for (uint64_t i = 0; i < 2 * q; ++i) {
		if (events[i].leaving) {
			--in_apartment;
		} else {
			if (in_apartment == 0) {
				needs_key[events[i].idx] = true;
			}
			++in_apartment;
		}
	}

	uint64_t keys = k;
	for (uint64_t i = 0; i < 2 * q; ++i) {
		if (!needs_key[events[i].idx]) {
			continue;
		}

		if (events[i].leaving) {
			if (keys == 0) {
				cout << "IMPOSSIBLE" << endl;
				return 0;
			}
			--keys;
		} else {
			++keys;
		}
	}

	for (uint64_t i = 0; i < q; ++i) {
		if (needs_key[i]) {
			cout << "1";
		} else {
			cout << "0";
		}
	}
	cout << endl;
}
