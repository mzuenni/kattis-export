#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

template<int m>
struct mod {
	i64 x;
	mod(i64 x = 0): x((m + x%m) % m) { }
	
	mod operator+(const mod &a) const { return mod(x+a.x); }
	mod operator-(const mod &a) const { return mod(x-a.x); }
	mod operator*(const mod &a) const { return mod(x*a.x); }
	mod operator/(const mod &a) const { return *this * (a^(m-2)); }
	
	bool operator==(const mod &a) const { return x == a.x; }

	mod operator^(i64 n) const {
		i64 res = 1, a = x;
		for (; n; n /= 2) {
			if (n%2) res = res*a % m;
			a = a*a % m;
		}
		return mod(res);
	}
};
using num = mod<1'000'000'007>;

const int N = 1e6 + 10;
num fac[N];

int main() {
    fac[0] = 1;
    for (int n = 1; n < N; n++) {
        fac[n] = num(n)*fac[n-1];
    }

    int n, k;
    cin >> n >> k;
    vector<int> a(k);
    for (int &x: a) cin >> x;
    a.push_back(n - accumulate(begin(a), end(a), 0));

    vector<num> dp(k+1);
    for (int i = 0; i <= k; i++) {
        int sum = a[i];
        for (int j = i-1; j >= 0; j--) {
            dp[i] = dp[i] - fac[sum] * dp[j];
            sum += a[j];
        }
        dp[i] = dp[i] + fac[sum];
    }
    cout << dp[k].x << '\n';
}
