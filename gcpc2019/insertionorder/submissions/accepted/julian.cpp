#include <bits/stdc++.h>

using namespace std;

void build(int n, int k, int start = 1)
{
    if (start > n) return;
    if (k == 1) {
        cout << start << " ";
    } else {
        int t = min(n, start + max(k - 1, (n - start + 1) / 2));
        cout << t << " ";
        build(t - 1, k - 1, start);
        build(n, k - 1, t + 1);
    }
}

int main()
{
    int n, k;
    cin >> n >> k;
    if (k < 60 && (1ll << k) <= n) {
        cout << "impossible\n";
    } else {
        build(n, k);
        cout << endl;
    }
}
