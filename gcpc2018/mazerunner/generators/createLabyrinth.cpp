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

const vector<pll> moves = {{0,1},{1,0},{0,-1},{-1,0}}; // nort, west, south, east
const ll flip_dir[] = {2,3,0,1};
const ll empty = sz(moves);
const ll allocated = sz(moves) + 1;

inline char p_hor(bool h) {
  return h ? '_' : ' ';
}

inline char p_vert(bool v) {
  return v ? '|' : ' ';
}

void flip(vector<vb> &vec, size_t start, size_t end) {
  while(start < end) {
    FOR(i,0,sz(vec)) {
      swap(vec[i][start], vec[i][end]);
    }
    start++;
    end--;
  }
}

void flip(vector<vb> &vec) {
  flip(vec, 0, sz(vec[0]) - 1);
}

void flip(vector<vb> &vec, size_t start) {
  flip(vec, start, sz(vec[0]) - 1);
}


void print(vvl &bitmap) {
  if(!DEBUG) return;
  FOR(i,0,sz(bitmap[0])){
    FOR(j,0,sz(bitmap)){
      cerr << bitmap[j][i];
    }
    cerr << endl;
  }
  cerr << endl;
}

void print(vector<vb> &bitmap) {
  if(!DEBUG) return;
  FOR(i,0,sz(bitmap[0])){
    FOR(j,0,sz(bitmap)){
      cerr << bitmap[j][i];
    }
    cerr << endl;
  }
  cerr << endl;
}
inline pll border(ll n, ll offset) {
  ll x = FAKT*n;
  ll y = x-n;
  if(offset > 0) {
    if(offset <= n) {
      x += offset;
    } else {
      x += n; offset -=n;
      if(offset <= 2*n) {
        y += offset;
      } else {
        y += 2*n;
        offset -= 2*n;
        x -= offset;
      }
    }
  } else {
    offset *= -1;
    if(offset <= n) {
      x -= offset;
    } else {
      x -= n; offset -=n;
      if(offset <= 2*n) {
        y += offset;
      } else {
        y += 2*n;
        offset -= 2*n;
        x += offset;
      }
    }
  }
  return mp(x,y);
}

inline ll coord(ll x, ll y, ll n) {
  return y * n + x;
}

inline pll m_coord(ll c, ll n) {
  return mp(c % n, c/n);
}

void connect(vvl &b, ll x, ll y, ll tgt_x, ll tgt_y, ll mid) {
  priority_queue<tuple<ll, ll, ll, ll>> q;
  vvl bitmap(b);
  ll length = 0, from = allocated;
  q.push(mt(length,x,y,from));
  do {
    tie(length, x, y, from) = q.top();
    q.pop();
    if(bitmap[x][y] != empty) continue;
    bitmap[x][y] = from;
    FOR(i,0,sz(moves)) {
      pll move = moves[i];
      ll new_x = x + move.xx;
      ll new_y = y + move.yy;
      if(new_x < 0 || new_x >= sz(bitmap) || new_y < 0 || new_y >= sz(bitmap)) continue;
      if(i == 1 && y > mid) continue;
      if(bitmap[new_x][new_y] != empty) continue;
      q.push(mt(length - 1, new_x, new_y, i));
    }
  }while(x != tgt_x || y != tgt_y);
  ll dir = bitmap[x][y];
  b[x][y] = dir;
  while(dir != allocated) {
    pll move = moves[flip_dir[dir]];
    x = x + move.xx; y = y + move.yy;
    dir = bitmap[x][y];
    b[x][y] = dir;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  ll n, queries;
  unsigned int seed;
  cin >> n >> queries >> seed;
  assert(n > 0 && queries > 0 && queries <= MAX_QUERIES);
  vvl bitmap(2*FAKT*n, vl(2*FAKT*n, empty));
  ll mid = FAKT*n;
  FOR(i,(FAKT-1)*n + 1,(FAKT+1)*n) {
    FOR(j,(FAKT-1)*n + 1, (FAKT+1)*n) {
      bitmap[i][j] = allocated;
    }
  }

  print(bitmap);

  pll s = border(n,0);
  pll t = border(n,1);
  ll ind = 0;
  while(s.xx < t.xx) {
    cerr << "Connecting " << ind + 1<< "/" << 4*n << endl;
    connect(bitmap, s.xx, s.yy, t.xx, t.yy, mid);
    ind++;
    s = border(n, -ind);
    t = border(n, ind + 1);
    print(bitmap);
  }

  ll size_x = -1, size_y = -1;
  ll start_x = oo, start_y = oo;

  FOR(x,0,sz(bitmap)){
    FOR(y,0,sz(bitmap[x])){
      if(bitmap[x][y] != empty) {
        start_x = min(start_x, x);
        start_y = min(start_y, y);
        size_x = max(size_x, x - start_x + 1);
        size_y = max(size_y, y - start_y + 1);
      }
    }
  }
  if(DEBUG)
    cerr << "x/y " << start_x << "/" << start_y << " len/heig " << size_x << "/" << size_y << endl;

  vector<vb> vert(size_x, vb(size_y, false));
  vector<vb> hor(size_x, vb(size_y, false));
  FOR(i,1,size_y) {
    vert[0][i] = true;
    vert[size_x - 1][i] = true;
  }
  FOR(i,0,size_x) {
    hor[i][0] = true;
    hor[i][size_y - 1] = true;
  }

  FOR(x,0,size_x){
    FOR(y,0,size_y) {
      switch(bitmap[start_x + x][start_y + y]) {
        case(0):
          vert[x][y] = true;
          break;

        case(1):
          hor[x-1][y] = true;
          break;

        case(2):
          vert[x][y+1] = true;
          break;

        case(3):
          hor[x][y] = true;
          break;
      }
    }
  }


  FOR(i,(FAKT-1)*n + 1,(FAKT+1)*n) {
    FOR(j,(FAKT-1)*n + 1, (FAKT+1)*n) {
      if(i >= j) {
        if(i <= (2 * FAKT) * n - j) {
          vert[i - start_x][j - start_y] = true;
        }
        if(i >= (2 * FAKT) * n - j) {
          hor[i - start_x][j - start_y] = true;
        }
      }

      if(i <= j) {
        if(i <= (2 * FAKT) * n - j) {
          hor[i - start_x - 1][j - start_y] = true;
        }
        if(i >= (2 * FAKT) * n - j) {
          vert[i - start_x][j - start_y + 1] = true;
        }
      }
    }
  }
  flip(hor);
  flip(vert, 1);
  print(hor);
  print(vert);
  cout << size_y - 1 << " " << size_x - 1 << endl;
  FOR(y,0,size_y) {
    FOR(x,0,size_x) {
      cout << p_vert(vert[x][y]);
      if(x != size_x -1)
        cout << p_hor(hor[x][y]);
    }
    cout << endl;
  }
  cout << queries << endl;
  if(seed == 0) {
    bool print_mid = true;
    FOR(i,0,queries) {
      if(print_mid) {
        cout << 3*n << " " << 4*n << endl;
      } else {
        cout << "1 1" << endl;
      }
      print_mid = !print_mid;
    }
  } else {
    srand(seed);
    ll last_x = -1, last_y = -1;
    FOR(i, 0, queries) {
      ll x,y;
      do {
        x = rand() % (size_x -1);
        y = rand() % (size_y -1);
      } while(x == last_x && y == last_y);
      last_x = x; last_y = y;
      cout << y + 1 << " " << x + 1 << endl;
    }
  }


  return 0;
}
