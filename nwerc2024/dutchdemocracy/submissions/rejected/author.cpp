// @EXPECTED_RESULTS@: WRONG_ANSWER, RUN_TIME_ERROR
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
using namespace std;

const int nmax = 60;
const int pmax = 100000;

int P[nmax];
long long A[nmax*pmax/2+1];

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &P[i]);

	sort(P, P+n, greater<int>());
	int s = 0;
	for (int i = 0; i < n; i++)
		s += P[i];

	memset(A, 0, sizeof(A));
	A[0] = 1;
	long long ans = 0;
	for (int i = 0; i < n; i++) {
		int p = P[i];
		for (int k = s/2; k+p > s/2; k--)
			ans += A[k];
		for (int k = s/2-p; k >= 0; k--)
			A[k+p] += A[k];
	}

	printf("%lld\n", ans);
	return 0;
}
