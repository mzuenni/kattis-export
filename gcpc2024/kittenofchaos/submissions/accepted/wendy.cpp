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

    string s, t; 
    cin >> s >> t; 

    pl a = {0, 0}; 
    for (char c: t) {
        if (c == 'r') {
            a.first++; 
            a.second++; 
        } else if (c == 'v') a.first++;
        else a.second++;  
    }

    if (a.second % 2 == 1) {
        for (char &c: s) {
            if (c == 'b') c = 'd'; 
            else if (c == 'd') c = 'b'; 
            else if (c == 'p') c = 'q'; 
            else c = 'p'; 
        }
        reverse(s.begin(), s.end()); 
    }
    if (a.first % 2 == 1) {
        for (char &c: s) {
            if (c == 'b') c = 'p'; 
            else if (c == 'p') c = 'b'; 
            else if (c == 'd') c = 'q'; 
            else c = 'd'; 
        }
    }
    cout << s << endl;     
}