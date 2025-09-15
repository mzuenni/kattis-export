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

/**
 * Creates a maze according to Eller's Algorithm
 */

void usage(char* name) {
  cerr << "usage: " << name << " <LENGTH> <WIDTH> <QUERIES> <SEED> [<BIAS>]" << endl;
  cerr << "<LENGTH> must be greater than 0" << endl;
  cerr << "<WIDTH> must be greater than 0" << endl;
  cerr << "<QUERIES> must be greater than 1" << endl;
  cerr << "<SEED> is parsed as unsigned integer" << endl;
  cerr << "<BIAS> must be between 0 and 1" << endl;
  exit(1);
}

void join(vl &row, ll into, ll from) {
  FOR(i, 0, sz(row)) {
    if(row[i] == from) row[i] = into;
  }
}

inline char print_ver(bool is_wall) {
  if(is_wall) return '|';
  return ' ';
}

inline char print_hor(bool is_wall) {
  if(is_wall) return '_';
  return ' ';
}

void print_row(vb &vert, vb &hor) {
  FOR(i, 0, sz(hor)) {
    cout << print_ver(vert[i]) << print_hor(hor[i]);
  }
  cout << print_ver(vert[sz(vert) - 1]) << endl;
}

void create_next_row(vl &cur_row, ll& ind, vb &vert, vb &hor, ld chance, bool last_row) {
  ll width = sz(cur_row);
  map<ll, ll> union_size;
  FOR(j, 0, width){
    if(cur_row[j] == -1) cur_row[j] = ind++;
    union_size[cur_row[j]]++;
  }
  vert[0] = true; vert[width] = true;
  FOR(j, 0, width - 1) {
    if(cur_row[j] == cur_row[j + 1] || (rand() < RAND_MAX * chance && !last_row)) {
      vert[j + 1] = true;
    } else {
      union_size[cur_row[j]] += union_size[cur_row[j + 1]];
      union_size[cur_row[j + 1]] = 0;
      join(cur_row, cur_row[j], cur_row[j + 1]);
    } 
  }

  // no need to create horizontal walls in the last row
  if(last_row) return;

  map<ll, set<ll>> sets;
  FOR(j, 0, width) sets[cur_row[j]].insert(j);
  for(pair<ll, set<ll>> p : sets) {
    set<ll> &cur_set = p.yy;
    // open at least one horizontal wall per set
    ll fail_safe = rand() % sz(cur_set);
    ll index_fail_safe = -1;
    bool one_open = false;
    for(ll index : cur_set) {
      if(fail_safe-- == 0) index_fail_safe = index;
      if(rand() < RAND_MAX * chance){
        one_open = true;
      } else {
        hor[index] = true;
      }
    }
    if(!one_open) hor[index_fail_safe] = false;
  }
  
  // clean up indices in cur_row if horizontal wall is under them
  FOR(j, 0, width) if(hor[j]) cur_row[j] = -1;
}

int main(int argc, char* argv[] ) {
  if(argc < 5 || 6 < argc) usage(argv[0]);
  ll length, width, queries;
  unsigned int seed;
  ld chance = 0.5;
  stringstream ss(argv[1]);
  if(!(ss >> length)) usage(argv[0]);
  ss.str(argv[2]);
  ss.clear();
  if(!(ss >> width)) usage(argv[0]);
  ss.str(argv[3]);
  ss.clear();
  if(!(ss >> queries)) usage(argv[0]);
  ss.str(argv[4]);
  ss.clear();
  if(!(ss >> seed)) usage(argv[0]);
  if(argc == 6) {
    ss.str(argv[5]);
    ss.clear();
    if(!(ss >> chance)) usage(argv[0]);
  }
  if(length < 1 || width < 1 || queries < 2 || chance < 0 || 1 < chance) usage(argv[0]);

  cout << length << " " << width << endl;

  // First row always contains only horizontal walls
  vb first_vert(width + 1, false);
  vb first_hor(width, true);
  print_row(first_vert, first_hor);

  srand(seed);
  ll ind = 0;
  vl cur_row(width, -1);
  FOR(i, 0, length - 1) {
    vb hor(width, false);
    vb vert(width + 1, false);
    create_next_row(cur_row, ind, vert, hor, chance, false);
    print_row(vert, hor);
  }
  vb last_vert(width + 1, false);
  vb last_hor(width, true);
  create_next_row(cur_row, ind, last_vert, last_hor, chance, true);
  print_row(last_vert, last_hor);

  cout << queries << endl;

  ll last_x = -1, last_y = -1;
  FOR(i, 0, queries) {
    ll x,y;
    do {
    x = rand() % width;
    y = rand() % length;
    } while(x == last_x && y == last_y);
    last_x = x; last_y = y;
    cout << y + 1 << " " << x + 1 << endl;
  }
	return 0;
}
