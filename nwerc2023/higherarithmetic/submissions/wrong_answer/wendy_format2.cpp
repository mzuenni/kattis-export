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

string mulRemaining(map<ll, ll> &a) {
    string res; 
    for(auto x : a) {
        for0(i, x.second) res += to_string(x.first) + "*"; 
    }
    if(sz(res) > 0) res.pop_back(); 
    return res; 
}

string add(string a, string b) {
    return "(" + a + "+" + b + ")"; 
}

string mul(string a, string b) {
    return a + "*" + b; 
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
    ll n; 
    cin >> n; 
    map<ll, ll> a;
    ll tmp;  

    ll m = 0; 
    for0(i, n) {
        cin >> tmp; 
        a[tmp]++;
        m = max(tmp, m);  
    } 

    if(n == 1) {
        cout << (*a.begin()).first << endl;
        return 0;  
    }

    a[m]--;      
    n--; 

    string res; 
    while(true) {
        if(a.find(1) == a.end() || a[1] == 0) {
            // cout << "zero" << endl; 
            res += "*" + mulRemaining(a);   
            break; 
        } 
        else if(a[1] == 1) {
            a.erase(1); 
            (*a.begin()).second--;
            res += "*" + add(to_string(1), to_string((*a.begin()).first)) + "*" + mulRemaining(a); 
            break; 
        } else if(a.find(2) != a.end() && a[1] == 2 && a[2] == 1) {
            res += "*" + add("1", add("1", "2"));
            a[1] -= 2; 
            a[2]--;  
        } else if(a.find(2) != a.end() && a[2] != 0) {
            res += "*" + add("1", "2");
            a[1]--; 
            a[2]--;  
        } else if(a[1] > 4 || a[1] == 3) {
            res += "*" + add("1", add("1", "1")); 
            a[1] -= 3; 
        } else {
            res += "*" + add("1", "1"); 
            a[1] -= 2; 
        }        
    }

    if(res[0] == '*') res.erase(res.begin()); 
    if(sz(res) > 0 && res.back() == '*') res.erase(res.end() - 1); 

    cout << res << endl; 
}