// Author: Thomas Beuman

#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

const int NMAX = 500;

const double eps = 1e-3;

int X[NMAX];
int Y[NMAX];
int Heights[NMAX];

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d %d %d", &X[i], &Y[i], &Heights[i]);
	for (int i = 0; i < n; i++) {
		int maxlen = Heights[i];
		for (int j = 0; j < n; j++)
			if (Heights[j] > Heights[i]) {
				int dx = X[i]-X[j];
				int dy = Y[i]-Y[j];
				int dis = sqrt(dx*dx + dy*dy + eps);
				maxlen = min(maxlen, dis);
			}
		printf("%d\n", maxlen);
	}
	return 0;
}
