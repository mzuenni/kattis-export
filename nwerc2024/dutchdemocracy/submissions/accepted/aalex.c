#include <stdio.h>
#include <stdlib.h>

#define MAX_PARTIES 60
#define MAX_SEATS 10000

int p[MAX_PARTIES];

/* dp[i][j] = number of subsets of p[0..<i] with sum <= j */
long long dp[MAX_PARTIES][MAX_SEATS * MAX_PARTIES / 2 + 1];

int main() {
  int n = 0;
  scanf("%d", &n);

  int total = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", p + i);
    total += p[i];
  }

  for (int i = 1; i < n; ++i) {
    for (int j = i; j > 0 && p[j] > p[j - 1]; --j) {
      int tmp = p[j];
      p[j] = p[j - 1];
      p[j - 1] = tmp;
    }
  }

  for (int j = 0; j <= total / 2; ++j) dp[0][j] = 1;
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j <= total / 2; ++j) dp[i][j] = dp[i - 1][j];
    int k = p[i - 1];
    for (int j = k; j <= total / 2; ++j) dp[i][j] += dp[i - 1][j - k];
  }

  long long result = 0;
  for (int i = 0; i < n; ++i) {
    result += dp[i][total / 2];
    if (p[i] <= total / 2) result -= dp[i][total / 2 - p[i]];
  }

  printf("%lld\n", result);

  return 0;
}
