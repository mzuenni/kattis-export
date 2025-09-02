#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> f1, f2, p;
ll min_base = 1;
ll solution = numeric_limits<ll>::max();

void try_base(ll b)
{
    if (b < min_base) return;
    ll carry = 0;
    for (int pos = 0; pos < p.size(); ++pos) {
        ll sum = carry;
        carry = 0;
        for (size_t i = max<ll>(0, pos - f2.size() + 1); i <= min<ll>(pos, f1.size() - 1); ++i) {
            sum += f1[i] * f2[pos - i];
            carry += sum / b;
            sum %= b;
        }
        if (sum != p[pos]) return;
    }
    solution = min(solution, b);
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
            min_base = max(min_base, i + 1);
        }
        reverse(v->begin(), v->end());
    }
    {
        size_t t = f1.size() + f2.size();
        if (p.size() < t - 1 || p.size() > t) {
            cout << "impossible\n";
            return 0;
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
        cout << min_base << endl;
        return 0;
    }

    for (ll i = 1; i * i <= max_base; ++i) {
        if (max_base % i == 0) {
            try_base(i);
            try_base(max_base / i);
        }
    }
    if (solution <= max_base) {
        cout << solution << "\n";
    } else {
        cout << "impossible\n";
    }
}
