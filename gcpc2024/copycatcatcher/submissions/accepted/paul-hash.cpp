#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int N = 1e6 + 10, K = 3;
const int p[K] = {int(1e9) + 7, int(1e9) + 9, int(1e9) + 21};
const int a[K] = {123, 456, 789};
i64 b[K][N];

void precalc() {
    for (int k = 0; k < 3; k++) {
        b[k][0] = 1;
        for (int n = 1; n < N; n++) {
            b[k][n] = a[k]*b[k][n-1] % p[k];
        }
    }
}

struct H {
    int len = 0;
    i64 val[K] = {};

    H() {}
    H(i64 x, int len = 1): len(len) {
        for (int k = 0; k < K; k++) {
            val[k] = (p[k] + x%p[k]) % p[k];
        }
    }

    H operator+(const H &h) const {
        H res(0, len + h.len);
        for (int k = 0; k < 3; k++) {
            res.val[k] = (b[k][h.len] * val[k] + h.val[k]) % p[k];
        }
        return res;
    }

    bool operator==(const H &h) const {
        return len == h.len && equal(val, val+K, h.val, h.val+K);
    }
    
    bool operator<(const H &h) const {
        if (len != h.len) return len < h.len;
        return lexicographical_compare(val, val+K, h.val, h.val+K);
    }
};

template<typename T>
struct id_map {
    int n = 0;
    map<T,int> id;
    int operator[](const T &t) {
        if (!id.count(t)) id[t] = n++;
        return id[t];
    }
};

int main() {
    precalc();

    id_map<string> token_id;
    auto hash_from = [&](const vector<string> &a, int i) {
        H h;
        vector<H> res;
        id_map<char> var_id;
        for (; i < ssize(a); i++) {
            const string &s = a[i];
            bool is_var = ssize(s) == 1 && isalpha(s[0]);
            int x = is_var ? var_id[s[0]] : 100 + token_id[s];
            h = h + H(x);
            res.push_back(h);
        }
        return res;
    };

    int n; cin >> n;
    vector<string> a(n);
    for (string &s: a) cin >> s;

    set<H> hashes;
    for (int i = 0; i < n; i++) {
        auto vec = hash_from(a, i);
        for (H h: hash_from(a, i)) hashes.insert(h);
    }

    int q; cin >> q;
    while (q--) {
        int k; cin >> k;
        vector<string> b(k);
        for (string &s: b) cin >> s;
        auto vec = hash_from(b, 0);
        cout << (hashes.count(vec.back()) ? "yes" : "no") << '\n';
    }
}
