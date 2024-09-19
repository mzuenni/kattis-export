#include<vector>
#include<iostream>

using namespace std;
vector<int> adj[1000000], adj_t[1000000];
vector<bool> used;
vector<int> order, comp;
vector<bool> assignment;


int n;
const int MAXN = 200000;



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
void add_equiv(int a, int b) {
    add_disjunction(a, false, b, true);
    add_disjunction(a, true, b, false);
}
void add_xor(int a, int b) {
    add_disjunction(a, true, b, true);
    add_disjunction(a, false, b, false);
}

int tmp[7];
int daysize[7];
int guess[MAXN][7];

int transl(int player, int day){
    return player * 7 + day;
}

// variables of the form "player i scores on day d"
// constraints of the kind "player i scores on day d if and only if player j does not score on day d"
// 
int main(){
    cin >> n;

    for(int i=0; i<7; i++) cin >> daysize[i];

    for(int i=0; i<n; i++){
        for(int d=0; d<7; d++) {
            cin >> guess[i][d];
        }
    }
    
    int p6, p7;
    cin >> guess[n][5] >> guess[n][6];
    for(int d=0; d<5; d++) guess[n][d] = 0;

    //cout << "haha" << endl;

    // quadratically many constraints
    for(int i=0; i <= n; i++){
        for(int j=0; j < i; j++){
            for(int d = 0; d < 7; d++){
                if(guess[i][d] == guess[j][d]) add_equiv(transl(i, d), transl(j, d));
                if(guess[i][d] == -guess[j][d]) add_xor(transl(i, d), transl(j, d));
            }
        }
    }
    //cout << "haha" << endl;

    // Pascal should win
    add_disjunction(transl(n, 5), true, transl(n, 5), true);
    add_disjunction(transl(n, 6), true, transl(n, 6), true);

    // Each player should score at most once
    for(int i=0; i<n; i++) for(int d1 = 0; d1 < 7; d1++) for(int d2 = 0; d2 < d1; d2++) add_disjunction(transl(i, d1), false, transl(i, d2), false);

    if(solve_2SAT(2*7*(n+1))) cout << "possible" << endl;
    else cout << "impossible" << endl;
}