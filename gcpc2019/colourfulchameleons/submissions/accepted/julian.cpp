#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    ll n, c, y;
    cin >> n >> c >> y;
    vector<ll> x(n);
    ll sum = 0;
    for (auto& i: x) {
        cin >> i;
        sum += i;
    }
    swap(x[c - 1], x.back());
    x.pop_back();

    ll maxi = *(max_element(x.begin(), x.end()));
    ll cnt = 0;
    for (auto i: x) {
        ll diff = maxi - i;
        if (diff % (y + 1) != 0) {
            cout << "impossible\n";
            return 0;
        }
        cnt += diff / (y + 1);
    }

    cnt += maxi - cnt;
    cout << cnt << " " << sum + cnt * (y - n + 1) << "\n";
}
