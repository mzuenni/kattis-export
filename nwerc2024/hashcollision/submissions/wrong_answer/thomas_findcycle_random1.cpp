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
 *
 * Finding the cycle length:
 * First, we take h = f^n(1) (or any other value instead of 1),
 *   to ensure that h is on the cycle.
 * Then, we keep applying f a random number of times.
 * If at some point we encounter a value that we have already seen,
 *   c.e. f^a(h) = f^b(h) for some a < b,
 *   we know that the cycle length is a divisor of m = b-a.
 *
 * To find r as above, it does not matter that k is the exact cycle length;
 *   a multiple of the cycle length will also do.
 * However, k-c may not exceed n, so we need a divisor of m that is at most n.
 * For this, we simply try divisors k <= n of m until we confirm f^k(h) = h.
 *
 * Analysis of probability of success:
 * Let us say we take s perfectly uniform random samples from the cycle.
 * The probability that two of these are congruent modulo k is then approximately
 *   p ~= 1 - exp( -s(s-1) / 2k )
 * For k ~= 200000 and s ~= 1000 this gives p ~= 92%
 */

#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;

const int NMAX = 200000;
const int QMAX = 1000;

long long A[NMAX+1];

// Basic linear congruential generator
int randnr()
{
	static int rseed = 1;
	return rseed =  (16807ll * rseed) % 0x7fffffff;
}

int query (int c, int r)
{
	printf("? %d %d\n", c, r);
	fflush(NULL);
	int h;
	scanf("%d", &h);
	return h;
}

int main()
{
	int n;
	scanf("%d", &n);
	int r = query(n, 1);
	memset(A, -1, sizeof(A));
	A[r] = 0;
	long long t = 0;
	while (true) {
		int c = randnr() % n + 1;
		t += c;
		int h = query(c, r);
		if (A[h] >= 0) {
			long long m = t - A[h];
			fprintf(stderr, "m = %lld\n", m);
			for (int k = n; true; k--)
				if (m % k == 0 && query(k, h) == h) {
					c = k - h % k;
					int r = query(c, h);
					printf("! %d %d\n", h, r);
					fflush(NULL);
					return 0;
				}
		}
		A[h] = t;
		r = h;
	}
}
