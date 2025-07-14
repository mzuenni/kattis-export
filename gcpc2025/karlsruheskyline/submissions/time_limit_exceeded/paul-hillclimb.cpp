#include <bits/stdc++.h>
using namespace std;

int vis(vector<int> h, bool is_left) {
    int k = 0, x = 0;
    if (is_left) {
        for (int y: h)
            k += x < y, x = max(x, y);
    } else {
        reverse(h.begin(), h.end());
        for (int y: h)
            k += x < y, x = max(x, y);
    }
    return k;
}

int main() {
    int n, a, b;
    cin >> n >> a >> b;

    if (a+b > n+1 || max(a, b) == 1) {
        cout << "no" << '\n';
        exit(0);
    }
    cout << "yes" << '\n';

    auto score = [&](const vector<int> &h) {
        return abs(vis(h, 1) - a) + abs(vis(h, 0) - b);
    };

    mt19937_64 gen(987);

    vector<int> h(n);
    iota(begin(h), end(h), 1);
    shuffle(begin(h), end(h), gen);

    int s = score(h);
    while (s > 0) {
        int i = gen() % n, j = gen() % n;
        swap(h[i], h[j]);
        int t = score(h);
        if (t < s) s = t;
        else swap(h[i], h[j]);
    }
    for (int x: h) cout << x << ' ';
    cout << '\n';
}
