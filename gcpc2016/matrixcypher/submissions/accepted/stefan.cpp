//Author: Stefan Toman

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

string sub(string a, string b) {
  if(a.size() == 0) return "";
  string aa = a.substr(0, a.size()-8);
  string ba = b.substr(0, b.size()-8);
  int ae = stoi(a.substr(a.size()-8));
  int be = stoi(b.substr(b.size()-8));
  int d = ae - be;
  if(d < 0) {
    d += 100000000;
    string one = "00000001";
    while(one.size() < aa.size()) one = "00000000" + one;
    aa = sub(aa, one);
  }
  stringstream t;
  t << d;
  string tt;
  t >> tt;
  while(tt.size() < 8) tt = "0" + tt;
  return sub(aa, ba) + tt;
}

int main() {
  vector< vector<string> > a(2, vector<string>(2));
  stringstream ss;
  cin >> a[0][0] >> a[0][1] >> a[1][0] >> a[1][1];
  int l = max(max(a[0][0].size(), a[0][1].size()), max(a[1][0].size(), a[1][1].size()));
  while(l % 8 != 0) l++;
  for(int i = 0; i <= 1; i++) for(int j = 0; j <= 1; j++) while(a[i][j].size() < l) a[i][j] = "0" + a[i][j];
  vector<string> c(2);
  c[0] = "0"; c[1] = "1";
  for(int i = 0; i <= 1; i++) while(c[i].size() < l) c[i] = "0" + c[i];
  
  
  while(a[0][0] != c[1] || a[0][1] != c[0] || a[1][0] != c[0] || a[1][1] != c[1]) {
    if(a[0][0] > a[0][1] || (a[0][0] == a[0][1] && a[1][0] > a[1][1])) {
      a[0][0] = sub(a[0][0], a[0][1]);
      a[1][0] = sub(a[1][0], a[1][1]);
      ss<<'0';
    }
    else {
      a[0][1] = sub(a[0][1], a[0][0]);
      a[1][1] = sub(a[1][1], a[1][0]);
      ss<<'1';
    }
  }
  string sss = ss.str();
  reverse(sss.begin(), sss.end());
  cout << sss << endl;
  return 0;
}
                      
