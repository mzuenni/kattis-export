#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

int main(void) {
	int N;
	ll K, a[100], minv[200000];
	scanf("%d%lld", &N, &K);
	for (int i = 0; i < N; ++i) scanf("%lld", a+i);
	fill(minv, minv+a[0], K+1);
	minv[K % a[0]] = 0;
	for (int i = 1; i < N; ++i)
		for (int t = 1; t < a[0]; t *= 2)
			for (int x = 0; x < a[0]; ++x)
				minv[x] = min(minv[x], minv[(x+t*a[i]) % a[0]] + t*a[i]);
	printf("%s\n", minv[0] <= K ? "possible" : "impossible");
	return 0;
}
