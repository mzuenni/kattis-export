#include <bits/stdc++.h>
using namespace std;

template<int m>
struct mod {
	long x;
	mod(long x = 0): x((m + x%m) % m) { }
	
	mod operator+(const mod &a) const { return mod(x+a.x); }
	mod operator-(const mod &a) const { return mod(x-a.x); }
	mod operator*(const mod &a) const { return mod(x*a.x); }
	mod operator/(const mod &a) const { return *this * a.pow(m-2); }
	
	bool operator==(const mod &a) const { return x == a.x; }

	mod pow(long n) const {
		long res = 1, a = x;
		for (; n; n /= 2) {
			if (n%2) res = res*a % m;
			a = a*a % m;
		}
		return mod(res);
	}
};

using num = mod<998'244'353>;

int main() {
    int n; cin >> n;
    vector<pair<int,int>> ab(n);
    for (auto &[a, b]: ab) cin >> a >> b;
    sort(begin(ab), end(ab));
    vector<int> a(n+2), b(n+2);
    a[n+1] = 1e9 + 1;
    for (int i = 1; i <= n; i++) {
        tie(a[i], b[i]) = ab[i-1];
    }

    vector mark(n+2, vector<int>(n+2));
    vector dp(n+2, vector<num>(n+2));

    auto rec = [&](const auto &self, int l, int r) -> num {
        if (l > r) return num(0);
        if (mark[l][r]) return dp[l][r];
        int k = 0;
        for (int i = l; i <= r; i++) {
            if (a[l-1] <= b[i] && b[i] <= a[r+1]) {
                num cur = num(1) + self(self, l, i-1) + self(self, i+1, r);
                dp[l][r] = dp[l][r] + cur, k++;
            }
        }
        if (k > 0) dp[l][r] = dp[l][r] / num(k);
        mark[l][r] = 1;
        return dp[l][r];
    };

    cout << rec(rec, 1, n).x << '\n';
}
