/**
 * Author: Thomas Beuman

 * Retrieve r = f^n(1) (or any other number instead of 1)
 * If r == n, we have a solution to f^c(r) = c with (c,r) = (n,1)
 * Otherwise, retrieve k = f^{n-r}(1)
 * We now have r = f^n(1) = f^r(f^{n-r}(1)) = f^r(k)
 * Hence we have a solution to f^c(r) = c with (c,r) = (r,k)
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
	if (h == n) {
		k = 1;
	}
	else {
		k = query(n-h, 1);
	}
	printf("! %d %d\n", h, k);
	fflush(NULL);
	return 0;
}
