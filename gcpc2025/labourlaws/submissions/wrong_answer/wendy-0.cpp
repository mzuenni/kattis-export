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


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
    int t;
    cin >> t;
    for0(i, t) {
        if (t - i > 10 * 60) continue;
        if (t - i > 9 * 60 && i < 45) continue;
        if (t - i > 6 * 60 && i < 30) continue;
        cout << i << endl;
        return 0;
    }
}