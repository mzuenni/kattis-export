#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    int n;
    cin >> n;
    vector<ll> cnt(n + 1);
    for (auto& i: cnt) cin >> i;

    ll area = 0;
    for (int i = 0; i <= n; ++i) {
        area += (1ll << i) * (1ll << i) * cnt[i];
    }

    for (ll i = 1; i * i <= area; ++i) {
        if (area % i != 0) continue;

        ll current_area = 0;
        bool possible = true;
        for (int k = n; k >= 0; --k) {
            ll border_length = 1ll << k;
            current_area += border_length * border_length * cnt[k];
            ll a = (i / border_length) * border_length;
            ll b = ((area / i) / border_length) * border_length;
            if (a * b < current_area) {
                possible = false;
                break;
            }
        }

        if (possible) {
            cout << i << " " << area / i << "\n";
            return 0;
        }
    }

    cout << "impossible\n";
	cout << '.';
}
