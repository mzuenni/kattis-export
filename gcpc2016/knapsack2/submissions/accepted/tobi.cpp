#include <bits/stdc++.h>

using namespace std;
#define FOR(i,a,b) for (long long i=(a); i<(b); i++)
long long K, N, items[20];
bool visited[200005];
set<long long> q {0};

int main() {
	cin >> N >> K;
	FOR(i, 0, N) cin >> items[i];
	while (q.size() > 0) {
		long long cur = *q.begin();
		q.erase(cur);
		if (visited[cur % items[0]]) continue;
		visited[cur % items[0]] = true;
		FOR(i, 1, N) {
			long long next = cur + items[i], nextMod = next % items[0];
			if (next <= K && !visited[nextMod]) q.insert(next);
		}
	}
	cout << (visited[K%items[0]] > 0 ? "possible" : "impossible") << endl;

	return 0;
}
