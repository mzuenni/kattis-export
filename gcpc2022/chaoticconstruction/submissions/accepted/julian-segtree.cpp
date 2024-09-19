#include <bits/stdc++.h>
using namespace std;

class segtree {
private:
    vector<bool> values;
    size_t size;

    int parent(int i) {
        return i / 2;
    }
    int left(int i) {
        return 2 * i;
    }
    int right(int i) {
        return 2 * i + 1;
    }

    void update(int i) {
        if (i >= 1) {
            values[i] = min(values[left(i)], values[right(i)]);
            update(parent(i));
        }
    }

    // Query sum of interval [i, j)
    // current_node represents the interval [l, r)
    long long query(int i, int j, int l, int r, int current_node) {
        if (r <= i || j <= l) return true; // current interval and query interval don't intersect
        if (r <= j && i <= l) return values[current_node]; // current interval contained in query interval

        int m = (l + r) / 2;
        return min(query(i, j, l, m, left(current_node)), query(i, j, m, r, right(current_node)));
    }

public:
    segtree(size_t n) {
        size = 1;
        while (size < n) size *= 2;
        values.assign(2 * size, true);
    }

    // Query sum of interval [i, j)
    long long query(int i, int j) {
        return query(i, j, 0, size, 1);
    }

    // Set value at position i to val
    void update(int i, long long val) {
        values[i + size] = val;
        update(parent(i + size));
    }
};

int main()
{
    int n, q;
    cin >> n >> q;

    segtree s(2 * n);
    while (q--) {
        char c;
        cin >> c;
        if (c == '?') {
            int a, b;
            cin >> a >> b;
            --a; --b;
            if (a > b) swap(a, b);
            if (s.query(a, b + 1) || s.query(b, a + n + 1)) {
                cout << "possible\n";
            } else {
                cout << "impossible\n";
            }
        } else {
            int a;
            cin >> a;
            --a;
            if (c == '-') {
                s.update(a, 0);
                s.update(a + n, 0);
            } else {
                s.update(a, 1);
                s.update(a + n, 1);
            }
        }
    }
}
