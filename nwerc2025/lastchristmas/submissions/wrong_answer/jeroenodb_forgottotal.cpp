#include <iostream>
#include <map>
#include <array>
using namespace std;
int main() {
    int n; cin >> n;
    map<string,array<int,11>> hits;

    for(int i=0;i<n;++i) {
        for(int j=1;j<=10;++j) {
            string s; cin >> s;
            hits[s][j]+=1;
        }
    }
    map<array<int,11>,string> mp;
    for(auto [k,v] : hits) {
        if(mp.count(v)) {
            mp[v]="";
        } else mp[v]=k;
    }
    auto ans = mp.rbegin()->second;
    if(ans.empty()) ans="tie";
    cout << ans << '\n';

}