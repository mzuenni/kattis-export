#include <stdio.h>
#include <stdlib.h>

#define MAX 500
#define FAIL (exit(43))

typedef struct {
  int x, y;
} vec2d;

int h, w;
char status[MAX][MAX];
int puzzle[MAX][MAX];

/* non-negative, no leading zeroes, decimal number system */
int assert_int(int max, int term) {
  int c = getchar();
  if (c == '0') {
    if (getchar() != term) FAIL;
    return 0;
  }

  int n = 0;
  do {
    if (c < '0' || c > '9') FAIL;
    c -= '0';
    if (n > max / 10) FAIL;
    n *= 10;
    if (n > max - c) FAIL;
    n += c;
  } while ((c = getchar()) != term);
  return n;
}

int labels[MAX * MAX];

int compar(const void* a, const void* b) {
  const int* p = a;
  const int* q = b;
  return *p - *q;
}

void check_labels() {
  if (puzzle[h - 1][w - 1] != 0) FAIL;

  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (status[i][j] == '#' && puzzle[i][j] != i * w + j + 1) FAIL;
      labels[i * w + j] = puzzle[i][j];
    }
  }

  qsort(labels, h * w, sizeof labels[0], compar);
  for (int k = 0; k < h * w; ++k) {
    if (labels[k] != k) FAIL;
  }
}

vec2d bfsq[MAX * MAX];

void check_connected() {
  int a = 0, b = 0;
  status[h - 1][w - 1] |= 1;
  bfsq[b++] = (vec2d) {h - 1, w - 1};
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (i > 0 && i < h - 1 && j > 0 && j < w - 1) continue;
      if (status[i][j] == '#') {
        status[i][j] |= 1;
        bfsq[b++] = (vec2d) {i, j};
      }
    }
  }

  while (a < b) {
    int x = bfsq[a].x, y = bfsq[a].y;
    ++a;

    if (x > 0 && (status[x][y] ^ 1) == status[x - 1][y]) {
      status[x - 1][y] |= 1;
      bfsq[b++] = (vec2d) {x - 1, y};
    }
    if (y > 0 && (status[x][y] ^ 1) == status[x][y - 1]) {
      status[x][y - 1] |= 1;
      bfsq[b++] = (vec2d) {x, y - 1};
    }
    if (x < h - 1 && (status[x][y] ^ 1) == status[x + 1][y]) {
      status[x + 1][y] |= 1;
      bfsq[b++] = (vec2d) {x + 1, y};
    }
    if (y < w - 1 && (status[x][y] ^ 1) == status[x][y + 1]) {
      status[x][y + 1] |= 1;
      bfsq[b++] = (vec2d) {x, y + 1};
    }
  }

  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (!(status[i][j] & 1)) FAIL;
    }
  }
}

int main(int argc, char* argv[]) {
  h = assert_int(MAX, ' ');
  if (h < 1) FAIL;
  w = assert_int(MAX, '\n');
  if (w < 1) FAIL;

  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      status[i][j] = getchar();
      if (status[i][j] != '.' && status[i][j] != '#') FAIL;
    }
    if (getchar() != '\n') FAIL;
  }

  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w - 1; ++j) {
      puzzle[i][j] = assert_int(h * w - 1, ' ');
    }
    puzzle[i][w - 1] = assert_int(h * w - 1, '\n');
  }

  if (getchar() != EOF) FAIL;

  check_labels();
  check_connected();

  return 42;
}
