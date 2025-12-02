#include <cstdio>
#include <iostream>

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
	for (int i = 0; i < n; ++i) {
		a[i] = readInt();
	}

	for (int i = 0; i < n + 1; ++i) {
		if (i > 0) {
			for (int j = 0; j <= n; ++j) {
				dp[j] += a[i - 1] == (i + j);
			}
		}
		for (int j = 1; j <= n; ++j) {
			dp[j] = std::max(dp[j], dp[j - 1] + (a[n - j] == (i + j)));
		}
	}
		

	std::cout << n - dp[n] << std::endl;
}
