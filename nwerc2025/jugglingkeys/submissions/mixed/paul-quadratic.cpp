// @EXPECTED_RESULTS@: ACCEPTED, TIME_LIMIT_EXCEEDED
// This is quadratic, but with a very good constant factor. Not super-realistic
// as an in-contest submission, so it's not that vital that this times out.
#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k, q;
    cin >> n >> k >> q;

    vector<int> a(q), l(q), r(q), i2x;
    for (int i = 0; i < q; i++) {
        cin >> a[i] >> l[i] >> r[i];
        i2x.push_back(l[i]);
        i2x.push_back(r[i]);
    }

    map<int,int> x2i;
    sort(begin(i2x), end(i2x));
    for (int i = 0; i < 2*q; i++) {
        x2i[i2x[i]] = i;
    }

    for (int i = 0; i < q; i++) {
        l[i] = x2i[l[i]];
        r[i] = x2i[r[i]];
    }

    vector<int> at_home(2*q, n);
    for (int i = 0; i < q; i++) {
        for (int j = l[i]; j <= r[i]; j++) {
            at_home[j]--;
        }
    }

    vector<int> res(q), keys_at_home(2*q, k);
    for (int i = 0; i < q; i++) {
        res[i] = at_home[r[i]] == 0;
        if (res[i]) {
            for (int j = l[i]; j <= r[i]; j++) {
                if (--keys_at_home[j] < 0) {
                    cout << "impossible" << '\n';
                    return 0;
                }
            }
        }
    }

    for (int x: res) cout << x;
    cout << '\n';
}
