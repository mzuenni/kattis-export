#include <iostream>
#include <limits>
#include <string>
#include <vector>

typedef long long ll;

using std::cerr;
using std::cin;
using std::vector;

int main()
{
    ll n;
    cin >> n;

    vector<ll> v(n + 1);
    for (ll& i: v) cin >> i;

    __int128_t sum = 0;
    for (ll i = 0; i <= n; ++i) {
        sum += (1ll << i) * (1ll << i) * static_cast<__int128_t>(v[i]);
    }

    if (sum > 1000ll * 1000 * 1000 * 1000 * 1000) { // 10^15
        if (sum > std::numeric_limits<ll>::max()) {
            cerr << "Total area is far too large\n";
        } else {
            cerr << "Total area is too large (" << static_cast<ll>(sum) << ")\n";
        }
        return 1;
    }

    return 42;
}
