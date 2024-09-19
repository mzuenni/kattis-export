#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    ll a, b;
    cin >> a >> b;
	a--, b--;
    ll result = 1;
    ll j = a;
    for (ll i = 1; i < a; ++i) {
        while (j && i * i + j * j > a * a) --j;
        if (i * i + j * j == a * a) {
            if (b % (a / gcd(i, j)) == 0) ++result;
        }
    }
    cout << ((a == b) ? 1 : 2) * result << endl;
}
