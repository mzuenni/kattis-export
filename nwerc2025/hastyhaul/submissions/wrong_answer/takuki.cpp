#include<iostream>
#include<functional>
using namespace std;

using ull = unsigned long long;

int main() {
    vector C(65, vector(65, 0ULL));
    C[0][0] = 1;
    for (int n = 1; n <= 64; n++) {
        C[n][0] = 1;
        for (int k = 1; k <= n; k++) {
            C[n][k] = C[n - 1][k] + C[n - 1][k - 1];
        }
    }

    function<ull(ull, int, int)> order_of_value = [&](ull x, int n, int k) {
        if (k == 0) {
            return 0ULL;
        } else if (x & (1ULL << (n - 1))) {
            return C[n][k] - 1 - order_of_value(x ^ (1ULL << (n - 1)), n - 1, k - 1);
        } else {
            return order_of_value(x, n - 1, k);
        }
    };

    function<ull(ull, int, int)> find_by_order = [&](ull x, int n, int k) {
        if (k == 0) {
            return 0ULL;
        } else if (x < C[n - 1][k]) {
            return find_by_order(x, n - 1, k);
        } else {
            return (1ULL << (n - 1)) ^ find_by_order(C[n][k] - 1 - x, n - 1, k - 1);
        }
    };

    int t;
    cin >> t;
    while (t--) {
        int h, w, k;
        cin >> h >> w >> k;
        ull x = 0;
        for (int i = 0; i < h; i++) {
            string s;
            cin >> s;
            for (int j = 0; j < w; j++) {
                x |= 1ULL << (i * w + j);
            }
        }

        int n = h * w;
        k = __builtin_popcountll(x);
        if (C[n][k] % 2 == 1) {
            cout << "risky" << endl;
        }

        ull y = find_by_order(order_of_value(x, n, k) ^ 1, n, k);

        for (int i = 0; i < n; i++) {
            if ((x & (1ULL << i)) && !(y & (1ULL << i))) {
                cout << (i % w) + 1 << " " << (i / w) + 1 << endl;
            }
        }
        for (int i = 0; i < n; i++) {
            if (!(x & (1ULL << i)) && (y & (1ULL << i))) {
                cout << (i % w) + 1 << " " << (i / w) + 1 << endl;
            }
        }
    }
    return 0;
}
