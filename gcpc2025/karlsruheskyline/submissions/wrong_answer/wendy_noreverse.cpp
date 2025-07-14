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
    ll n, a, b;
    cin >> n >> a >> b;
    if (a + b - 1 > n || max(a, b) == 1) {
        cout << "no" << endl;
        return 0;
    }
    // bool swapped = false;
    // if (b < a) {
    //     swap(a, b);
    //     swapped = true;
    // }
    vl res(n, -1);

    for0(i, a - 1) res[i] = i;
    res[a - 1] = n - 1;
    b--;
    for0(i, b) res[n - i - 1] = a + i - 1;
    res[n - b] = n - 2;
    for(ll i = a; i < n - b; i++) res[i] = a + b + i - (a + 2);

    // if (swapped) reverse(res.begin(), res.end());
    cout << "yes" << endl;
    for0(i, n) cout << res[i] + 1 << " ";
    cout << endl;
}