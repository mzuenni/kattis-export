#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <stack>
#include <queue>
#include <map>
#include <climits>
#include <cstdio>
#include <set>
#include <unordered_set>
using namespace std;
#define db(a) (cout << (#a) << " = " << (a) << endl)
typedef long long ll;

/*
 * Correcting Cheeseburgers
 * Bidirectional BFS & maxPath = 6
 */

void bit(string& in, int b, int e, int p)
{
  string sa = in.substr(0, b);
  string sb = in.substr(b, e-b);
  string sc = in.substr(e, p-e);
  string sd = in.substr(p);
  in = sc + sa + sd + sb;
}

void inv_bit(string& in, int b, int e, int p)
{
  string sa = in.substr(0, b);
  string sb = in.substr(b, e-b);
  string sc = in.substr(e, p-e);
  string sd = in.substr(p);
  in = sb + sd + sa + sc;
}

unordered_set<string> dist_t1, dist_t2, dist_s1, dist_s2;

int main()
{
  ios_base::sync_with_stdio(false);  
  
  string s,t;
  int N;
  cin >> N;
  stringstream ss;  
  for(int i=0;i<N;i++)
  {
	int x;
	cin >> x;
	s.append(1, (x-1) + '0');
	t.append(1, i + '0');
  }
  
  if(s == t)
  {
	  cout << "0\n";
	  return 0;
  }
  
  // 1. step forward
  bool found = false;
  for(int i=0;i<N;i++) for(int j=i;j<N;j++) for(int k=j;k<=N;k++)
  {
	string c = s;
	bit(c,i,j,k);
	if(c == t) found = true;
	dist_s1.insert(c);
  }
  if(found) {cout << "1\n"; return 0;}
  // 2. step forward
  for(auto& s1 : dist_s1) for(int i=0;i<N;i++) for(int j=i;j<N;j++) for(int k=j;k<=N;k++)
  {
	string c = s1;
	bit(c,i,j,k);
	if(c == t) found = true;
	dist_s2.insert(c);
  }
  if(found) {cout << "2\n"; return 0;}
  // 1. step back
  for(int i=0;i<N;i++) for(int j=i;j<N;j++) for(int k=j;k<=N;k++)
  {
	string c = t;
	inv_bit(c,i,j,k);
	if(dist_s2.count(c) > 0) found = true;
	dist_t1.insert(c);
  }
  if(found) {cout << "3\n"; return 0;}
  // 2. step back
  for(auto& t1 : dist_t1) for(int i=0;i<N;i++) for(int j=i;j<N;j++) for(int k=j;k<=N;k++)
  {
	string c = t1;
	inv_bit(c,i,j,k);
	if(dist_s2.count(c) > 0) found = true;
	dist_t2.insert(c);
  }
  if(found) {cout << "4\n"; return 0;}
  // 3. step back
  for(auto& t2 : dist_t2) for(int i=0;i<N;i++) for(int j=i;j<N;j++) for(int k=j;k<=N;k++)
  {
	string c = t2;
	inv_bit(c,i,j,k);
	if(dist_s2.count(c) > 0) found = true;
  }
  if(found) cout << "5\n";
  else cout << "6\n";
  
  return 0;
}
