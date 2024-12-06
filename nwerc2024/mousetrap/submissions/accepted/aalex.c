#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
  uint64_t lo, hi;
} myint;

myint sgnext(uint64_t a) {
  return (myint) {a, -(a >> 63)};
}

myint plus(myint a, myint b) {
  return (myint) {a.lo + b.lo, a.hi + b.hi + (a.lo > UINT64_MAX - b.lo)};
}

myint minus(myint a, myint b) {
  return (myint) {a.lo - b.lo, a.hi - b.hi - (a.lo < b.lo)};
}

myint times(myint a, myint b) {
  uint64_t a0 = a.lo << 32 >> 32;
  uint64_t a1 = a.lo >> 32;
  uint64_t a2 = a.hi << 32 >> 32;
  uint64_t a3 = a.hi >> 32;

  uint64_t b0 = b.lo << 32 >> 32;
  uint64_t b1 = b.lo >> 32;
  uint64_t b2 = b.hi << 32 >> 32;
  uint64_t b3 = b.hi >> 32;

  uint64_t a0b0 = a0 * b0;

  uint64_t a0b1 = a0 * b1;
  uint64_t a1b0 = a1 * b0;

  uint64_t a0b2 = a0 * b2;
  uint64_t a1b1 = a1 * b1;
  uint64_t a2b0 = a2 * b0;

  uint64_t a0b3 = a0 * b3;
  uint64_t a1b2 = a1 * b2;
  uint64_t a2b1 = a2 * b1;
  uint64_t a3b0 = a3 * b0;

  uint64_t lo = 0;
  uint64_t hi = 0;
  uint64_t sh = 0;

  sh += a0b0 << 32 >> 32;
  lo |= sh << 32 >> 32;
  sh >>= 32;

  sh += a0b0 >> 32;
  sh += a0b1 << 32 >> 32;
  sh += a1b0 << 32 >> 32;
  lo |= sh << 32;
  sh >>= 32;

  sh += a0b1 >> 32;
  sh += a1b0 >> 32;
  sh += a0b2 << 32 >> 32;
  sh += a1b1 << 32 >> 32;
  sh += a2b0 << 32 >> 32;
  hi |= sh << 32 >> 32;
  sh >>= 32;

  sh += a0b2 >> 32;
  sh += a1b1 >> 32;
  sh += a2b0 >> 32;
  sh += a0b3 << 32 >> 32;
  sh += a1b2 << 32 >> 32;
  sh += a2b1 << 32 >> 32;
  sh += a3b0 << 32 >> 32;
  hi |= sh << 32;
  sh >>= 32;

  return (myint) {lo, hi};
}

int comp(myint a, myint b) {
  if (a.hi < b.hi || (a.hi == b.hi && a.lo < b.lo)) return -1;
  if (a.hi > b.hi || (a.hi == b.hi && a.lo > b.lo)) return 1;
  return 0;
}

myint div(myint* a, myint b) {
  if (comp(*a, b) < 0) return (myint) {0, 0};

  int k = 0;
  for (uint64_t i = a->hi ? a->hi : (k -= 64, a->lo); !(i >> 63); i <<= 1) --k;
  for (uint64_t i = b.hi ? b.hi : (k += 64, b.lo); !(i >> 63); i <<= 1) ++k;

  if (k >= 64) {
    b.hi = b.lo << (k - 64);
    b.lo = 0;
  } else if (k > 0) {
    b.hi = (b.hi << k) | b.lo >> (64 - k);
    b.lo <<= k;
  }
  
  myint q = {0, 0};
  do {
    q.hi = (q.hi << 1) | (q.lo >> 63);
    q.lo <<= 1;
    if (comp(*a, b) >= 0) {
      *a = minus(*a, b);
      q.lo |= 1;
    }
    b.lo = (b.lo >> 1) | ((b.hi & 1) << 63);
    b.hi >>= 1;
  } while (--k >= 0);
  return q;
}

void printint(myint a) {
  char output[128];
  int len = 0;
  do {
    myint b = div(&a, sgnext(10));
    output[len++] = '0' + a.lo;
    a = b;
  } while (a.hi != 0 || a.lo != 0);
  while (len > 0) printf("%c", output[--len]);
}

void printdec(myint a, int digits) {
  char output[128];
  int len = 0;
  while (digits-- > 0) {
    myint b = div(&a, sgnext(10));
    output[len++] = '0' + a.lo;
    a = b;
  }
  while (len > 0) printf("%c", output[--len]);
}

int main() {
  int32_t n;
  scanf("%" SCNd32 "d", &n);

  myint polygon_area = {0, 0};
  myint triangles_area = {0, 0};
  myint cross_sum = {0, 0};
  myint x_diff_sum = {0, 0};
  myint y_diff_sum = {0, 0};
  int64_t x_sum = 0;
  int64_t y_sum = 0;

  uint64_t x0, y0, prev_x, prev_y;
  for (int32_t i = 0, x, y; i < n; ++i) {
    scanf("%" SCNd32 "%" SCNd32, &x, &y);

    if (i > 0) {
      polygon_area = plus(polygon_area, sgnext(prev_x * y - prev_y * x));
    } else {
      x0 = x;
      y0 = y;
    }

    triangles_area = plus(triangles_area, cross_sum);
    triangles_area = plus(triangles_area, times(sgnext(y), x_diff_sum));
    triangles_area = minus(triangles_area, times(sgnext(x), y_diff_sum));

    cross_sum = plus(cross_sum, times(sgnext(y), sgnext(x_sum)));
    cross_sum = minus(cross_sum, times(sgnext(x), sgnext(y_sum)));

    x_diff_sum = plus(x_diff_sum, sgnext((uint64_t) i * x));
    x_diff_sum = minus(x_diff_sum, sgnext(x_sum));

    y_diff_sum = plus(y_diff_sum, sgnext((uint64_t) i * y));
    y_diff_sum = minus(y_diff_sum, sgnext(y_sum));

    x_sum += x;
    y_sum += y;

    prev_x = x;
    prev_y = y;
  }
  polygon_area = plus(polygon_area, sgnext(prev_x * y0 - prev_y * x0));

  myint rem = triangles_area;
  myint quot = div(&rem, polygon_area);
  rem = times(rem, sgnext(100000000));
  rem = div(&rem, polygon_area);
  printint(quot);
  printf(".");
  printdec(rem, 8);
  printf("\n");

  return 0;
}
