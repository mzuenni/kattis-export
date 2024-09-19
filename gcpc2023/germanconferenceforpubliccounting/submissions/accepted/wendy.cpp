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

    string s; 
    cin >> s; 
    string x(sz(s), s[0]); 
    cout << (s[0] - '0' - (stoll(x) > stoll(s)))  * sz(s) + (10 - (s[0] - '0') + (stoll(x) > stoll(s))) * (sz(s) - 1) + (stoll(s) < 10) << endl; 
}