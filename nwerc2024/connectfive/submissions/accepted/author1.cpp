#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

int X[5], Y[5];
int Xsorted[5], Ysorted[5];
int X0[5], Y0[5];

vector<pair<int,int>> Paths[10];
int TotalHorizLength[1<<20], TotalVertLength[1<<20];

void generate_paths (vector<pair<int,int>>& V, int x1, int y1, int x2, int y2, int horiz, int vert)
{
	if (x1 == x2 && y1 == y2)
		V.push_back(make_pair(horiz, vert));
	int b = 1<<(4*y1+x1);
	if (x1 < x2)
		generate_paths(V, x1+1, y1, x2, y2, horiz | b, vert);
	else if (x1 > x2)
		generate_paths(V, x1-1, y1, x2, y2, horiz | (b>>1), vert);
	b = 1<<(4*x1+y1);
	if (y1 < y2)
		generate_paths(V, x1, y1+1, x2, y2, horiz, vert | b);
	else if (y1 > y2)
		generate_paths(V, x1, y1-1, x2, y2, horiz, vert | (b>>1));
}

int minimum_length (int k, int horiz, int vert)
{
	if (k == 10)
		return TotalHorizLength[horiz] + TotalVertLength[vert];
	int minlen = 999999;
	for (pair<int,int> path : Paths[k])
		minlen = min(minlen, minimum_length(k+1, horiz | path.first, vert | path.second));
	return minlen;
}

int main()
{
	for (int i = 0; i < 5; i++)
		scanf("%d %d", &X[i], &Y[i]);

	// Identify the roads with a location
	for (int i = 0; i < 5; i++) {
		Xsorted[i] = X[i];
		Ysorted[i] = Y[i];
	}
	sort(Xsorted, Xsorted + 5);
	sort(Ysorted, Ysorted + 5);
	int n = 1;
	for (int i = 1; i < 5; i++)
		if (Xsorted[i] > Xsorted[i-1])
			Xsorted[n++] = Xsorted[i];
	int m = 1;
	for (int i = 1; i < 5; i++)
		if (Ysorted[i] > Ysorted[i-1])
			Ysorted[m++] = Ysorted[i];

	// Pre-compute the total length for all subsets
	TotalHorizLength[0] = TotalVertLength[0] = 0;
	for (int k = 0; k < 20; k++) {
		int horizlen = Xsorted[k%4+1] - Xsorted[k%4];
		int vertlen = Ysorted[k%4+1] - Ysorted[k%4];
		for (int s = 0; s < (1<<k); s++) {
			TotalHorizLength[s+(1<<k)] = TotalHorizLength[s] + horizlen;
			TotalVertLength[s+(1<<k)] = TotalVertLength[s] + vertlen;
		}
	}

	// "Shrink" the grid
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)
			if (X[i] == Xsorted[j]) {
				X0[i] = j;
				break;
			}
		for (int j = 0; j < 5; j++)
			if (Y[i] == Ysorted[j]) {
				Y0[i] = j;
				break;
			}
	}

	// Determine all shortest paths for every pair of locations
	int k = 0;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < i; j++) {
			Paths[k].clear();
			generate_paths(Paths[k++], X0[i], Y0[i], X0[j], Y0[j], 0, 0);
		}

	int ans = minimum_length(0, 0, 0);
	printf("%d\n", ans);
	return 0;
}
