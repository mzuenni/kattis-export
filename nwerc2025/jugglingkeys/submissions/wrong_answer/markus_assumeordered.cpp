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

	vector<event> events1(q), events2(q);
	vector<event> events;

	for (uint64_t i = 0; i < q; ++i) {
		uint64_t ni, li, ri;
		cin >> ni >> li >> ri;
		events1[i] = event { i, li, true };
		events2[i] = event { i, ri, false };
	}

	sort(events2.begin(), events2.end());
	merge(events1.begin(), events1.end(), events2.begin(), events2.end(), back_inserter(events));

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
