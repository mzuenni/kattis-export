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
    string total = "";
    vector<int> idx(k);
    for (int i = 0; i < k; i++) {
        getline(cin,texts[i]);
        idx[i] = size(total);
        total += texts[i] + '#';
    }
    vector<bool> good(k, true);
    vector<int> balance(k, 0), lst(k, -1);
    auto count = [&](const string& pat, int i, int val) {
        int cnt = 0;
        auto pos = total.find(pat);
        int j = -1;
        while(pos != string::npos) {
            if (j == -1 || j + 1 < k && idx[j + 1] <= pos)
                j = upper_bound(idx.begin() + j + 1, idx.end(), pos) - idx.begin() - 1;
            if (lst[j] != i && balance[j] != 0)
                good[j] = false;
            if (lst[j] != i)
                lst[j] = i, balance[j] = 0;
            balance[j] += val;
            lst[j] = i;
            if(pos+1+size(pat)>size(total)) break;
            pos = total.find(pat, pos+1);
        }
        return cnt;
    };
    for (int i = 0; i < m; i++) {
        auto [u, v] = edges[i];
        count(names[u], i, +1);
        count(names[v], i, -1);
    }
    for (int i = 0; i < k; i++) {
        if (balance[i] != 0)
            good[i] = false;
        cout << (good[i] ? "yes" : "no") << endl;
    }
}

