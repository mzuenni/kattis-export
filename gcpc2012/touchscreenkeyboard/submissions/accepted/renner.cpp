// @EXPECTED_RESULTS@: CORRECT
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string kb[] = {"qwertyuiop", "asdfghjkl", "zxcvbnm"};

int dist[26][26];

typedef struct {
  string str;
  int dist;
} score_t;

bool operator < (const score_t & a, const score_t & b) {
    if      (a.dist < b.dist) return true;
    else if (a.dist > b.dist) return false;
    else return a.str < b.str;
}

int getDist(const string & a, const string & b) {
  int sum = 0;
  for (int i = 0; i < a.length(); i++) {
    sum += dist[a[i]-'a'][b[i]-'a'];
  }
  return sum;
}

void tc() {
  vector<score_t> res;
  string a, b;
  int n;
  cin >> a >> n;
  while (n--) {
    score_t tmp;
    cin >> tmp.str;
    tmp.dist = getDist(a, tmp.str);
    res.push_back(tmp);
  }
  sort(res.begin(), res.end());
  for (vector<score_t>::iterator it = res.begin(); it != res.end(); it++) {
    cout << it->str << " " << it->dist << endl;
  }
}

void findPos(int * x, int * y, char c) {
  for (*y = 0; *y < 3; (*y)++) {
    for (*x = 0; *x < kb[*y].length(); (*x)++) {
      if (kb[*y][*x] == c) return;
    }
  }
}

int main() {
  // init
  for (char c1 = 'a'; c1 <= 'z'; c1++) {
    int x1, y1;
    findPos(&x1, &y1, c1);
    for (char c2 = 'a'; c2 <= 'z'; c2++) {
      int x2, y2;
      findPos(&x2, &y2, c2);
      dist[c1-'a'][c2-'a'] = abs(x1 - x2) + abs(y1 - y2);
    }
  }

  int ntc;
  cin >> ntc;
  while (ntc--) tc();
  return 0;
}
