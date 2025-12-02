#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

int main() {
	int n;
	cin >> n;
	map<string, int> count_general;
	vector<map<string, int>> count_top_k(10);
	for (int i = 0; i < n; i++) for (int j = 0; j < 10; j++) {
		string s;
		cin >> s;
		count_general[s]++;
		count_top_k[j][s]++;
	}
	int best_result = 0;
	for (auto [s, r]: count_general) best_result = max(best_result, r);
	set<string> candidates;
	for (auto [s, r]: count_general) {
		if (r == best_result) candidates.insert(s);
	}
	for (int i = 0; i < 10 && (int) candidates.size() > 1; i++) {
		set<string> ncand;
		int br = 0;
		for (auto [s, r]: count_top_k[i]) if (candidates.count(s)) br = max(br, r);
		for (auto [s, r]: count_top_k[i]) if (candidates.count(s)) {
			if (r == br) ncand.insert(s);
		}
		if ((int) ncand.size() > 0) candidates = ncand;
	}
	if ((int) candidates.size() > 1) {
		cout << "tie\n";
	} else {
		cout << *candidates.begin() << '\n';
	}
}