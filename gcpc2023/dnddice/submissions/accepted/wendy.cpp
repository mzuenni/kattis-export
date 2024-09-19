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

    ll t, c, o, d, i; 
    cin >> t >> c >> o >> d >> i; 
    ll sum = 4 * t + 6 * c + 8 * o + 12 * d + 20 * i; 
    ll m = (t + c + o + d + i + sum) / 2; 
    for(int k = 0; k <= sum - (t + c + o + d + i); k++) {
        m +=  (2 * (k % 2) - 1) * k; 
        cout << m << " ";
    }
    cout << endl;  
}