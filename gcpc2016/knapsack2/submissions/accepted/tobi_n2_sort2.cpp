#include <bits/stdc++.h>

using namespace std;
#define FOR(i,a,b) for (long long i=(a); i<(b); i++)
long long K, N, items[100];
map<int, long long> possible {make_pair(0,0)};
vector<long long> q {0};

int main() {
	cin >> N >> K;
	FOR(i, 0, N) cin >> items[i];
	sort(items, items + N, greater<long long>());
	FOR(qC, 0, q.size()) FOR(i, 1, N) {
		long long next = q[qC] + items[i], nextMod = next % items[0];
		if (next <= K && (possible.count(nextMod) == 0 || possible[nextMod] > next)) {
			possible[nextMod] = next;
			q.push_back(next);
		}
	}
	cout << (possible.count(K%items[0]) > 0 ? "possible" : "impossible") << endl;

	return 0;
}
