#include <map>
#include <iostream>

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

    ll n;
    string s;
    cin >> n;
    map<string, string> list;
    getline(cin, s);
    for0(i, n) {
        getline(cin, s);
        string x;
        bool b = s[0] >= 'A' && s[0] <= 'Z';
        for0(i, sz(s)) {
            if (s[i] == ' ') {
                if (b) break;
                if (!b && s[i + 1] >= 'A' && s[i + 1] <= 'Z') b = true;
            } else if (b) x.pb(s[i]);
        }
        list[x] = s;
    }
    for (auto x : list) cout << x.second << endl;
}