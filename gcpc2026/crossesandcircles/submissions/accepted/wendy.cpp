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

ll a, b;
void print(ll r, ll c) {
    cout << r << " " << c << endl;
    cin >> a >> b;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
    print(10, 10);
    if (b != 10) {
        print(9, 10);
        if (a != 8) print(8, 10);
        else print(11, 10);
        return 0;
    }
    if (a != 10) {
        print(10, 9);
        if (b != 8) print(10, 8);
        else print(10, 11);
        return 0;
    }
}
