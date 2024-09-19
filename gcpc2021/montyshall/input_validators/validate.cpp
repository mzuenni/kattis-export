#include <iostream>
using namespace std;

const long long MIN_X = 1;
const long long MAX_X = 1000 * 1000;

int main() {
  long long d,s,e;
	if(!(cin >> d >> s >> e)) return 43;
	if(s < MIN_X || e < MIN_X || d < MIN_X || MAX_X < s || MAX_X < e || MAX_X < d) return 43;
	if(s + e < d) return 42;
  return 43;
}
