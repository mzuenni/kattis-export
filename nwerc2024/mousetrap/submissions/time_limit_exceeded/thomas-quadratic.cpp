/**
 * Author: Thomas Beuman
 * 
 * The answer is the sum of the areas of all triangles
 *   divided by the area of the entire polygon.
 *
 * The doubled area of a single triangle is
 *   x_i y_j - x_j y_i + x_j y_k - x_k y_j + x_k y_i - x_i y_k,
 * where i, j and k are in counterclockwise order.
 *
 * Summing all triangle areas together, for any i<j,
 *   the term x_i y_j - x_j y_i appears with a plus sign for every k < i and k > j,
 *   which amounts to n-1+i-j values of k.
 * It appears with a minus sign for i < k < j, of which there are j-i-1.
 *
 * This leads to the formula
 *   sum_{i<j} ((n-1+i-j) - (j-i-1)) * (x_i y_j - x_j y_i)
 *   sum_{i<j} (n+2i-2j) * (x_i y_j - x_j y_i)
 *
 * Time: O(n^2)
 * Memory: O(n)
 */

#include <cstdio>
using namespace std;

const int NMAX = 300000;

__int128 X[NMAX];
__int128 Y[NMAX];

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		X[i] = x;
		Y[i] = y;
	}

	__int128 areasum = 0;
	for (int i = 0; i < n; i++)
		for (int j = i+1; j < n; j++)
			areasum += (n+2*i-2*j) * (X[i]*Y[j] - X[j]*Y[i]);

	// Total area
	__int128 area = 0;
	for (int i = 0; i < n; i++) {
		int j = (i+1)%n;
		area += X[i]*Y[j] - X[j]*Y[i];
	}

	long double ans = (long double)areasum / area;
	printf("%Lf\n", ans);
	return 0;
}
