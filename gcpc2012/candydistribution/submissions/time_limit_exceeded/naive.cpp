// @EXPECTED_RESULTS@: TIMELIMIT

#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

ll gcd(ll a, ll b) {
	if (b == 0) {
		return a;
	}
	if (b > a) {
		return gcd(b, a);
	}
	return gcd(b, a%b);
}

int main(int argc, char **argv) {
	int numCases;
	scanf("%d", &numCases);

	while (numCases --> 0) {
		long long K, C;
		scanf("%lld%lld", &K, &C);
		if (C == 1) {
			printf("%lld\n", K + 1);
			continue;
		} else if (K == 1) {
			puts("1");
			continue;
		}

		ll ggt = gcd(K, C);

		if (ggt != 1LL) {
			puts("IMPOSSIBLE");
		} else {
			ll i;
			for (i = 1; (i * C) % K != 1; i++) { }
			printf("%lld\n", i);
		}
	}

	return 0;
}
