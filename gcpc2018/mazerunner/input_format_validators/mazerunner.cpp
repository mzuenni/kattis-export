#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

#define xx first
#define yy second
#define MAZE_SIZE 1000
#define QUERY_SIZE 10000

vector<pll> valid_moves = {{0,-1},{-1,0},{0,1},{1,0}};

void check(vector<string> &maze, vector<vector<bool>> &visited, stack<tuple<ll,ll,ll>> &s) {
  ll x, y, from;
  while(!s.empty()) {
    tie(x,y,from) = s.top();
    s.pop();
    visited[x][y] = true;
    for(int i = 0; i < 4; i++) {
      // ignore path where we came from
      if(i == from)
        continue;
      //0 -> north
      if(i == 0 && maze[y][2 * x + 1] == '_')
        continue;
      // 1 -> west
      if(i == 1 && maze[y + 1][2 * x] == '|')
        continue;
      // 2 -> south
      if(i == 2 && maze[y + 1][2 * x + 1] == '_')
        continue;
      // 3 -> east
      if(i == 3 && maze[y + 1][2 * x + 2] == '|')
        continue;

      pll move = valid_moves[i];
      if(visited[x + move.xx][y + move.yy]) {
        cerr << "found loop at position " << x << " " << y << " checking " << i <<  endl;
        exit(43);
      }
      s.push(make_tuple(x + move.xx, y + move.yy, (ll)(i - 2 < 0 ? i + 2 : i - 2)));
    }
  }
}

int main() {

  string line;

  if(!getline(cin, line))
    exit(43);

  stringstream ss;
  ss.str(line);
  ll l, w;

  if(!(ss >> l >> w))
    exit(43);
  if(l < 2 || 1000 < l)
    exit(43);
  if(w < 2 || 1000 < w)
    exit(43);

  vector<string> maze(l + 1);
  vector<vector<bool>> visited(w, vector<bool>(l, false));

  for(ll i = 0; i < l + 1; i++) {
    if(!getline(cin, maze[i])) {
      cerr << "unexpected eof" << endl;
      exit(43);
    }
    if(maze[i].size() != 2 * w + 1) {
      cerr << "wrong dimension in line " << i << endl;
      exit(43);
    }
    for(ll j = 0; j < 2 * w + 1; j++) {
      char c = maze[i][j];
      if(j % 2 == 0) {
        // vertical walls
        if((j == 0 || j == 2 * w) && i != 0) {
          // must be enclosed
          if(c != '|') { cerr<< "enclosure not right pos" << i << " " << j << endl; exit(43);}
        } else {
          if(c != '|' && c != ' ') { cerr<< "enclosure not right pos" << i << " " << j << endl; exit(43);}
        }
      } else {
        // horizontal walls
        if(i == 0 || i == l) {
          // must be enclosed
          if(c != '_') {cerr<< "enclosure not right pos" << i << " " << j << endl;exit(43);}
        } else {
          if(c != '_' && c != ' ') {cerr<< "enclosure not right pos" << i << " " << j << endl;exit(43);}
        }
      }
    }
  }

  // check maze at 0/0 pretending to have come from north
  stack<tuple<ll,ll,ll>> st;
  st.push(make_tuple(0LL,0LL,0LL));
  check(maze, visited, st);

  // check if every module was reached
  for(ll i = 0; i < w; i++) {
    for(ll j = 0; j < l; j++) {
      if(!visited[i][j]) {
        cerr << "Position " << i << "/" << j << " was not visited." << endl;
        exit(43);
      }
    }
  }


  if(!getline(cin, line))
    exit(43);
  ss.clear();
  ss.str(line);
  ll m, last_x = -1, last_y = -1;
  if(!(ss >> m))
    exit(43);
  for(ll i; i < m; i++) {
    if(!getline(cin, line))
      exit(43);
    ss.clear();
    ss.str(line);
    ll x, y;
    if(!(ss >> y >> x))
      exit(43);
    if(x < 1 || w < x)
      exit(43);
    if(y < 1 || l < y)
      exit(43);
    // same position does not appear more than once in a row
    if(last_x == x && last_y == y)
      exit(43);
    last_x = x;
    last_y = y;
  }

  exit(42);
}
