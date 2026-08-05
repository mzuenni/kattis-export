//Author: Stefan Toman

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main() {
  vector< vector<long long> > a(2, vector<long long>(2));
  stringstream ss;
  cin >> a[0][0] >> a[0][1] >> a[1][0] >> a[1][1];
  while(a[0][0] != 1 || a[0][1] != 0 || a[1][0] != 0 || a[1][1] != 1) {
    if(a[0][0] > a[0][1] || (a[0][0] == a[0][1] && a[1][0] > a[1][1])) {
      a[0][0] -= a[0][1];
      a[1][0] -= a[1][1];
      ss<<'0';
    }
    else {
      a[0][1] -= a[0][0];
      a[1][1] -= a[1][0];
      ss<<'1';
    }
  }
  string sss = ss.str();
  reverse(sss.begin(), sss.end());
  cout << sss << endl;
  return 0;
}
                      
