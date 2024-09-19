#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll n;
    cin >> n;
    if (__builtin_popcountll(--n) < 3) cout << (n & (n - 1)) + 1 << endl;
    else cout << "impossible" << endl;
    return 0;
}
