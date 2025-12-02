#include "validate.h"
using namespace OutputValidator;

constexpr Integer LIM = 10'001;
inline const std::regex ANS_PATTERN("splittable", std::regex::nosubs | std::regex::optimize);

// O(LIM^2/64)
bool representable(Integer k, const std::vector<Integer>& coins) {
	if (k >= LIM) juryOut << "k too large: " << k << FAIL;
	std::bitset<LIM> dp;
	dp[0] = 1;
	for (Integer c : coins) dp |= dp << c;
	return dp[k];
}

/*
// O(LIM*log(LIM)/64) => should handle LIM = 10^7
bool representable(Integer k, const std::vector<Integer>& coins) {
	if (k >= LIM) juryOut << "k too large: " << k << FAIL;
	std::map<Integer, Integer> count;
	for (Integer c : coins) count[c]++;
	std::bitset<LIM> dp;
	dp[0] = 1;
	for (auto [c, n]: count) {
		for (Integer i = 1; n > 0; i *= 2) {
			dp |= dp << (std::min(i, n) * c);
			n -= i;
		}
	}
	return dp[k];
}*/

/*
// O(LIM) => should handle LIM = 10^7
bool representable(Integer k, const std::vector<Integer>& coins) {
	if (k >= LIM) juryOut << "k too large: " << k << FAIL;
	std::map<Integer, Integer> count;
	for (Integer c : coins) count[c]++;
	std::bitset<LIM> dp;
	dp[0] = 1;
	for (auto [c, n]: count) {
		std::bitset<LIM> next;
		for (Integer j = 0; j < c; j++) {
			Integer active = 0;
			for (Integer i = j; i <= k; i += c) {
				active += dp[i];
				next[i] = active > 0;
				if (i >= n*c) active -= dp[i - n*c];
			}
		}
		dp = next;
	}
	return dp[k];
}*/

bool read(Integer n, InputStream& in, std::string_view who, Verdict onError) {
	std::string ans = "unsplittable";
	
	if(isalpha(static_cast<unsigned char>(in.peek()))) {
		ans = in.string(ANS_PATTERN);
		if (caseSensitive && !isLower(ans)) juryOut << who << ": wrong case" << onError;
		in.newline();
		toLower(ans);
	}
	
	
	if (ans == "splittable") {
		in.eof();
		return false;
	}
	Integer k = in.integer(1, n+1);
	in.newline();
	auto selected = in.integers(k, 1, 501);
	Integer sum = 0;
	for (Integer x : selected) {
		if (x !=   1 && x !=   2 && x !=   5 &&
			x !=  10 && x !=  20 && x !=  50 &&
			x != 100 && x != 200 && x != 500) {
			juryOut << who << ": selected invalid coin value: " << x << onError;
		}
		sum += x;
	}
	if (sum != n) juryOut << who << ": got " << sum << " as sum, but expected " << n << onError;
	in.newline();
	in.eof();
	if (n % 2 == 0 && representable(n / 2, selected)) juryOut << who << ": answer is invalid" << onError;
	return true;
}

int main(int argc, char **argv) {
	init(argc, argv);

	Integer n = testIn.integer();

	bool jury = read(n, juryAns, "Jury", FAIL);
	bool team = read(n, teamAns, "Team", WA);

	if (!jury && team) juryOut << "team found valid solution but jury not" << FAIL;
	if (jury && !team) juryOut << "jury found valid solution but team not" << WA;
	teamOut << "ok" << AC;
}
