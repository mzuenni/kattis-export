#include<vector>
#include<iostream>

using namespace std;
vector<int> adj[1000000], adj_t[1000000];
vector<bool> used;
vector<int> order, comp;
vector<bool> assignment;

// 2-SAT implementation from cp-algorithms.com

void dfs1(int v) {
    used[v] = true;
    for (int u : adj[v]) if (!used[u]) dfs1(u);
    order.push_back(v);
}

void dfs2(int v, int cl) {
    comp[v] = cl;
    for (int u : adj_t[v]) if (comp[u] == -1) dfs2(u, cl);
}

bool solve_2SAT(int n) {
    order.clear();
    used.assign(n, false);
    for (int i = 0; i < n; ++i) if (!used[i]) dfs1(i);

    comp.assign(n, -1);
    for (int i = 0, j = 0; i < n; ++i) {
        int v = order[n - i - 1];
        if (comp[v] == -1) dfs2(v, j++);
    }

    assignment.assign(n / 2, false);
    for (int i = 0; i < n; i += 2) {
        if (comp[i] == comp[i + 1]) return false;
        assignment[i / 2] = comp[i] > comp[i + 1];
    }
    return true;
}

void add_disjunction(int a, bool na, int b, bool nb) {
    // na and nb signify whether a and b are to be negated 
    a = 2*a ^ na;
    b = 2*b ^ nb;
    int neg_a = a ^ 1;
    int neg_b = b ^ 1;
    adj[neg_a].push_back(b);
    adj[neg_b].push_back(a);
    adj_t[b].push_back(neg_a);
    adj_t[a].push_back(neg_b);
}

int tmp[7];
int daysize[7];

pair<int, int> transl(int day, int guess){
    int erg = 0;
    for(int d = 0; d < day; d++) erg += daysize[d];
    if(guess < 0) return {erg - guess - 1, false};
    else return {erg + guess - 1, true};
}

int main(){
    int n;
    cin >> n;

    for(int i=0; i<7; i++) cin >> daysize[i];

    for(int i=0; i<n; i++){
        for(int j=0; j<7; j++) {
            cin >> tmp[j];
            for(int l = 0; l < j; l++) add_disjunction(transl(j, tmp[j]).first, !transl(j, tmp[j]).second, transl(l, tmp[l]).first, !transl(l, tmp[l]).second);
        }
    }
    
    int p6, p7;
    cin >> p6 >> p7;
    add_disjunction(transl(5, p6).first, transl(5, p6).second, transl(5, p6).first, transl(5, p6).second);
    add_disjunction(transl(6, p7).first, transl(6, p7).second, transl(6, p7).first, transl(6, p7).second);

    int v = 0;
    for(int i=0; i<7; i++) v+= daysize[i];
    if(solve_2SAT(2*v)) cout << "possible" << endl;
    else cout << "impossible" << endl;
}