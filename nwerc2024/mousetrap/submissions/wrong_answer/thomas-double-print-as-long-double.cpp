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
 * This sum can be split:
 * sum_j {
 *     (n-2j) y_j (sum x_i)
 *   + 2 y_j (sum i x_i)
 *   - (n-2j) x_j (sum y_i)
 *   - 2 x_j (sum i y_i)
 * }
 * The sums over i can be precalculated
 *
 * Time: O(n)
 * Memory: O(n)
 *
 * This solution uses doubles, which are not accurate enough
 */

#include <cstdio>
using namespace std;

const int NMAX = 300000;

double X[NMAX];
double Y[NMAX];

double Xsum[NMAX+1];
double Ysum[NMAX+1];
double Xisum[NMAX+1];
double Yisum[NMAX+1];

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

	Xsum[0] = Ysum[0] = Xisum[0] = Yisum[0] = 0;
	for (int i = 0; i < n; i++) {
		Xsum[i+1] = Xsum[i] + X[i];
		Ysum[i+1] = Ysum[i] + Y[i];
		Xisum[i+1] = Xisum[i] + i*X[i];
		Yisum[i+1] = Yisum[i] + i*Y[i];
	}

	double areasum = 0;
	for (int j = 0; j < n; j++) {
		areasum += (n-2*j) * Y[j] * Xsum[j];
		areasum += 2 * Y[j] * Xisum[j];
		areasum -= (n-2*j) * X[j] * Ysum[j];
		areasum -= 2 * X[j] * Yisum[j];
	}

	// Total area
	double area = 0;
	for (int i = 0; i < n; i++) {
		int j = (i+1)%n;
		area += X[i]*Y[j] - X[j]*Y[i];
	}

	double ans = areasum / area;
	printf("%.9Lf\n", ans); // this produces nan for some reason
	return 0;
}
