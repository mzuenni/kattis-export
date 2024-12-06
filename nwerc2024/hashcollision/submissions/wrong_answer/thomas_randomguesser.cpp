/**
 * Author: Thomas Beuman
 *
 * Method: I'm feeling lucky!
 */

#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;

const int NMAX = 200000;
const int QMAX = 1000;

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
	for (int q = 0; q < QMAX; q++) {
		int c = randnr() % n + 1;
		int r = randnr() % n + 1;
		int h = query(c, r);
		if (h == c) {
			printf("! %d %d\n", c, r);
			return 0;
		}
	}
	// No queries left; one more stab in the dark!
	int c = randnr() % n + 1;
	int r = randnr() % n + 1;
	printf("! %d %d\n", c, r);
	return 0;
}
