#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    int n;
    cin >> n;
    n = min(n, 30);

    if (n == 1) cout << "100 0\n";
    else {
        pair<int, int> result{0, 1};
        for (int i = 2; i < n; ++i) result = {result.second, result.first * 2 + result.second};
        double r = 100 * static_cast<double>(result.first) / (1 << (n - 2));
        cout << setprecision(7) << r << " " << 100 - r << "\n";
    }
}
