#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef struct parcel {
	parcel *succ;
	parcel *pred;
	long long tracking;
} parcel;

int main() {
	long long n, s1, s2;
	cin >> n >> s1 >> s2;
	vector<parcel> parcels(n + 3);
	parcel *before = &parcels[n + 1];
	before->tracking = n + 1;
	parcel tmp_tops;
	tmp_tops.tracking = -1;
	while(s1--) {
		long long num;
		cin >> num;
		parcel *this_parcel = &parcels[num];
		before->succ = this_parcel;
		this_parcel->pred = before;
		this_parcel->tracking = num;
		before = this_parcel;
	}
	before->succ = &tmp_tops;
	tmp_tops.pred = before;
	before = &tmp_tops;
	while(s2--) {
		long long num;
		cin >> num;
		parcel *this_parcel = &parcels[num];
		before->succ = this_parcel;
		this_parcel->pred = before;
		this_parcel->tracking = num;
		before = this_parcel;
	}
	before->succ = &parcels[n + 2];
	parcels[n + 2].pred = before;
	parcels[n + 2].tracking = n + 2;

	long long on_top = 1;
	parcel *tops = &tmp_tops;

	for(long long i = 1; i <= n; ++i) {
		if(tops->pred->tracking == 0 || tops->succ->tracking == 0)
			++on_top;
		tops->pred->succ = tops->succ;
		tops->succ->pred = tops->pred;
		tops = &parcels[i];
	}
	cout << on_top << endl;
	return 0;
}
