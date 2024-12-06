#include <stdio.h>

long long N, K;
char str[100000 + 1];

long long getstep(long long k) {
  if (k == 0) {
    return 1 % N;
  }

  long long step = getstep(k >> 1);
  step *= step;
  step %= N;
  if (k & 1) {
    step *= 2;
    step %= N;
  }

  return step;
}

int main() {
  scanf("%lld%lld%s", &N, &K, str);

  long long step = getstep(K);

  for (long long pos = 0, i = 0; i < N; ++i) {
    printf("%c", str[pos]);
    pos += step;
    pos %= N;
  }
  printf("\n");

  return 0;
}
