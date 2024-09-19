#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

const long long MIN_N = 1;
const long long MAX_N = 100 * 1000;
const long long MIN_SB = 0;
const long long MAX_SB = 1000 * 1000;
const long long MIN_P = 1;
const long long MAX_P = 10 * 1000 * 100;

long long safe_parse(const string& to_parse) {
	try {
		size_t idx;
		long long a = stoll(to_parse, &idx, 10);
		if(idx != to_parse.size())
			exit(43);
		return a;
	} catch(...) {
		exit(43);
	}
}

int main() {
	long long n;
	if(!(cin >> n)) return 43;
	if(n < MIN_N || MAX_N < n) return 43;
	unordered_set<long long> prices;
	while(n--) {
		string s_p;
		long long p, b, s;
		if(!(cin >> s_p >> b >> s)) return 43;
		size_t p_size = s_p.length();
		if(s_p[p_size - 3] != '.') return 43;

		p = 100 * safe_parse(s_p.substr(0, p_size - 3)) + safe_parse(s_p.substr(p_size - 2, 2));
		if(p < MIN_P || MAX_P < p) return 43;
		if(b < MIN_SB || MAX_SB < b || s < MIN_SB || MAX_SB < s) return 43;
		if(b == 0 && s == 0) return 43;

		if(prices.find(p) != prices.end()) return 43;
		prices.insert(p);
	}
	char foo;
	if(cin >> foo) return 43;
	return 42;
}
