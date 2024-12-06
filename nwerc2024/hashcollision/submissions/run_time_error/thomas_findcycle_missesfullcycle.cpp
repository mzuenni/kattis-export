/**
 * Author: Thomas Beuman
 *
 * Repeated application of f will eventually result in a value already seen,
 *   and thus from then on a cycle.
 * Let k be the length of the cycle, and h any f(x) part of the cycle,
 *   then we have h = f^k(h) = f^{2k}(h) = ...
 * Hence, the value of r that satisfies f^h(r) = h,
 *   also satisfies f^c(r) = h for c = r%k.
 * Now h = f^k(h) = f^c(f^{k-c}(h)), so r = f^{k-c}(h).
 * Note that k may also be a multiple of the cycle length for this to work.
 *
 * Finding the cycle length:
 * First, we take r = f^n(1) (or any other value instead of 1),
 *   to ensure that r is on the cycle.
 * If f^a(r) = f^b(r) = h for some a < b, we know that b-a is a multiple of k.
 * The other way around, if b-a is a multiple of k, we have f^a(r) = f^b(r).
 *
 * Let m be any integer <= n. Consider the set
 *   S = {0, 1, 2, ..., m-2, m-1, m, 2m, 3m, ..., floor(n/m)*m, n}
 * For any k, there will be an a and b of S such that k = b-a
 *   (namely, with a = m - k%m).
 * If we take m ~= sqrt(n), the size of S will be |S| ~= 2*sqrt(n),
 *   sufficiently small to stay within q_max.
 *
 * This is based on the accepted solution thomas_findcycle.cpp,
 *   but forgets to include n in S.
 */

#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;

const int NMAX = 200000;
const int QMAX = 1000;

long long A[NMAX+1];

int query (int c, int r)
{
	printf("? %d %d\n", c, r);
	fflush(NULL);
	int h;
	scanf("%d", &h);
	return h;
}

bool check (int c, int r)
{
	int h = query(c, r);
	if (A[h] >= 0) {
		int k = c - A[h];
		c = k - h % k;
		r = query(c, h);
		printf("! %d %d\n", h, r);
		fflush(NULL);
		return true;
	}
	A[h] = c;
	return false;
}

int main()
{
	int n;
	scanf("%d", &n);
	int r = query(n, 1);
	memset(A, -1, sizeof(A));
	A[r] = 0;
	int m = sqrt(n);
	for (int c = 1; c < m; c++)
		if (check(c, r))
			return 0;
	for (int c = m; c <= n; c += m)
		if (check(c, r))
			return 0;
	// Error: the cycle length could be larger than the largest multiple of m!
	// Should be finished now!
	return 1;
}
