//
// Created by niko on 5/4/25.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  string t;
  cin >> t;
  if (t[0] == 'E') {
    int YYY;
    cin >> YYY;
    string s;
    cin >> s;
    auto o = std::count(s.begin(), s.end(), s[0]);
    if (o == s.size()) {
      std::cout << s << '\n';
    } else {
      auto i = find_if_not(s.begin(), s.end(), [&](unsigned char c) { return c == s[0]; });
      for (auto x = s.begin(); x != i; x++) {
        std::cout << '2';
      }
      for (; i != s.end(); i++) {
        std::cout << *i;
      }
      std::cout << '\n';
    }
  } else {
  int YYY; cin >> YYY;
    string s;
    cin >> s;
    auto o = std::count(s.begin(), s.end(), '2');
    if (o == 0) std::cout << s << '\n';
    else {
      auto x = s + s + s;
      auto a = find_if_not(x.begin(), x.end(), [](auto c) { return c == '2'; });
      auto b = find(a, x.end(), '2');
      auto c = find_if_not(b, x.end(), [](auto c) { return c == '2'; });
      for (int k = 0; k < distance(b, c); k++) {
        std::cout << "01"[*c == '0'];
      }
      auto e = b;
      e += s.size();
      for (; c != e; c++) {
        std::cout << *c;
      }
      std::cout << '\n';
    }
  }
}
