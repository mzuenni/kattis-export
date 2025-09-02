// This should fail due to an integer overflow in convert

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> f1, f2, p;
ll min_base = 1;
ll solution = numeric_limits<ll>::max();

__int128_t convert(vector<ll> digits, ll base)
{
    __int128_t f = 1, result = 0;
    for (ll d: digits) {
        result += f * d;
        f *= base;
    }
    return result;
}

int main()
{
    ios_base::sync_with_stdio(false);

    for (auto* v: {&f1, &f2, &p}) {
        int n;
        cin >> n;
        v->resize(n);
        for (auto& i: *v) {
            cin >> i;
            min_base = max(min_base, i);
        }
        reverse(v->begin(), v->end());
    }

    {
        size_t t = f1.size() + f2.size();
        if (p.size() < t - 1 || p.size() > t) {
            cout << "impossible\n";
        }
        f1.push_back(0);
        f2.push_back(0);
        p.push_back(0);
    }

    ll max_base = 0;
    for (int pos = 0; pos < p.size(); ++pos) {
        ll sum = 0;
        for (size_t i = max<ll>(0, pos - f2.size() + 1); i <= min<ll>(pos, f1.size() - 1); ++i) {
            sum += f1[i] * f2[pos - i];
        }
        sum -= p[pos];
        if (sum != 0) {
            max_base = sum;
            break;
        }
    }

    if (max_base == 0) {
        cout << min_base + 1 << endl;
        return 0;
    }

    ll mini = min_base, maxi = max_base;
    while (mini < maxi - 1) {
        ll m = (mini + maxi) / 2;
        if (convert(f1, m) * convert(f2, m) <= convert(p, m)) {
            maxi = m;
        } else {
            mini = m;
        }
    }

    if (convert(f1, maxi) * convert(f2, maxi) == convert(p, maxi)) {
        cout << maxi << "\n";
    } else {
        cout << "impossible\n";
    }
}
