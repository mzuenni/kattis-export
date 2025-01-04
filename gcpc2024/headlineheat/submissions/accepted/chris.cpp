#include <bits/stdc++.h>

#define rep(a, b)   for(int a = 0; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define endl        '\n'

using namespace std;
using ll = long long;
const ll M = 998244353;
const ll B = 21419;

struct AhoCorasick {
    const static int A = 27;
    struct Vert {
        array<int,A> next = {};
        ll balance = 0;
    };
    vector<Vert> trie = {{}};

    int addWord(string& s) {
        int v = 0;
        for(auto c : s) {
            c-='a';
            if(!trie[v].next[c]) {
                trie[v].next[c] = trie.size();
                trie.emplace_back();
            }
            v = trie[v].next[c];
        }
        return v;
    }

    void finalize() {
        queue<array<int,4>> q{{{0,0,0,0}}};
        while(size(q)) {
            auto [v, parent, plink, pch] = q.front(); q.pop();
            int link = parent == 0 ? 0 : trie[plink].next[pch];
            rep(c,A) {
                if(!trie[v].next[c]) trie[v].next[c] = trie[link].next[c];
                else q.push({trie[v].next[c], v, link, c});
            }

            if(v==0) continue; // safety reasons :)
            // propagate data over suffix links
            trie[v].balance += trie[link].balance;
            trie[v].balance %= M;
        }
    }
};

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
    // replace spaces
    for(auto& name : names) replace(all(name), ' ', char('z'+1));
    for(auto& text : texts) replace(all(text), ' ', char('z'+1));


    // build aho corasick
    AhoCorasick aho;
    vector node(n,0);
    rep(i,size(names))
        node[i] = aho.addWord(names[i]);
    vector b_pow(m,B);
    rep(i,m-1) b_pow[i+1] = b_pow[i]*B%M;
    rep(i,size(edges)) {
        auto [u,v] = edges[i];
        aho.trie[node[u]].balance += M-b_pow[i];
        aho.trie[node[u]].balance %= M;
        aho.trie[node[v]].balance += b_pow[i];
        aho.trie[node[v]].balance %= M;
    }
    aho.finalize();

    // answer queries
    for(auto& text : texts) {
        ll balance = 0;
        int v = 0;
        for(auto c : text) {
            v = aho.trie[v].next[c-'a'];
            balance += aho.trie[v].balance;
        }
        cout << (balance%M == 0 ? "yes" : "no") << endl;
    }

    return 0;
}
