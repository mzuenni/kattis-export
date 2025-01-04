#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int N = 265432;

template<typename F>
void sums(vector<int> a, F f) {
    int n = size(a);
    vector<i64> s = {0};
    for (int i = 0; i < n; i++) {
        for (int mask = 0; mask < (1 << i); mask++) {
            s.push_back(s[mask] + a[i]);
        }
    }

    for (int mask = 0; mask < (1 << n); mask++) {
        for (int smask = mask; ; smask = (smask-1) & mask) {
            f(smask, mask^smask, s[smask] - s[mask^smask]);
            if (smask == 0) break;
        }
    }
}

void print_mask(int mask) {
    cout << __builtin_popcount(mask);
    for (int i = 0; i < 28; i++) if (mask & (1 << i)) {
        cout << ' ' << i+1;
    }
    cout << '\n';
}

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a[i] = x*N + y;
    }

    n = min(n, 28);
    int m = n/2;
    vector<int> aL(begin(a), begin(a)+m);
    vector<int> aR(begin(a)+m, begin(a)+n);

    vector<i64> sumL, sumR;
    sums(aL, [&](int mask1, int mask2, i64 cur) { sumL.push_back(cur); });
    sums(aR, [&](int mask1, int mask2, i64 cur) { sumR.push_back(cur); });
    sort(begin(sumL), end(sumL));
    sort(begin(sumR), end(sumR));

    int p = 0, q = 0;
    while (p < ssize(sumL) && q < ssize(sumR)) {
        i64 diff = sumL[p] - sumR[q], val = sumL[p];
        if (diff == 0 && val != 0) {
            int maskL1, maskL2, maskR1, maskR2;
            sums(aL, [&](int mask1, int mask2, i64 cur) { if (cur == val) maskL1 = mask1, maskL2 = mask2; });
            sums(aR, [&](int mask1, int mask2, i64 cur) { if (cur == val) maskR1 = mask2, maskR2 = mask1; });
            cout << "no" << '\n';
            print_mask(maskL1 | (maskR1 << m));
            print_mask(maskL2 | (maskR2 << m));
            return 0;
        }
        (diff < 0 ? p : q)++;
    }
    cout << "yes" << '\n';
}
