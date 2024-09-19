#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define ABS(a) ((a) < 0 ? -(a) : (a))

#define MAXN 12

int x[MAXN];
int y[MAXN];
int n;

double dp[1<<MAXN][MAXN];
double dist[MAXN][MAXN];

double distance(double angle, int i, int j) {
  double dx = x[j] - x[i];
  double dy = y[j] - y[i];
  double x = dx * cos(angle) - dy * sin(angle);
  double y = dx * sin(angle) + dy * cos(angle);
  return ABS(x) + ABS(y);
}

double withAngle(double angle) {
  for(int i = 0; i < n; i++)
    for(int j = i + 1; j < n; j++)
      dist[i][j] = dist[j][i] = distance(-angle, i, j);
  
  dp[0][0] = 0;
  for(int i = 1; i < (1<<n); i++) {
    for(int j = 0; j < n; j++) {
      dp[i][j] = 1e99;
      for(int k = 0; k < n; k++) {
	if((i & (1<<k)) == 0) continue;
	if(j == k) continue;
	dp[i][j] = MIN(dp[i][j], dp[i^(1<<k)][k] + dist[j][k]);
      }
    }
  }
  double ret = 1e99;
  for(int i = 0; i < n; i++)
    ret = MIN(ret, dp[(1<<n)-(1<<i)-1][i]);
  return ret;
}

int main() {
  scanf("%d\n", &n);
  for(int i = 0; i < n; i++)
    scanf("%d %d\n", &x[i], &y[i]);

  double best = 1e99;

  for(int i = 0; i < n; i++) {
    for(int j = i + 1; j < n; j++) {
      double angle = atan2(y[j] - y[i], x[j] - x[i]);
      double cur = withAngle(angle);
      if(cur < best) best = cur;
    }
  }

  printf("%lf\n", best);

  return 0;
}
