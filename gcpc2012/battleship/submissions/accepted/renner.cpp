// @EXPECTED_RESULTS@: CORRECT

#include <iostream>
#include <string>
#include <cstring>
using namespace std;


#define MAX_DIM  30

int map[2][MAX_DIM][MAX_DIM];
int ships[2];

enum { WATER, SHIP, HIT };


int play(int p, int rem) {
  int x, y;
  p = (p + 1) & 1;
  while (rem-- > 0) {
    cin >> x >> y;

    // test target
    if (map[p][y][x] == SHIP) {
      map[p][y][x] = HIT;
      if (--ships[p] == 0) return rem;
    } else {
      return rem;
    }
  }
  return 0;
}


void tc() {
  int w, h, n;
  cin >> w >> h >> n;

  // read
  ships[0] = ships[1] = 0;
  for (int p = 0; p < 2; p++) {
    for (int i = h - 1; i >= 0; i--) {
      string str;
      cin >> str;
      for (unsigned int s = 0; s < str.length(); s++) {
        // '_' == water, '#' == ship
        if (str[s] == '#') {
          map[p][i][s] = SHIP;  
          ships[p]++;;
        } else {
          map[p][i][s] = WATER;
        }
      }
    }
  }
  
  // sim
  bool done = false;
  while (n > 0) {
    n = play(0, n);  // p one
    n = play(1, n);  // p two

    if (! done) {
      if (ships[0] == 0 && ships[1] == 0) {
        cout << "draw" << endl;
        done = true;
      } else if (ships[0] == 0) {
        cout << "player two wins" << endl;
        done = true;
      } else if (ships[1] == 0) {
        cout << "player one wins" << endl;
        done = true;
      }
    }
  }

  if (! done) {
    cout << "draw" << endl;
  }
}



int main() {
  int ntc;
  cin >> ntc;
  while (ntc--) tc();
  return 0;
}
