#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int sign(ll i)
{
    return i > 0 ? 1 : -1;
}

int main()
{
    ll x[2], y[2], d[2];
    for (int i: {0, 1}) cin >> x[i] >> y[i] >> d[i];

    ll dist = abs(x[0] - x[1]) + abs(y[0] - y[1]);
    if (dist > d[0] + d[1] || (x[0] + x[1] + y[0] + y[1] + d[0] + d[1]) % 2) {
        cout << "impossible\n";
        return 0;
    }
    if (d[0] > dist) d[0] = dist - (d[1] % 2);

    ll x_dist = abs(x[0] - x[1]);
    if (d[0] >= x_dist) {
        cout << x[1] << " " << y[0] + (d[0] - x_dist) * sign(y[1] - y[0]) << endl;
    } else {
        cout << x[0] + d[0] * sign(x[1] - x[0]) << " " << y[0] << endl;
    }
}
