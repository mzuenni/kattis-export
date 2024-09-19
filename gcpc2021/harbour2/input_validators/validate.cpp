#include <iostream>
#include <set>
using namespace std;

constexpr int64_t MIN_X = 2;
constexpr int64_t MAX_X = 200'000;

constexpr int64_t MIN_N = 3;
constexpr int64_t MAX_N = MAX_X * 2 + 1;

int main() {
	int64_t n, s1, s2;
	if(!(cin >> n >> s1 >> s2)) return 43;
	if(n < MIN_N || MAX_N < n) return 43;
	if(s1 < MIN_X || MAX_X < s1) return 43;
	if(s2 < MIN_X || MAX_X < s2) return 43;
	if(s1 + s2 != n + 1) return 43;
	set<int64_t> tracking_no;
	while(s1--) {
		int64_t num;
		if(!(cin >> num)) return 43;
		if(num < 0 || n < num) return 43;
		if(!s1 && !num) return 43;
		tracking_no.insert(num);
	}
	while(s2--) {
		int64_t num;
		if(!(cin >> num)) return 43;
		if(num < 0 || n < num) return 43;
		if(!s2 && !num) return 43;
		tracking_no.insert(num);
	}
	char foo;
	if(cin >> foo) return 43;
	if(tracking_no.size() != n + 1) return 43;
	return 42;
}
