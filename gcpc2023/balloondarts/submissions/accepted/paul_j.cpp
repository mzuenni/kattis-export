#include <bits/stdc++.h>

#define NUM_TRIES 100
#define SEED 123456789

using namespace std;

struct pt {
  uint64_t x, y;
};

bool collinear(pt a, pt b, pt c) {
  return (a.y - b.y) * (a.x - c.x) == (a.y - c.y) * (a.x - b.x);
}

bool covered_by_one_line(vector<pt> &points) {
  if (points.size() <= 2) return true;
  return all_of(points.begin() + 1, points.end(), [&points](pt p){
    return collinear(points[0], points[1], p);
  });
}

bool covered_by_k_lines(vector<pt> &points, uint64_t k) {
  if (points.size() <= 2 * k) return true;
  if (k == 1) return covered_by_one_line(points);

  std::mt19937 gen(SEED);
  std::uniform_int_distribution<uint64_t> dist(0, points.size() - 1);

  for (uint64_t cur = 0; cur < NUM_TRIES; ++cur) {
    uint64_t idx1 = dist(gen);
    uint64_t idx2 = dist(gen);
    while (idx1 == idx2) idx2 = dist(gen);

    uint64_t on_line = count_if(points.begin(), points.end(),
        [&points, idx1, idx2](pt p){
      return collinear(points[idx1], points[idx2], p);
    });

    if (on_line >= (points.size() + k - 1) / k) {
      vector<pt> remaining;
      copy_if(points.begin(), points.end(), back_inserter(remaining),
          [&points, idx1, idx2](pt p){
        return !collinear(points[idx1], points[idx2], p);
      });
      if (covered_by_k_lines(remaining, k - 1)) return true;
    }
  }
  return false;
}

int main() {
  uint64_t n;
  scanf("%ld", &n);

  vector<pt> points;
  points.reserve(n);

  for (size_t i = 0; i < n; ++i) {
    uint64_t x, y;
    scanf("%ld %ld", &x, &y);
    points.push_back(pt {x, y});
  }

  if (covered_by_k_lines(points, 3)) printf("possible\n");
  else printf("impossible\n");

  return 0;
}
