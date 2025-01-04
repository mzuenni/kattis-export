#include "bits/stdc++.h"
using namespace std;

struct node{
    map<string, node *> children;
    string normalizedToken;

    node * extend(string & token){
        if(!children[token]) children[token] = new node();
        children[token]->normalizedToken = token;
        return children[token];
    }

    node * lookup(string & s){
        return children[s];
    }
};

vector<string> reference;
vector<string> pattern;
vector<string> tmp;

void normalize(vector<string>::iterator start, vector<string>::iterator end, vector<string> & output){
    map<char, int> varMap;
    int numVars = 0;


    output.clear();
    for(auto it = start; it != end; it++){
        char c = (*it)[0];
        if(it -> size() == 1 && (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z')){
            if(!varMap[(*it)[0]]){
                varMap[(*it)[0]] = numVars < 26 ? 'a' + numVars : 'A' + numVars - 26;
                numVars++;
            }
            (*it)[0] = varMap[(*it)[0]];
        }
        output.push_back(*it);
    }
}

node * build_trie(){
    node * tree = new node();
    for(auto i = reference.begin(); i != reference.end(); i++){
        normalize(i, reference.end(), tmp);
        node * cur = tree;
        for(auto token : tmp) cur = cur -> extend(token);
    }
    return tree;
}

bool check_pattern(node * trie){
    node * cur = trie;
    normalize(pattern.begin(), pattern.end(), tmp);
    for(string & token : tmp){
        cur = cur->lookup(token);
        if(cur == NULL) return false;
    }
    return true;
}

void read(vector<string> & vec){
    int n;
    cin >> n;
    vec.clear();
    for(int i=0; i<n; i++){
        string s;
        cin >> s;
        vec.push_back(s);
    }
}

int main(){
    read(reference);
    node * trie = build_trie();
    int q;
    cin >> q;

    for(int i=0; i<q; i++){
        read(pattern);
        if(check_pattern(trie)) cout << "yes" << endl;
        else cout << "no" << endl;
    }
}