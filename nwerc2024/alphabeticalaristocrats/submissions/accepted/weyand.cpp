#include <bits/stdc++.h>
#define rep(a, b)   for(int a = 0; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin>>n;
    cin.get();

    vector<string> names(n);
    rep(i,n) getline(cin, names[i]);
    auto dutch = [&](string_view s) {
        rep(i,size(s))
            if('A'<=s[i] && s[i]<='Z')
                return s.substr(i);
    };
    sort(all(names), [&](auto& a, auto& b) { return dutch(a)<dutch(b); });

    for(auto& s : names) 
        cout << s << endl;

    return 0;
}
