#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

constexpr int BLOCKED = '#';
constexpr int UNSEEN = '.';
constexpr int SEEN = ':';
constexpr int CHECK = '!';

constexpr std::pair<int, int> DELTAS[] = {
  {-1, 0},
  {0, -1},
  {0, 1},
  {1, 0},
};

int h, w;
std::vector<std::string> status;
std::vector<std::vector<int>> puzzle;
std::vector<std::vector<int>> dist2root;
std::vector<std::vector<int>> backreach;

struct stack_entry {
  std::pair<int, int> pos;
  std::pair<int, int> parent;
  int delta_index;
  int b_index;
};

std::stack<stack_entry> a_stack;
std::vector<std::pair<int, int>> b_stack;

void push(std::pair<int, int> node, std::pair<int, int> paren, int dist) {
  auto [x, y] = node;
  status[x][y] = SEEN;
  dist2root[x][y] = backreach[x][y] = dist;
  a_stack.push({node, paren, -1});
  b_stack.emplace_back(x, y);
}

template <class Iterator>
bool iseven(Iterator first, Iterator last) {
  for (Iterator it = first; it != last; ++it) {
    auto [x, y] = *it;
    status[x][y] = CHECK;
  }

  bool even = true;
  for (Iterator it = first; it != last; ++it) {
    auto [x, y] = *it;
    if (status[x][y] != CHECK) continue;
    do {
      if (status[x][y] != CHECK) return false;
      status[x][y] = SEEN;
      even = !even;
      int t = puzzle[x][y] - 1;
      x = t / w;
      y = t % w;
    } while (x != it->first || y != it->second);
    even = !even;
  }

  return even;
}

bool issolv() {
  push({h - 1, w - 1}, {-1, -1}, 0);
  while (!a_stack.empty()) {
    stack_entry& entry = a_stack.top();
    auto [x, y] = entry.pos;

    if (entry.delta_index >= 0) {
      auto [dx, dy] = DELTAS[entry.delta_index];
      int x2 = x + dx;
      int y2 = y + dy;
      if (backreach[x2][y2] >= dist2root[x][y]) {
        if (!iseven(b_stack.begin() + entry.b_index, b_stack.end())) {
          return false;
        }
        b_stack.resize(entry.b_index);
      }
      backreach[x][y] = std::min(backreach[x][y], backreach[x2][y2]);
    }
    
    while (true) {
      if (++entry.delta_index >= sizeof DELTAS / sizeof DELTAS[0]) {
        a_stack.pop();
        break;
      }

      auto [dx, dy] = DELTAS[entry.delta_index];
      int x2 = x + dx;
      int y2 = y + dy;
      if (x2 < 0 || h <= x2) continue;
      if (y2 < 0 || w <= y2) continue;
      if (x2 == entry.parent.first && y2 == entry.parent.second) continue;
      if (status[x2][y2] == BLOCKED) continue;
      if (status[x2][y2] == UNSEEN) {
        entry.b_index = b_stack.size();
        push({x2, y2}, {x, y}, dist2root[x][y] + 1);
        break;
      }
      backreach[x][y] = std::min(backreach[x][y], dist2root[x2][y2]);
    }
  }
  return true;
}

int main() {
  std::cin >> h >> w;
  status.resize(h);
  for (auto& s : status) std::cin >> s;
  puzzle.resize(h);
  for (auto& v : puzzle) {
    v.resize(w);
    for (auto& i : v) std::cin >> i;
  }

  dist2root.resize(h);
  for (auto& v : dist2root) v.resize(w);
  backreach.resize(h);
  for (auto& v : backreach) v.resize(w);

  std::cout << (issolv() ? "possible" : "impossible") << std::endl;

  return 0;
}
