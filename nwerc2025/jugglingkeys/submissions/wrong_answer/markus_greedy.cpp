#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdint>
#include <set>
#include <map>
using namespace std;

vector<int64_t> tree;

void update(int i, int64_t val) {
	for (i++; i < (int)tree.size(); i += i & -i) tree[i] += val;
}

void init(int n) {
	tree.assign(n + 1, 0);
}

int64_t prefix_sum(int i) {
	int64_t sum = 0;
	for (i++; i > 0; i -= i & -i) sum += tree[i];
	return sum;
}

struct event {
	uint64_t idx;
	uint64_t time;
	uint64_t t2;
	bool leaving;
};

bool operator<(const event &l, const event &r) {
	return l.time < r.time;
}

int main() {
	int64_t n, k, q;
	cin >> n >> k >> q;

	set<uint64_t> times;
	
	vector<event> events(2 * q);
	for (uint64_t i = 0; i < q; ++i) {
		uint64_t ni, li, ri;
		cin >> ni >> li >> ri;
		events[2 * i] = event { i, li, ri, true };
		events[2 * i + 1] = event { i, ri, li, false };
		times.insert(li);
		times.insert(ri);
	}

	map<uint64_t, uint64_t> rev;

	for (const uint64_t &t : times) {
		uint64_t next = rev.size();
		rev[t] = next;
	}

	init(rev.size());

	sort(events.begin(), events.end());

	vector<bool> needs_key(q);

	uint64_t in_apartment = n;
	for (uint64_t i = 0; i < 2 * q; ++i) {
		if (events[i].leaving) {
			--in_apartment;
		} else {
			if (in_apartment == 0) {
				int64_t keys = k - prefix_sum(rev[events[i].t2]);
				if (keys <= 0) {
					cout << "impossible" << endl;
					return 0;
				}
				update(rev[events[i].t2], 1);
				update(rev[events[i].time], -1);
				needs_key[events[i].idx] = true;
			}
			++in_apartment;
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
