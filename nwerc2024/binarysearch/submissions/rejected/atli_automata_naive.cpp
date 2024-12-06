// @EXPECTED_RESULTS@: TIME_LIMIT_EXCEEDED, WRONG_ANSWER

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <climits>
#include <cstring>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

const int CHAR_NUM = 2;

struct node {
    int next[CHAR_NUM];
    bool accepting;
    node() : accepting(false) {
        memset(next, -1, sizeof(next));
    }
};

struct dfa {
    vector<node> nodes;
    int initial;

    dfa(int n, int i) : nodes(vector<node>(n)), initial(i) { }

    void negate() {
        for(int i = 0; i < nodes.size(); ++i)
            nodes[i].accepting = !nodes[i].accepting;
    }
    
    void print(ostream &out) {
        out << nodes.size() << ' ' << initial << '\n';
        for(int i = 0; i < nodes.size(); ++i) {
            for(int j = 0; j < CHAR_NUM; ++j) {
                out << nodes[i].next[j] << ' ';
            }
            out << nodes[i].accepting << '\n';
        }
    }
};

struct partition_refinement {
    int *locs, *ord_elem, *set_ind;
    vector<pair<int,int>> ranges;

    partition_refinement(int n) : ranges(1, make_pair(0, n - 1)) {
        locs = new int[n];
        ord_elem = new int[n];
        set_ind = new int[n];
        memset(set_ind, 0, n * sizeof(int));
        for(int i = 0; i < n; ++i) ord_elem[i] = locs[i] = i;
    }
    
    ~partition_refinement() {
        delete[] locs;
        delete[] ord_elem;
        delete[] set_ind;
    }

    vector<pair<int,int>> refine(vector<int>::iterator xb, vector<int>::iterator xe) {
        vector<pair<int,int>> hit, ret;
        for(auto it = xb; it != xe; ++it) {
            hit.push_back(make_pair(set_ind[*it], *it));
        }
        sort(hit.begin(), hit.end());
        for(int i = 0, j = 0; i < hit.size(); i = j + 1) {
            while(j + 1 < hit.size() && hit[j + 1].first == hit[i].first) j++;
            int ind = hit[i].first;
            int sz = ranges[ind].second - ranges[ind].first + 1;
            int to_move = j - i + 1;
            if(sz == to_move) continue;
            ret.push_back(ranges[ind]);
            for(int k = i; k <= j; ++k) {
                locs[ord_elem[ranges[ind].second]] = locs[hit[k].second];
                swap(ord_elem[locs[hit[k].second]], ord_elem[ranges[ind].second]);
                locs[hit[k].second] = ranges[ind].second;
                ranges[ind].second--;
            }
            for(int k = ranges[ind].second + 1; k <= ranges[ind].second + to_move; ++k) {
                set_ind[ord_elem[k]] = ranges.size();
            }
            ranges.push_back(make_pair(ranges[ind].second + 1, ranges[ind].second + to_move));
            ret.push_back(ranges[ind]);
            ret.push_back(ranges.back());
        }
        return ret;
    }
};

void remove_unreachable(dfa &d) {
    vector<bool> reachable(d.nodes.size(), false);
    vector<int> q;
    reachable[d.initial] = true;
    q.push_back(d.initial);
    while(q.size() > 0) {
        vector<int> new_q;
        for(int j = 0; j < CHAR_NUM; ++j) {
            for(int i : q) {
                int x = d.nodes[i].next[j];
                if(!reachable[x]) {
                    reachable[x] = true;
                    new_q.push_back(x);
                }
            }
        }
        q = new_q;
    }
    int counter = 0;
    vector<int> new_ind;
    for(int i = 0; i < d.nodes.size(); ++i) {
        if(!reachable[i]) new_ind.push_back(-1);
        else new_ind.push_back(counter++);
    }
    if(counter == d.nodes.size()) return;
    dfa smaller(counter, new_ind[d.initial]);
    for(int i = 0; i < d.nodes.size(); ++i) {
        if(reachable[i]) {
            smaller.nodes[new_ind[i]].accepting |= d.nodes[i].accepting;
            for(int j = 0; j < CHAR_NUM; ++j) {
                int x = d.nodes[i].next[j];
                smaller.nodes[new_ind[i]].next[j] = new_ind[d.nodes[i].next[j]];
            }
        }
    }
    d = smaller;
}

void remove_duplicates(dfa &d) {
    partition_refinement p(d.nodes.size());
    vector<int> acc;
    vector<vector<int>> rev(d.nodes.size() * CHAR_NUM, vector<int>());
    for(int i = 0; i < d.nodes.size(); ++i) {
        if(d.nodes[i].accepting) acc.push_back(i);
        for(int j = 0; j < CHAR_NUM; ++j) {
            rev[d.nodes[i].next[j] * CHAR_NUM + j].push_back(i);
        }
    }
    p.refine(acc.begin(), acc.end());
    set<pair<int,int>> todo;
    todo.insert(p.ranges[0]);
    while(todo.size() > 0) {
        pair<int,int> a = *todo.begin();
        todo.erase(todo.begin());
        for(int j = 0; j < CHAR_NUM; ++j) {
            vector<int> x;
            for(int i = a.first; i <= a.second; ++i) {
                for(int k : rev[p.ord_elem[i] * CHAR_NUM + j]) {
                    x.push_back(k);
                }
            }
            auto res = p.refine(x.begin(), x.end());
            for(int i = 0; i < res.size(); i += 3) {
                if(todo.count(res[i])) {
                    todo.erase(res[i]);
                    todo.insert(res[i + 1]);
                    todo.insert(res[i + 2]);
                } else {
                    int sz1 = res[i + 1].second - res[i + 1].first;
                    int sz2 = res[i + 2].second - res[i + 2].first;
                    todo.insert(sz1 < sz2 ? res[i + 1] : res[i + 2]);
                }
            }
        }
    }
    int *new_ind = new int[d.nodes.size()];
    memset(new_ind, -1, d.nodes.size() * sizeof(int));
    int initial = -1;
    for(int i = 0; i < p.ranges.size(); ++i) {
        for(int j = p.ranges[i].first; j <= p.ranges[i].second; ++j) {
            if(p.ord_elem[j] == d.initial)
                initial = i;
            new_ind[p.ord_elem[j]] = i;
        }
    }
    dfa reduced(p.ranges.size(), initial);
    for(int i = 0; i < p.ranges.size(); ++i) {
        for(int j = 0; j < CHAR_NUM; ++j) {
            for(int k = p.ranges[i].first; k <= p.ranges[i].second; ++k) {
                reduced.nodes[i].next[j] = new_ind[d.nodes[p.ord_elem[k]].next[j]];
                reduced.nodes[i].accepting |= d.nodes[p.ord_elem[k]].accepting;
            }
        }
    }
    delete[] new_ind;
    d = reduced;
}

dfa powerset_construction(vector<int> w, vector<vector<int>> g) {
    vector<int> init(g.size(), 0);
    for(int i = 0; i < g.size(); ++i)
        init[i] = i;
    dfa pd(1, 0);
    pd.nodes.back().accepting = true;
    map<vector<int>,int> ind;
    ind[init] = 0;
    vector<pair<vector<int>,int>> q;
    q.push_back(make_pair(init, 0));
    while(q.size() > 0) {
        auto [cur, cur_ind] = q.back();
        q.pop_back();
        vector<int> one_res, zero_res;
        for(int x : cur) {
            for(int y : g[x]) {
                if(w[y] == 1) one_res.push_back(y);
                else zero_res.push_back(y);
            }
        }
        sort(one_res.begin(), one_res.end());
        sort(zero_res.begin(), zero_res.end());
        one_res.erase(unique(one_res.begin(), one_res.end()), one_res.end());
        zero_res.erase(unique(zero_res.begin(), zero_res.end()), zero_res.end());
        if(!ind.count(zero_res)) {
            int x = ind.size();
            ind[zero_res] = x;
            pd.nodes.emplace_back();
            pd.nodes.back().accepting = !zero_res.empty();
            q.push_back(make_pair(zero_res, x));
        }
        pd.nodes[cur_ind].next[0] = ind[zero_res];
        if(!ind.count(one_res)) {
            int x = ind.size();
            ind[one_res] = x;
            pd.nodes.emplace_back();
            pd.nodes.back().accepting = !one_res.empty();
            q.push_back(make_pair(one_res, x));
        }
        pd.nodes[cur_ind].next[1] = ind[one_res];
    }
    remove_duplicates(pd);
    return pd;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vi w(n);
    for(int i = 0; i < n; ++i)
        cin >> w[i];
    vvi g(n);
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfa walk = powerset_construction(w, g);
    if(walk.nodes.size() == 1) {
        cout << "infinity\n";
        return 0;
    }
    vi dist(walk.nodes.size(), -1);
    dist[walk.initial] = 0;
    queue<int> q;
    q.push(walk.initial);
    int mn = INT_MAX;
    while(q.size() > 0) {
        int cur = q.front();
        q.pop();
        for(int i = 0; i < 2; ++i) {
            int j = walk.nodes[cur].next[i];
            if(dist[j] != -1) continue;
            dist[j] = dist[cur] + 1;
            if(!walk.nodes[j].accepting) {
                mn = min(mn, dist[j]);
            }
            q.push(j);
        }
    }
    cout << mn << '\n';
}

