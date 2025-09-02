#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define FOR(i,a,b) for(ll i = (a); i < (b); i++)

void create_tree_balanced(ll start, ll end) {
  if(end < start) return;
  ll mid = (start + end) / 2;
  cout << mid << " ";
  create_tree_balanced(start, mid - 1);
  create_tree_balanced(mid + 1, end);
}
void create_tree(ll start, ll end, ll depth_rem) {
  if(depth_rem <= 0) {create_tree_balanced(start, end); return;}
  ll mid = (start + end) / 2;
  ll first_borrow = max(start, mid - depth_rem);
  FOR(i, first_borrow, mid + 1) cout << i << " ";
  create_tree_balanced(start, first_borrow - 1);
  create_tree(mid + 1, end, depth_rem - mid + first_borrow);
}

int main() {
	ios_base::sync_with_stdio(false);
  ll n,k;
  cin >> n >> k;
  for(ll i = n; i > 0; i /= 2) k--;
  if(k < 0) { cout << "impossible" << endl; return 0;}
  create_tree(1,n,k);
  cout << endl;
  cout << '.';
	return 0;
}
