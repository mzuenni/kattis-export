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

void powerset_construction(vector<int> w, vector<vector<int>> g) {
    vector<int> init(g.size(), 0);
    for(int i = 0; i < g.size(); ++i)
        init[i] = i;
    map<vector<int>,int> dist;
    dist[init] = 0;
    queue<pair<vector<int>,int>> q;
    q.push(make_pair(init, 0));
    while(q.size() > 0) {
        auto [cur, cur_dist] = q.front();
        q.pop();
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
        if(one_res.empty() || zero_res.empty()) {
            cout << cur_dist + 1 << '\n';
            return;
        }
        if(!dist.count(zero_res)) {
            dist[zero_res] = cur_dist + 1;
            q.push(make_pair(zero_res, cur_dist + 1));
        }
        if(!dist.count(one_res)) {
            dist[one_res] = cur_dist + 1;
            q.push(make_pair(one_res, cur_dist + 1));
        }
    }
    cout << "infinity\n";
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
    powerset_construction(w, g);
}

