#include <cstdio>
#include <utility>

constexpr int MAXH = 500;
constexpr int MAXW = 500;

constexpr int BLOCKED = '#';
constexpr int UNSEEN = '.';
constexpr int SEEN = ':';
constexpr int CHECKING = '!';

constexpr std::pair<int, int> DELTAS[] = {
  {0, 1},
  {0, -1},
  {-1, 0},
  {1, 0},
};

constexpr int NUM_DELTAS = sizeof DELTAS / sizeof DELTAS[0];

int h, w;
char status[MAXH][MAXW + 1];
int puzzle[MAXH][MAXW];

int depth[MAXH][MAXW];
int backreach[MAXH][MAXW];
int progress[MAXH][MAXW];
int bindex[MAXH][MAXW];
std::pair<int, int> parent[MAXH][MAXW];

int lena, lenb;
std::pair<int, int> stacka[MAXH * MAXW], stackb[MAXH * MAXW];

void push(std::pair<int, int> node, std::pair<int, int> paren, int dep) {
  auto [x, y] = node;
  status[x][y] = SEEN;
  depth[x][y] = backreach[x][y] = dep;
  progress[x][y] = -1;
  bindex[x][y] = lenb;
  parent[x][y] = paren;
  stacka[lena++] = stackb[lenb++] = node;
}

void backdate(int x, int y, int dep) {
  if (backreach[x][y] > dep) {
    backreach[x][y] = dep;
  }
}

template <class Iterator>
bool isevenpermut(Iterator first, Iterator last) {
  for (Iterator it = first; it != last; ++it) {
    auto [x, y] = *it;
    status[x][y] = CHECKING;
  }

  int even = true;
  for (Iterator it = first; it != last; ++it) {
    auto [x, y] = *it;
    if (status[x][y] != CHECKING) continue;

    int j = x;
    int k = y;
    do {
      if (status[j][k] != CHECKING) return false;
      status[j][k] = SEEN;
      even = !even;
      int p = puzzle[j][k] - 1;
      j = p / w;
      k = p % w;
    } while (j != x || k != y);
    even = !even;
  }

  return even;
}

bool issolv() {
  lena = lenb = 0;
  push({h - 1, w - 1}, {-1, -1}, 0);
  while (lena > 0) {
    auto [x, y] = stacka[lena - 1];

    if (progress[x][y] >= 0) {
      auto [dx, dy] = DELTAS[progress[x][y]];
      int x2 = x + dx;
      int y2 = y + dy;

      backdate(x, y, backreach[x2][y2]);

      if (backreach[x2][y2] >= depth[x][y]) {
        if (!isevenpermut(stackb + bindex[x][y] + 1, stackb + lenb)) return false;
        lenb = bindex[x][y] + 1;
      }
    }
    
    while (true) {
      if (++progress[x][y] >= NUM_DELTAS) {
        --lena;
        break;
      }

      auto [dx, dy] = DELTAS[progress[x][y]];
      int x2 = x + dx;
      int y2 = y + dy;

      if (x2 < 0 || h <= x2) continue;
      if (y2 < 0 || w <= y2) continue;
      if (x2 == parent[x][y].first && y2 == parent[x][y].second) continue;
      if (status[x2][y2] == BLOCKED) continue;

      if (status[x2][y2] == UNSEEN) {
        push({x2, y2}, {x, y}, depth[x][y] + 1);
        break;
      }

      backdate(x, y, depth[x2][y2]);
    }
  }
  return true;
}

int main() {
  scanf("%d%d", &h, &w);
  for (int i = 0; i < h; ++i) {
    std::scanf("%s", status[i]);
  }
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      std::scanf("%d", &puzzle[i][j]);
    }
  }

  std::printf("%s\n", issolv() ? "possible" : "impossible");

  return 0;
}
