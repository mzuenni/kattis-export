#include <algorithm>
#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    string s;
    cin >> n >> s;
    array<int, 3> cnt = {};
    string colours = "rgb";
    for (char c : s) {
        cnt[colours.find(c)]++;
    }
    sort(cnt.begin(), cnt.end());

    long double p = 1 / powl(2, cnt[0]);
    long double ans = 1.5L * cnt[0];
    for (int i=0; i<=cnt[0]; i++) {
        ans += p * min(i+cnt[1], n - (i+cnt[1])) * 3;
        p = p * (cnt[0]-i) / (i+1);
    }

    cout << setprecision(42) << ans << '\n';
}
