/**
 * Author: Thomas Beuman
 * 
 * First, note that, if we are going to place some separators,
 *   we might as well put them on the smallest ones.
 *
 * After placing the separators, we (try to) fill the book rack
 *   by filling up one shelf at a time, from highest to smallest,
 *   and use the books in order from highest to lowest.
 * If this strategy fails, it is impossible to fill the book rack.
 *
 * The strategy will fail only in case we just filled a shelf
 * but the next book is too high for the next shelf (or there is no next shelf).
 *
 * Index the shelves and the books from high to low.
 * Let b_i be the number of books that can only fit (height-wise) on the top i shelves.
 *
 * With s separators, the top i shelves (with i >= n-s) can only hold
 *   (n-s)*x + (i+s-n)*y  =  i*y + n*(x-y) - s*(x-y)
 * books width-wise.
 * For the failure condition to not occur, we thus require
 *   b_i <= i*y + n*(x-y) - s*(x-y)
 * or (if x != y)
 *   s <= (i*y + n*(x-y) - b_i) / (x-y)
 * for every  i >= n-s.
 *
 * We can turn this around, by checking for each i what the maximum value of s is,
 *   and taking the minimum over all i to be the final answer.
 * Note that the case  s = n-i  gives the inequality  b_i <= x*i,
 *   the condition for being able to fit the books at all, even without shortening any shelves.
 * Therefore, should we find  s < n-i  for some i,  there is no solution at all.
 *
 * This version fails to properly account for the possibility
 *   that the calculated limit for s is negative.
 *
 * Time: O(n log n)
 */

#include <algorithm>
#include <cstdio>
#include <functional>
using namespace std;

const int NMAX = 100000;

int Shelves[NMAX+1];
int Books[NMAX];

int main()
{
	int n, m, x, y;
	scanf("%d %d %d %d", &n, &m, &x, &y);
	for (int i = 0; i < n; i++)
		scanf("%d", &Shelves[i]);
	for (int j = 0; j < m; j++)
		scanf("%d", &Books[j]);
	sort(Shelves, Shelves + n, greater<int>());
	sort(Books, Books + m, greater<int>());
	Shelves[n] = 0;
	int ans = n;
	int b = 0;
	for (int i = 0; i <= n; i++) {
		while (b < m && Books[b] > Shelves[i])
			b++;
		if (y == x) {
			if (i*y < b) // Impossible
				ans = -1;
		}
		else {
			int s = (i*y + n*(x-y) - b) / (x-y);
			if (s < n-i) // Impossible
				ans = -1;
			ans = min(ans, s); // This might set ans smaller than -1
		}
	}
	if (ans == -1) // Fail: ans could also be smaller than -1
		printf("impossible\n");
	else
		printf("%d\n", ans);
	return 0;
}
