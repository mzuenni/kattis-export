#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000
#define MAXS 50

char names[MAXN][MAXS + 8];
int pos[MAXN];
int order[MAXN];

int compar(const void* a, const void* b) {
  const int* p = a;
  const int* q = b;
  return strcmp(names[*p] + pos[*p], names[*q] + pos[*q]);
}

int main() {
  char line[MAXS + 8];
  fgets(line, MAXS + 4, stdin);
  int n = atoi(line);
  for (int i = 0; i < n; ++i) {
    fgets(names[i], MAXS + 4, stdin);
    for (pos[i] = 0; !isupper(names[i][pos[i]]); ++pos[i]) {}
    order[i] = i;
  }
  
  qsort(order, n, sizeof order[0], compar);

  for (int i = 0; i < n; ++i) {
    fputs(names[order[i]], stdout);
  }

  return 0;
}
