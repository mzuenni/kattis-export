#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using vl = vector<ll>;
using vvl = vector<vl>;
using pll = pair<ll,ll>;
using pld = pair<ld,ld>;
using vb = vector<bool>;
const ll oo = 0x3f3f3f3f3f3f3f3fLL;
const ld eps = 1e-9;
#define sz(c) ll((c).size())
#define all(c) begin(c),end(c)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define xx first
#define yy second
#define has(c,i) ((c).find(i) != end(c))
#define FOR(i,a,b) for(ll i = (a); i < (b); i++)
#define FORD(i,a,b) for(ll i = ll(b) - 1; i >= (a); i--)
#define DBG(x) ({if(1) cerr << "DBG: " << (#x) << " = " << (x) << endl; })
#define FAKT 5
#define DEBUG 0
#define MAX_QUERIES 10000
#define MAX_SIZE 1000

/* 
 * Creates a maze with balanced junctions
 */


typedef struct cell {
  bool north = true, west = true, south = true, east = true;
} cell;

void flip_vert(cell &src, cell &tgt) {
  tgt.north = src.south;
  tgt.south = src.north;
  tgt.west = src.west;
  tgt.east = src.east;
}

void flip_hor(cell &src, cell &tgt) {
  tgt.north = src.north;
  tgt.south = src.south;
  tgt.west = src.east;
  tgt.east = src.west;
}

void print(vector<vector<cell>> &c) {
  cout << ' ';
  FOR(j,0,sz(c[0])) {
    if(c[0][j].north) cout << '_';
    else cout << ' ';
    cout << ' ';
  }
  cout << endl;
  FOR(i,0,sz(c)) {
    if(c[i][0].west) cout << '|';
    else cout << ' ';
    FOR(j,0,sz(c[i])) {
      if(c[i][j].south) cout << '_';
      else cout << ' ';
      if(c[i][j].east) cout << '|';
      else cout << ' ';
    }
    cout << endl;
  }
}

void doubl(vector<vector<cell>> &res, ll len) {
  res[len / 4][len/2 - 1].east = false;
  res[len / 4][len/2].east = false;
  res[len / 4][len/2].west = false;
  FOR(i,0,len / 2) {
    FOR(j,0,len / 2) {
      flip_hor(res[i][j], res[i][len - 1 - j]);
    }
  }
  FOR(i,0,len/2) res[i][len/2].south = false;
  FOR(i,1,len/2 + 1) res[i][len/2].north = false;
  FOR(i,0, len / 2) {
    FOR(j, 0, len) {
      flip_vert(res[i][j], res[len - 1 - i][j]);
    }
  }
  res[len/2][len/2].south = false;
  FOR(j,0,len - 1) res[len/2][j].east = false;
  FOR(j,1,len) res[len/2][j].west = false;
}

void check(vector<vector<cell>> &c) {
  FOR(i,0,sz(c) - 1) {
    FOR(j,0,sz(c[i]) - 1) {
      assert(c[i][j].south == c[i+1][j].north);
      assert(c[i][j].east == c[i][j+1].west);
    }
  }
}
  

int main() {
  ios_base::sync_with_stdio(false);
 
  ll x_size, y_size, queries;
  uint32_t seed;
  cin >> x_size >> y_size >> queries >> seed;

  assert(2 <= x_size <= MAX_SIZE);
  assert(2 <= y_size <= MAX_SIZE);
  assert(2 <= queries <= MAX_QUERIES);

  ll bigger = max(x_size, y_size), s = 2;
  while(s <= bigger) s = s << 1;


  vector<vector<cell>> c(s-1,vector<cell>(s-1));
  ll len = 2;
  while(len-1 != sz(c)) {
    len = len << 1;
    doubl(c,len - 1);
    check(c);
  }
  //print(c);

  ll change_size = 1;
  while(s - change_size > x_size) change_size = change_size << 1;
  x_size = s - change_size;
  assert(x_size >= 2);

  change_size = 1;
  while(s - change_size > y_size) change_size = change_size << 1;
  y_size = s - change_size;
  assert(y_size >= 2);
  cout << y_size << " " << x_size << endl;

  c.resize(y_size);
  FOR(i,0,y_size) {
    c[i].resize(x_size);
    c[i][x_size - 1].east = true;
  }
  FOR(j,0,x_size) {
    c[y_size - 1][j].south = true;
  }
  print(c);
  
  cout << queries << endl;
  srand(seed);
  ll last_x = -1, last_y = -1;
  FOR(i, 0, queries) {
    ll x,y;
    do {
      x = rand() % x_size;
      y = rand() % y_size;
    } while(x == last_x && y == last_y);
    last_x = x; last_y = y;
    cout << y + 1 << " " << x + 1 << endl;
  }


  return 0;
}
