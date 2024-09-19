#include "validation.h"
#include <climits>
using namespace std;

const int LEN = 5;

int main(int argc, char *argv[]) {
    InputValidator v(argc, argv);
    int n = v.read_integer("n", 5, 100);
    v.space();
    int k = v.read_integer("k", 1, 10);
    v.check(5*k <= n*n, "too many ships for this size");
    v.space();
    int f = v.read_integer("f", 0, k);
    v.space();
    int seed = v.read_integer("seed", 0, INT_MAX);
    v.space();
    double p = v.read_float("p", 0, 1);
    v.newline();

    set<pair<int,int>> squares;
    for (int i = 0; i < f; i++) {
      string dir = v.test_strings({"h", "v"}, "dir");
      v.space();
      int x = v.read_integer("x", 1, n);
      v.space();
      int y = v.read_integer("y", 1, n);
      v.newline();
      
      for (int j = 0; j < LEN; j++) {
        int nx = x + (dir=="h")*j, ny = y + (dir=="v")*j;
        v.check(nx <= n && ny <= n, "ship goes out of bounds");
        squares.emplace(nx, ny);
      }
    }
    v.check(int(squares.size()) == f*LEN, "ships intersect");
}
