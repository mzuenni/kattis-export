#include <istream>
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;
typedef unsigned __int128 mull;
typedef unsigned long long ull;
typedef vector<int> vi;

int rho2(int x) {
    int sm = 0;
    while(x > 0) {
        sm += x / 2;
        x /= 2;
    }
    return sm;
}

bool nck2(int n, int k) {
    if(n < 0 || k < 0 || k > n)
        return false;
    return rho2(n) == rho2(k) + rho2(n - k);
}

bool parity(ull x) {
    bool odd = false;
    int k = popcount(x);
    for(int i = 63; i >= 0; --i) {
        if(x & (1ULL << i)) {
            odd ^= nck2(i, k);
            k--;
        }
    }
    return odd;
}

void print(ull mask, int x, int y, int w, bool rev) {
    bool corr = !((mask >> x) & 1);
    if(corr != rev) swap(x, y);
    /*if(x % w == -1) {
        cout << "FAILURE\n";
        exit(0);
    }*/
    cout << (x / w) + 1 << ' ';
    cout << (x % w) + 1 << '\n';
    cout << (y / w) + 1 << ' ';
    cout << (y % w) + 1 << '\n';
}

bool maximal(int n, ull mask) {
    if(n != 64)
        mask &= (1ULL << n) - 1;
    if(mask == 0)
        return true;
    int lead = countl_zero(mask);
    int trail = countr_zero(mask);
    int set = popcount(mask);
    if(lead + trail + set != 64)
        return false;
    return (mask >> (n - 1)) & 1;
}

void solve_rec(int n, int w, ull mask, bool rev = false) {
    if(n != 64) mask &= (1ULL << n) - 1;
    int k = popcount(mask);
    bool b1 = (mask >> (n - 1)) & 1;
    bool b2 = (mask >> (n - 2)) & 1;
    if(b1) {
        solve_rec(n, w, ~mask, !rev);
        return;
    }
    bool all_even = !nck2(n - 2, k) && !nck2(n - 2, k - 2);
    if(all_even || !maximal(n - 2, mask)) {
        if(b1 != b2) {
            print(mask, n - 1, n - 2, w, rev);
            return;
        }
        solve_rec(n - 2, w, mask, rev);
        return;
    }
    if(n == 2) {
        print(mask, 0, 1, w, rev);
        return;
    }
    if(n == 3) {
        print(mask, 1, 2, w, rev);
        return;
    }
    int ind = countr_zero(mask);
    if(b1 == b2) {
        // 00 1^a 0^b -> 01 1^(b-1) 0^(a+1)
        print(mask, n - 2, ind, w, rev);
    } else {
        // 01 1^a 0^b -> 00 1^(a+1) 0^(b-1)
        if(k == n - 1)
            print(mask, n - 2, n - 1, w, rev);
        else
            print(mask, n - 2, ind - 1, w, rev);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int h, w, jnk; cin >> h >> w >> jnk;
        ull mask = 0;
        for(int i = 0; i < h; ++i) {
            for(int j = 0; j < w; ++j) {
                char c; cin >> ws >> c;
                if(c == '#')
                    mask |= 1ULL << (i * w + j);
            }
        }
        if(nck2(h * w, popcount(mask))) {
            cout << "risky\n";
            continue;
        }
        int k = popcount(mask);
        solve_rec(h * w, w, mask);
    }
}
