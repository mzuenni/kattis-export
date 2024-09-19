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
    for0(i, sz(s)) s[i] = s[i] - ('A' - 'a'); 
    set<string> out; 
    out.insert(s); 
    for0(i, sz(s)) {
        if(s[i] == 's') {
            if(i < sz(s) - 1 && s[i + 1] == 's') out.insert((s.substr(0, i).append("B")).append(s.substr(i + 2))); 
        }
    }
    for(string s : out) cout << s << endl; 
}