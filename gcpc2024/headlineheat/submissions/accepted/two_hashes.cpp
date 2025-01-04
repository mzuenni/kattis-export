#include <bits/stdc++.h>

#define rep(a, b)   for(int a = 0; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define endl        '\n'

using namespace std;
using ll = long long;
const ll M1 = 998244353;
const ll M2 = 1'000'000'007;
const ll B = 21419;

struct AhoCorasick {
    const static int A = 27;
    struct Vert {
        array<int,A> next = {};
        ll balance1 = 0;
        ll balance2 = 0;
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
            trie[v].balance1 += trie[link].balance1;
            trie[v].balance1 %= M1;
            trie[v].balance2 += trie[link].balance2;
            trie[v].balance2 %= M2;
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
    vector b_pow1(m,B);
    vector b_pow2(m,B);
    rep(i,m-1) b_pow1[i+1] = b_pow1[i]*B%M1;
    rep(i,m-1) b_pow2[i+1] = b_pow2[i]*B%M2;
    rep(i,size(edges)) {
        auto [u,v] = edges[i];
        aho.trie[node[u]].balance1 += M1-b_pow1[i];
        aho.trie[node[u]].balance1 %= M1;
        aho.trie[node[v]].balance1 += b_pow1[i];
        aho.trie[node[v]].balance1 %= M1;

        aho.trie[node[u]].balance2 += M2-b_pow2[i];
        aho.trie[node[u]].balance2 %= M2;
        aho.trie[node[v]].balance2 += b_pow2[i];
        aho.trie[node[v]].balance2 %= M2;
    }
    aho.finalize();

    // answer queries
    for(auto& text : texts) {
        ll balance1 = 0;
        ll balance2 = 0;
        int v = 0;
        for(auto c : text) {
            v = aho.trie[v].next[c-'a'];
            balance1 += aho.trie[v].balance1;
            balance2 += aho.trie[v].balance2;
        }
        bool good = (balance1%M1==0 && balance2%M2==0);
        cout << (good ? "yes" : "no") << endl;
    }

    return 0;
}
