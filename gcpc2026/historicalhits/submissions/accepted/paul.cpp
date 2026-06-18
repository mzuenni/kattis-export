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

    vector<vector<int>> lev(n+2), rev(n+2);
    for (int i = 1; i <= n; i++) {
        int l = i, r = i;
        while (a[l-1] > b[i]) l--;
        while (a[r+1] < b[i]) r++;
        lev[l].push_back(i);
        rev[r].push_back(i);
    }

    vector dp(n+2, vector<num>(n+2));
    vector<num> pre(n+2), suf(n+2);
    vector<int> cpre(n+2), csuf(n+2);

    for (int d = 0; d < n; d++) {
        for (int l = 1; l+d <= n; l++) {
            int r = l+d;
            for (int i: rev[r]) {
                if (i >= l && b[i] >= a[l-1]) {
                    pre[l] = pre[l] + dp[l][i-1];
                    cpre[l]++;
                }
            }
            for (int i: lev[l]) {
                if (i <= r && b[i] <= a[r+1]) {
                    suf[r] = suf[r] + dp[i+1][r];
                    csuf[r]++;
                }
            }
            num k(cpre[l]);
            dp[l][r] = (k + pre[l] + suf[r]) / k;
        }
    }
    cout << dp[1][n].x << '\n';
}
