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
 * Correcting Cheeseburgers Time Limit
 * BFS of depth > 2 should result in TLE. 
 */

void bit(string& in, int b, int e, int p)
{
  string sa = in.substr(0, b);
  string sb = in.substr(b, e-b);
  string sc = in.substr(e, p-e);
  string sd = in.substr(p);
  in = sc + sa + sd + sb;
}

unordered_set<string> dist_t;

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
  
  dist_t.insert(s);
  int depth = 0;
  queue<string> q;
  q.push(s);
  while(!q.empty())
  {
    int size = q.size();
    depth++;
    for(int i=0;i<size;i++)
    {
      string v = q.front();
      q.pop();      
      for(int b=0;b<=N;b++) for(int e=b;e<=N;e++) for(int p=e;p<=N;p++)
      {
        string c = v;
        bit(c,b,e,p);
        if(c == t)
        {
			cout << depth << "\n";
			return 0;
		}
        if(dist_t.count(c) == 0)
        {
          dist_t.insert(c);
          q.push(c);
        }
      }
    }
  }
  
  return 0;
}
