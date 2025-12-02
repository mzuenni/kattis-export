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
	vector<int> keys_used(2 * q);
	vector<int> in_apartment(2 * q);
	vector<int> leavei(q);

	int i = 0;
	while (i < 2 * q) {
		int keys_used_before = i == 0 ? 0 : keys_used[i - 1];
		int in_apartment_before = i == 0 ? n : in_apartment[i - 1];

		if (events[i].leaving) {
			leavei[events[i].idx] = i;
			if (needs_key[events[i].idx]) {
				keys_used[i] = keys_used_before + 1;
				if (keys_used_before + 1 > k) {
					cout << "impossible" << endl;
					return 0;
				}
			} else {
				keys_used[i] = keys_used_before;
			}
			in_apartment[i] = in_apartment_before - 1;
		} else {
			if (in_apartment_before == 0 && !needs_key[events[i].idx]) {
				needs_key[events[i].idx] = true;
				i = leavei[events[i].idx];
				continue;
			}
			in_apartment[i] = in_apartment_before + 1;
			if (needs_key[events[i].idx]) {
				keys_used[i] = keys_used_before - 1;
			} else {
				keys_used[i] = keys_used_before;
			}
		}
		++i;
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
