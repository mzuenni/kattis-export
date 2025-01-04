#include <bits/stdc++.h>

#define rep(a, b)   for(int a = 0; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define endl        '\n'

using namespace std;
using Graph = vector<vector<int>>;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);
    string lineskip;

    // read input
    int n,m,k; cin>>n>>m>>k;
    vector<string> names(n);
    vector<pair<int,int>> edges(m);
    vector<string> texts(k);

    getline(cin,lineskip); // skip newline
    for(auto& name : names) getline(cin,name);
    for(auto& [u,v] : edges) cin>>u>>v, --u,--v;
    getline(cin,lineskip); // skip newline
    for(auto& text : texts) getline(cin,text);

    auto count = [](const string& pat, string& txt) {
        int cnt = 0;
        auto pos = txt.find(pat);
        while(pos != string::npos) {
            cnt++;
            if(pos+1+size(pat)>size(txt)) break;
            pos = txt.find(pat, pos+1);
        }
        return cnt;
    };


    for(auto& text : texts) {
        bool good = true;
        for(auto [u,v] : edges) {
            auto cnt1 = count(names[u], text);
            auto cnt2 = count(names[v], text);
            good &= (cnt1==cnt2);
            if (!good) break;
        }
        cout << (good ? "yes" : "no") << endl;
    }

    return 0;
}

