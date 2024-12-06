#include <stdio.h>

#define MAXH 500
#define MAXW 500

#define BLOCKED '#'
#define UNSEEN '.'
#define SEEN ':'
#define CHECK '!'

typedef struct {
  int x, y;
} vec2d;

const vec2d DELTAS[] = {
  {-1, 0},
  {0, -1},
  {0, 1},
  {1, 0},
};

int h, w;
char status[MAXH][MAXW + 1];
int puzzle[MAXH][MAXW];

int dist2root[MAXH][MAXW];
int backreach[MAXH][MAXW];
int progress[MAXH][MAXW];
int bindex[MAXH][MAXW];
vec2d parent[MAXH][MAXW];

int lena, lenb;
vec2d stacka[MAXH * MAXW], stackb[MAXH * MAXW];

void push(int x, int y, int px, int py, int d) {
  status[x][y] = SEEN;
  dist2root[x][y] = backreach[x][y] = d;
  progress[x][y] = -1;
  bindex[x][y] = lenb;
  parent[x][y].x = px;
  parent[x][y].y = py;

  stacka[lena].x = x;
  stacka[lena].y = y;
  ++lena;

  stackb[lenb].x = x;
  stackb[lenb].y = y;
  ++lenb;
}

int iseven(vec2d* first, vec2d* last) {
  for (vec2d* p = first; p != last; ++p) {
    status[p->x][p->y] = CHECK;
  }

  int even = 1;
  for (vec2d* p = first; p != last; ++p) {
    int x = p->x;
    int y = p->y;
    if (status[x][y] != CHECK) continue;
    do {
      if (status[x][y] != CHECK) return 0;
      status[x][y] = SEEN;
      even ^= 1;
      int t = puzzle[x][y] - 1;
      x = t / w;
      y = t % w;
    } while (x != p->x || y != p->y);
    even ^= 1;
  }

  return even;
}

int issolv() {
  lena = lenb = 0;
  push(h - 1, w - 1, -1, -1, 0);
  while (lena > 0) {
    int x = stacka[lena - 1].x;
    int y = stacka[lena - 1].y;

    if (progress[x][y] >= 0) {
      int x2 = x + DELTAS[progress[x][y]].x;
      int y2 = y + DELTAS[progress[x][y]].y;
      if (backreach[x2][y2] >= dist2root[x][y]) {
        if (!iseven(stackb + bindex[x2][y2], stackb + lenb)) return 0;
        lenb = bindex[x2][y2];
      }
      if (backreach[x][y] > backreach[x2][y2]) {
        backreach[x][y] = backreach[x2][y2];
      }
    }
    
    while (1) {
      if (++progress[x][y] >= sizeof DELTAS / sizeof DELTAS[0]) {
        --lena;
        break;
      }

      int x2 = x + DELTAS[progress[x][y]].x;
      int y2 = y + DELTAS[progress[x][y]].y;
      if (x2 < 0 || h <= x2) continue;
      if (y2 < 0 || w <= y2) continue;
      if (x2 == parent[x][y].x && y2 == parent[x][y].y) continue;
      if (status[x2][y2] == BLOCKED) continue;
      if (status[x2][y2] == UNSEEN) {
        push(x2, y2, x, y, dist2root[x][y] + 1);
        break;
      }

      if (backreach[x][y] > dist2root[x2][y2]) {
        backreach[x][y] = dist2root[x2][y2];
      }
    }
  }
  return 1;
}

int main() {
  scanf("%d%d", &h, &w);
  for (int i = 0; i < h; ++i) {
    scanf("%s", status[i]);
  }
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      scanf("%d", &puzzle[i][j]);
    }
  }

  printf("%s\n", issolv() ? "possible" : "impossible");

  return 0;
}
