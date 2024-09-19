#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print(long long number) {
	printf("+%lld.%02lld", number / 100, number % 100);
}

int main() {
	long long n;
	cin >> n;
	vector<pair<long long, pair<long long, long long>>> entries(n);
	while(n--) {
		string s_p;
		long long  p, b, s;
		cin >> s_p >> b >> s;
		size_t p_len = s_p.length();
		p = stoll(s_p.substr(0,p_len -3)) * 100 + stoll(s_p.substr(p_len - 2, 2));
		entries[n] = {p, {b, s}};
	}
	sort(entries.begin(), entries.end());
	for(size_t i = 1; i < entries.size(); ++i) {
		entries[i].second.second += entries[i - 1].second.second;
	}
	for(size_t i = entries.size() - 1; i > 0;) {
		entries[--i].second.first += entries[i].second.first;
	}
	long long turnover = 0, price = 0;
	for(pair<long long, pair<long long, long long>> &entry : entries) {
		long long this_turnover = min(entry.second.first, entry.second.second) * entry.first;
		if(this_turnover > turnover) {
			turnover = this_turnover;
			price = entry.first;
		}
	}
	if(turnover == 0) {
		printf("impossible\n");
	} else {
		print(price); printf(" "); print(turnover); printf("\n");
	}
	return 0;
}
