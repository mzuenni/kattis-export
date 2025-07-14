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

bool check(vector<pl> &blocks, ll n, ll d) {
    ll minPos = 0;
    for (auto [s, e] : blocks) {
        if (e - s > d) return false;
        if (minPos > s) return false;
        minPos = max(minPos + 2 * d, e + d);
    }
    return true;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
    ll n, d, x;
    cin >> n >> d;

    vector<vector<pl>> blocks(n + 1);
    for0(i, n) {
        cin >> x;
        if (blocks[x].empty()) blocks[x].pb({i, i + 1});
        else if (i - blocks[x].back().second + 1 <= d) blocks[x].back().second = i + 1;
        else blocks[x].pb({i, i + 1});
    }
    for0(i, n) {
        if (check(blocks[i], n, d)) {
            cout << i << endl;
            return 0;
        }
    }
}