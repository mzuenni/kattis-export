/**
 * Author: Thomas Beuman
 *
 * Retrieve h = f^n(1) (or any other number instead of 1)
 * Retrieve k = f^{n-h}(1)
 * We now have h = f^n(1) = f^h(f^{n-h}(1)) = f^h(k)
 * Hence we have a solution to f^c(r) = c with (c,r) = (h,k)
 *
 * This solution fails in case h == n, since then c == 0 in the second query
 */

#include <cstdio>
using namespace std;

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
	scanf("%d", &n);
	h = query(n, 1);
	k = query(n-h, 1);
	printf("! %d %d\n", h, k);
	fflush(NULL);
	return 0;
}
