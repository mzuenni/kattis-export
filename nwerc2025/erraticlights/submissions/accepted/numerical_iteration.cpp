#include<vector>
#include<iostream>
#include<iomanip>
#include<unordered_map>
#include<algorithm>
#include<cfloat>
#include<queue>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;

struct VectorHasher {
    int operator()(const vector<int> &V) const {
        int hash = V.size();
        for(auto &i : V) {
            hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

int n, k = 3;
unordered_map<vi,int,VectorHasher> indx;
vi is_uniform; vvvi g;

void make_exist(vi &v, queue<vi> &q) {
    if(!indx.count(v)) {
        int nonz = 0;
        for(int x : v) if(x != 0) nonz++;
        is_uniform.push_back(nonz == 1);
        g.emplace_back();
        int x = indx.size();
        indx[v] = x;
        q.push(v);
        /* cout << "IND: " << x << endl;
        for(int y : v) cout << y << ' ';
        cout << endl; */
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    cin >> n >> s;
    vi rho(k);
    string colours = "rgb";
    for(char c : s) {
        rho[colours.find(c)]++;
    }
    queue<vi> todo;
    make_exist(rho, todo);
    while(todo.size() > 0) {
        vi cur = todo.front();
        int ind = indx[cur];
        todo.pop();
        if(is_uniform[ind]) continue;
        for(int i = 0; i < k; ++i) {
            if(cur[i] == 0) continue;
            cur[i]--;
            vi poss;
            for(int j = 0; j < k; ++j) {
                cur[j]++;
                make_exist(cur, todo);
                poss.push_back(indx[cur]);
                cur[j]--;
            }
            g[ind].push_back(poss);
            cur[i]++;
        }
    }
    vector<double> weight(indx.size(), n * k + 1);
    for(int i = 0; i < indx.size(); ++i)
        if(is_uniform[i]) weight[i] = 0.0;
    while(true) {
        /* for(double x : weight) cout << x << ' ';
        cout << endl; */
        double max_delta = 0.0;
        for(int i = 0; i < indx.size(); ++i) {
            if(is_uniform[i]) continue;
            double bst = DBL_MAX;
            for(vi poss : g[i]) {
                double sm = 0.0;
                for(int j : poss) sm += weight[j];
                sm /= poss.size();
                sm += 1.0;
                bst = min(bst, sm);
            }
            if(bst < weight[i]) {
                max_delta = max(max_delta, weight[i] - bst);
                weight[i] = bst;
            }
        }
        if(max_delta < 1e-8) break;
    }
    cout << setprecision(15);
    cout << weight[0] << '\n';
}
