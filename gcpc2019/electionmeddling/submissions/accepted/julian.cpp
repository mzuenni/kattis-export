#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    int w, p;
    cin >> w >> p;
    vector<ll> bribes_needed(w);
    for (ll& b: bribes_needed) {
        vector<ll> votes(p);
        for (ll& i: votes) cin >> i;
        ll icpc = votes[0];
        swap(votes[0], votes.back()); votes.pop_back();

        ll mini = -1, maxi = 1024;
        while (mini < maxi - 1) {
            ll m = (mini + maxi) / 2;
            ll sum = 0;
            for (ll v: votes) {
                if (v >= icpc + m) sum += v - (icpc + m - 1);
            }
            if (sum > m) mini = m;
            else maxi = m;
        }
        b = maxi;
    }

    sort(bribes_needed.begin(), bribes_needed.end());
    ll sum = 0;
    for (int i = 0; i <= w / 2; ++i) {
        sum += bribes_needed[i];
    }
    cout << sum << "\n";
}
