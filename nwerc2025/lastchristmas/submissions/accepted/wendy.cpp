#include <bits/stdc++.h>
#define f(i, s, k, l) for (int i = s; i < k; i += l)
#define for0(i, k) f(i, 0, k, 1)

#define pl pair<long long, long long>
#define pb push_back

#define vl vector<long long>
#define vi vector<int>
#define sz(x) (ll)(x).size()

using namespace std;
using ll = long long;
using ld = long double;

ll k = 10;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
    ll n;
    string s;
    cin >> n;
    map<string, vl> m;
    for0(z, n) {
        for0(i, k) {
            cin >> s;
            if (m.count(s) == 0) m[s] = vl(k + 1, 0); // first index: sum
            m[s][i + 1]++;
            m[s][0]++;
        }
    }
    multiset<pair<vl, string>> res;
    for (auto &[x, y] : m) res.insert({y, x});

    // ll count = 0;
    // for (auto x: res) {
    //     if (count > sz(res) - 10) {
    //         for(ll a : x.first) cout << a << " ";
    //         cout << endl;
    //     }
    //     count++;
    // }
    if (sz(res) == 1) cout << s << endl;
    else if (prev(res.end())->first == prev(prev(res.end()))->first) cout << "tie" << endl;
    else cout << prev(res.end())->second << endl;
}
