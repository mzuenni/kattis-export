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
    vector<string_view> keys(n);
    rep(j,n) {
        auto& s = names[j];
        rep(i,size(s)) {
            if(s[i]<'A' || s[i]>'Z')
                continue;
            keys[j] = s;
            keys[j] = keys[j].substr(i);
            break;
        }
    }

    vector ids(n,0);
    iota(all(ids),0);
    sort(all(ids), [&](int a, int b) { return keys[a]<keys[b]; });
    for(int id : ids) 
        cout << names[id] << endl;

    return 0;
}
