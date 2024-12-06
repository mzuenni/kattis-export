/**
 * Author: Thomas Beuman
 *
 * Retrieve h = f^n(1) (or any other number instead of 1)
 * If h == n, we have a solution to f^c(r) = c with (c,r) = (n,1)
 * Otherwise, retrieve k = f^{n-h}(1)
 * We now have h = f^n(1) = f^h(f^{n-h}(1)) = f^h(k)
 * Hence we have a solution to f^c(r) = c with (c,r) = (h,k)
 *
 * This solution deliberately uses one more than the maximum amount of queries
 */

#include <cstdio>
using namespace std;

const int QMAX = 1000;

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
	int n, h, k;
	int q = 0;
	scanf("%d", &n);
	h = query(n, 1);
	q++;
	if (h == n) {
		k = 1;
	}
	else {
		k = query(n-h, 1);
		q++;
	}
	for (; q < QMAX+1; q++)
		query(1, 1);
	printf("! %d %d\n", h, k);
	fflush(NULL);
	return 0;
}
