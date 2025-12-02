#include <cstdio>
#include <iostream>
#include <set>
#include <vector>

int a[500007];
int dp[500007];

int readInt () {
	int result = 0;
	char ch;
	ch = getchar();
	while (true) {
		if (ch >= '0' && ch <= '9') break;
		ch = getchar();
	}
	result = ch - '0';
	while (true) {
		ch = getchar();
		if (ch < '0' || ch > '9') break;
		result = result*10 + (ch - '0');
	}
	return result;
}

int main() {
	
	int n = readInt();

	std::set<int> coords_i, scj;
	coords_i.insert(0);
	scj.insert(0);

	for (int i = 0; i < n; ++i) {
		a[i] = readInt();
		int j = a[i] - i;
	}
	for (int i = 1; i <= n; ++i) {
		int j = a[i - 1] - i;
		if (j >= 0) {
			coords_i.insert(i);
			scj.insert(j);
		}
	}
	for (int j = 1; j <= n; ++j) {
		int i = a[n - j] - j;
		if (i >= 0) {
			coords_i.insert(i);
			scj.insert(j);
		}
	}

	std::vector<int> coords_j(scj.begin(), scj.end());

	for (int i : coords_i) {
		if (i > 0) {
			for(int jj = 0; jj < (int)(coords_j.size()); ++jj) {
				int j = coords_j[jj];
				dp[jj] += a[i - 1] == (i + j);
			}
		}
		for (int jj = 1; jj < (int)(coords_j.size()); ++jj) {
			int j = coords_j[jj];
			dp[jj] = std::max(dp[jj], dp[jj - 1] + (a[n - j] == (i + j)));
		}
	}

	std::cout << n - dp[coords_j.size() - 1] << std::endl;
}
