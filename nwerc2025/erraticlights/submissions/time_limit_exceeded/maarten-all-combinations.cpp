#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;

    unordered_map<char, int> cnt;
    for (char ch : s) cnt[ch]++;

    vector<int> counts;
    counts.reserve(cnt.size());
    for (auto &p : cnt) counts.push_back(p.second);
    sort(counts.begin(), counts.end());


    if (counts.size() == 1) {
        cout << 0 << '\n';
    } else if (counts.size() == 2) {
        cout << 3LL * counts[0] << '\n';
    } else {
        long long a = counts[0];
        long long b = counts[1];
        long long c = counts[2];

        long double res = 1.5L * a; // expected steps for first phase

        unsigned long long total = 1ULL << a;
        long double sum_val = 0.0L;
        for (unsigned long long i = 0; i < total; ++i) {
            int ones = __builtin_popcountll(i);
            long long option1 = b + ones;
            long long option2 = c + (int)(a - ones);
            sum_val += 3.0L * (long long)min(option1, option2);
        }
        res += sum_val / (long double)total;

        cout << setprecision(42) << res << endl;
    }
}
